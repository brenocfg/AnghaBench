#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct str_MainHeader {unsigned char b_Nfunctions; TYPE_1__* s_Functions; void* w_HeaderSize; } ;
struct str_DigitalOutputHeader {int /*<<< orphan*/  w_Nchannel; } ;
struct str_DigitalInputHeader {int /*<<< orphan*/  w_Nchannel; } ;
struct str_AnalogInputHeader {int w_Nchannel; int /*<<< orphan*/  b_Resolution; scalar_t__ w_MinDelayTiming; scalar_t__ w_MinConvertTiming; int /*<<< orphan*/  b_HasDma; } ;
struct comedi_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  b_Resolution; int /*<<< orphan*/  w_Nchannel; } ;
typedef  TYPE_2__ str_AnalogOutputHeader ;
struct TYPE_7__ {unsigned int i_DoMaxdata; int i_NbrAiChannel; unsigned int ui_MinAcquisitiontimeNs; unsigned int ui_MinDelaytimeNs; unsigned int i_AiMaxdata; unsigned int i_AoMaxdata; int i_Timer; int /*<<< orphan*/  i_NbrAoChannel; int /*<<< orphan*/  i_Dma; int /*<<< orphan*/  pc_DriverName; int /*<<< orphan*/  i_NbrDoChannel; int /*<<< orphan*/  i_NbrDiChannel; } ;
struct TYPE_5__ {unsigned char b_Type; void* w_Address; } ;

/* Variables and functions */
#define  EEPROM_ANALOGINPUT 134 
#define  EEPROM_ANALOGOUTPUT 133 
#define  EEPROM_DIGITALINPUT 132 
#define  EEPROM_DIGITALOUTPUT 131 
#define  EEPROM_TIMER 130 
#define  EEPROM_TIMER_WATCHDOG_COUNTER 129 
#define  EEPROM_WATCHDOG 128 
 int /*<<< orphan*/  i_EepromReadAnlogInputHeader (unsigned short,char*,void*,struct str_AnalogInputHeader*) ; 
 int /*<<< orphan*/  i_EepromReadAnlogOutputHeader (unsigned short,char*,void*,TYPE_2__*) ; 
 int /*<<< orphan*/  i_EepromReadDigitalInputHeader (unsigned short,char*,void*,struct str_DigitalInputHeader*) ; 
 int /*<<< orphan*/  i_EepromReadDigitalOutputHeader (unsigned short,char*,void*,struct str_DigitalOutputHeader*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* this_board ; 
 void* w_EepromReadWord (unsigned short,char*,int) ; 

int i_EepromReadMainHeader(unsigned short w_PCIBoardEepromAddress,
	char *pc_PCIChipInformation, struct comedi_device *dev)
{
	unsigned short w_Temp, i, w_Count = 0;
	unsigned int ui_Temp;
	struct str_MainHeader s_MainHeader;
	struct str_DigitalInputHeader s_DigitalInputHeader;
	struct str_DigitalOutputHeader s_DigitalOutputHeader;
	/* struct str_TimerMainHeader     s_TimerMainHeader,s_WatchdogMainHeader; */
	str_AnalogOutputHeader s_AnalogOutputHeader;
	struct str_AnalogInputHeader s_AnalogInputHeader;

	/* Read size */
	s_MainHeader.w_HeaderSize =
		w_EepromReadWord(w_PCIBoardEepromAddress, pc_PCIChipInformation,
		0x100 + 8);

	/* Read nbr of functionality */
	w_Temp = w_EepromReadWord(w_PCIBoardEepromAddress,
		pc_PCIChipInformation, 0x100 + 10);
	s_MainHeader.b_Nfunctions = (unsigned char) w_Temp & 0x00FF;

	/* Read functionality details */
	for (i = 0; i < s_MainHeader.b_Nfunctions; i++) {
		/* Read Type */
		w_Temp = w_EepromReadWord(w_PCIBoardEepromAddress,
			pc_PCIChipInformation, 0x100 + 12 + w_Count);
		s_MainHeader.s_Functions[i].b_Type = (unsigned char) w_Temp & 0x3F;
		w_Count = w_Count + 2;
		/* Read Address */
		s_MainHeader.s_Functions[i].w_Address =
			w_EepromReadWord(w_PCIBoardEepromAddress,
			pc_PCIChipInformation, 0x100 + 12 + w_Count);
		w_Count = w_Count + 2;
	}

	/* Display main header info */
	for (i = 0; i < s_MainHeader.b_Nfunctions; i++) {

		switch (s_MainHeader.s_Functions[i].b_Type) {
		case EEPROM_DIGITALINPUT:
			i_EepromReadDigitalInputHeader(w_PCIBoardEepromAddress,
				pc_PCIChipInformation,
				s_MainHeader.s_Functions[i].w_Address,
				&s_DigitalInputHeader);
			this_board->i_NbrDiChannel =
				s_DigitalInputHeader.w_Nchannel;
			break;

		case EEPROM_DIGITALOUTPUT:
			i_EepromReadDigitalOutputHeader(w_PCIBoardEepromAddress,
				pc_PCIChipInformation,
				s_MainHeader.s_Functions[i].w_Address,
				&s_DigitalOutputHeader);
			this_board->i_NbrDoChannel =
				s_DigitalOutputHeader.w_Nchannel;
			ui_Temp = 0xffffffff;
			this_board->i_DoMaxdata =
				ui_Temp >> (32 - this_board->i_NbrDoChannel);
			break;

		case EEPROM_ANALOGINPUT:
			i_EepromReadAnlogInputHeader(w_PCIBoardEepromAddress,
				pc_PCIChipInformation,
				s_MainHeader.s_Functions[i].w_Address,
				&s_AnalogInputHeader);
			if (!(strcmp(this_board->pc_DriverName, "apci3200")))
				this_board->i_NbrAiChannel =
					s_AnalogInputHeader.w_Nchannel * 4;
			else
				this_board->i_NbrAiChannel =
					s_AnalogInputHeader.w_Nchannel;
			this_board->i_Dma = s_AnalogInputHeader.b_HasDma;
			this_board->ui_MinAcquisitiontimeNs =
				(unsigned int) s_AnalogInputHeader.w_MinConvertTiming *
				1000;
			this_board->ui_MinDelaytimeNs =
				(unsigned int) s_AnalogInputHeader.w_MinDelayTiming *
				1000;
			ui_Temp = 0xffff;
			this_board->i_AiMaxdata =
				ui_Temp >> (16 -
				s_AnalogInputHeader.b_Resolution);
			break;

		case EEPROM_ANALOGOUTPUT:
			i_EepromReadAnlogOutputHeader(w_PCIBoardEepromAddress,
				pc_PCIChipInformation,
				s_MainHeader.s_Functions[i].w_Address,
				&s_AnalogOutputHeader);
			this_board->i_NbrAoChannel =
				s_AnalogOutputHeader.w_Nchannel;
			ui_Temp = 0xffff;
			this_board->i_AoMaxdata =
				ui_Temp >> (16 -
				s_AnalogOutputHeader.b_Resolution);
			break;

		case EEPROM_TIMER:
			this_board->i_Timer = 1;	/* Timer subdevice present */
			break;

		case EEPROM_WATCHDOG:
			this_board->i_Timer = 1;	/* Timer subdevice present */
			break;

		case EEPROM_TIMER_WATCHDOG_COUNTER:
			this_board->i_Timer = 1;	/* Timer subdevice present */
		}
	}

	return 0;
}