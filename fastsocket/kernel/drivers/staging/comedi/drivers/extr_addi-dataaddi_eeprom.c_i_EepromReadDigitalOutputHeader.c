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
struct str_DigitalOutputHeader {int /*<<< orphan*/  w_Nchannel; } ;

/* Variables and functions */
 int /*<<< orphan*/  w_EepromReadWord (unsigned short,char*,int) ; 

int i_EepromReadDigitalOutputHeader(unsigned short w_PCIBoardEepromAddress,
	char *pc_PCIChipInformation, unsigned short w_Address,
	struct str_DigitalOutputHeader *s_Header)
{
/* Read Nbr channels */
	s_Header->w_Nchannel =
		w_EepromReadWord(w_PCIBoardEepromAddress, pc_PCIChipInformation,
		0x100 + w_Address + 6);
	return 0;
}