#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned short w_Nchannel; unsigned char b_Resolution; } ;
typedef  TYPE_1__ str_AnalogOutputHeader ;

/* Variables and functions */
 unsigned short w_EepromReadWord (unsigned short,char*,int) ; 

int i_EepromReadAnlogOutputHeader(unsigned short w_PCIBoardEepromAddress,
	char *pc_PCIChipInformation, unsigned short w_Address,
	str_AnalogOutputHeader *s_Header)
{
	unsigned short w_Temp;
	/*  No of channels for 1st hard component */
	w_Temp = w_EepromReadWord(w_PCIBoardEepromAddress,
		pc_PCIChipInformation, 0x100 + w_Address + 10);
	s_Header->w_Nchannel = (w_Temp >> 4) & 0x03FF;
	/*  Resolution for 1st hard component */
	w_Temp = w_EepromReadWord(w_PCIBoardEepromAddress,
		pc_PCIChipInformation, 0x100 + w_Address + 16);
	s_Header->b_Resolution = (unsigned char) (w_Temp >> 8) & 0xFF;
	return 0;
}