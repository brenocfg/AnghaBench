#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct str_DigitalInputHeader {unsigned char b_Interruptible; void* w_NinterruptLogic; void* w_Nchannel; } ;

/* Variables and functions */
 void* w_EepromReadWord (unsigned short,char*,int) ; 

int i_EepromReadDigitalInputHeader(unsigned short w_PCIBoardEepromAddress,
	char *pc_PCIChipInformation, unsigned short w_Address,
	struct str_DigitalInputHeader *s_Header)
{
	unsigned short w_Temp;

	/*  read nbr of channels */
	s_Header->w_Nchannel =
		w_EepromReadWord(w_PCIBoardEepromAddress, pc_PCIChipInformation,
		0x100 + w_Address + 6);

	/*  interruptible or not */
	w_Temp = w_EepromReadWord(w_PCIBoardEepromAddress,
		pc_PCIChipInformation, 0x100 + w_Address + 8);
	s_Header->b_Interruptible = (unsigned char) (w_Temp >> 7) & 0x01;

/* How many interruptible logic */
	s_Header->w_NinterruptLogic =
		w_EepromReadWord(w_PCIBoardEepromAddress, pc_PCIChipInformation,
		0x100 + w_Address + 10);

	return 0;
}