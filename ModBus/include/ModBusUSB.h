#ifndef __MODBUSUSB_H
#define __MODBUSUSB_H
//---------------------------------------------------------------------------

#include "libusb/include/libusb-1.0/libusb.h"
#include <stdlib.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//                              ���� �������
//---------------------------------------------------------------------------
//====================================================
#define MAX_COUNT_ADC   100000

typedef struct
{
  uint16_t  vid; //������������� �������������
  uint16_t  pid; //������������� ����������
  uint8_t   ep_in;
  uint8_t   ep_out;
  uint32_t  timeOut; // ������������ ����� ������� ������ �����
  uint32_t  adc_count;
  uint8_t   adc_freq;
  uint32_t  adc_channels;
}
TConfigUSBPort;

//====================================================
//====================================================

typedef struct
{
  libusb_device*          devpnt; // ��������� �� usb ����������
  libusb_device_handle*	  device_handle; // ��������� �� ���������� ����������

  uint16_t  bcdDevice;		// ����� ������ ���������� � �������-���������� ����
                          // 1- ���� ������ soft
                                    // 2- ���� ������ hard
  uint8_t   iManufacturer;  // ������ ������ ����������� �������������
  uint8_t   iProduct;       // ������ ������ ����������� �������.
  uint8_t   iSerialNumder;	// ������ ������ ����������� �������� ����� ����������
}
TUsbData;

typedef struct
{
        uint32_t    adc_channels;   // ????? ?????? ???
        uint32_t    adc_count;      // ?????????? ?????
        uint16_t    adc_freq;       // ??????? ????????????
        uint16_t    adc_buff[MAX_COUNT_ADC];     // ????? ?????? 16 ???
}
TADC_Data;

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//                              ��������� �������
//---------------------------------------------------------------------------
bool   OpenPort(TConfigUSBPort * AConfigUSBPort);  //  ������� ��������� � ����������� ���������������� ���� "COM".
void   ClosePort(void);                        //  ������� ��������� ���������������� ���� "COM".
//---------------------------------------------------------------------------
//                    ������� ������������� ������ ModBusRTU
//---------------------------------------------------------------------------
int  TransmitFrameControl(uint8_t * data_buff, uint32_t length, uint32_t waite); //  �������  ���������� ����� ������ � ���������������� ���� "COM".
int  ReseiveFrameControl (uint8_t * data_buff, uint32_t length, uint32_t waite);  //  �������  ��������� ����� ������ �� ����������������� ����� "COM"
int  ReseiveFrameData    (uint8_t * data_buff, uint32_t length, uint32_t waite);  //  �������  ��������� ����� ������ �� ����������������� ����� "COM"

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
int32_t   SetFreqSampleADC(uint8_t freq);   // ������� ���������� ��������� ������� ������� ���������� ���.

int32_t   SetCountSampleADC(uint32_t count_adc); // ������� ���������� ��������� �������� ���.

int32_t   SetEnableChannelADC(uint32_t enable);  //������� ���������� ������ � ������� ���������� ������ ������� ���

int32_t   ReadDataADC(uint32_t size_reg, uint8_t num_adc, uint16_t *buff_data);  // ������� ���������� ������ ������ ����� ���������� �������  � 65 START SAMPLE ADC

int32_t   StartSampleADC(uint32_t wait);       // ������� ��������� ������������ ���
//------------------------------------------------------------------------------
//                        ������� ��� ������ � �������
//------------------------------------------------------------------------------
#define HI(x) ((x)>>8)
#define LO(x) ((x)& 0xFF)

//------------------------------------------------------------------------------
//                              ���� ������
//------------------------------------------------------------------------------
#define ERROO_CONNECT_PORT                -10   //  ��� ���������� � ������
#define ERROR_TRANSMIT                    -12   //  ������ ��� �������� ������
#define ERROR_RECEIVE                     -14   //  ������ ��� �������� ������
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#endif // __MODBUSUSB_H
