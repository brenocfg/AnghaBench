#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ w_Temp ;
struct str_TimerMainHeader {unsigned short w_Ntimer; TYPE_1__* s_TimerDetails; } ;
struct TYPE_2__ {unsigned char b_Resolution; unsigned char b_Mode; unsigned short w_MinTiming; unsigned char b_TimeBase; void* w_HeaderSize; } ;

/* Variables and functions */
 void* w_EepromReadWord (unsigned short,char*,int) ; 

int i_EepromReadTimerHeader(unsigned short w_PCIBoardEepromAddress,
	char *pc_PCIChipInformation, unsigned short w_Address,
	struct str_TimerMainHeader *s_Header)
{

	unsigned short i, w_Size = 0, w_Temp;

/* Read No of Timer */
	s_Header->w_Ntimer =
		w_EepromReadWord(w_PCIBoardEepromAddress, pc_PCIChipInformation,
		0x100 + w_Address + 6);
/* Read header size */

	for (i = 0; i < s_Header->w_Ntimer; i++) {
		s_Header->s_TimerDetails[i].w_HeaderSize =
			w_EepromReadWord(w_PCIBoardEepromAddress,
			pc_PCIChipInformation,
			0x100 + w_Address + 8 + w_Size + 0);
		w_Temp = w_EepromReadWord(w_PCIBoardEepromAddress,
			pc_PCIChipInformation,
			0x100 + w_Address + 8 + w_Size + 2);

		/* Read Resolution */
		s_Header->s_TimerDetails[i].b_Resolution =
			(unsigned char) (w_Temp >> 10) & 0x3F;

		/* Read Mode */
		s_Header->s_TimerDetails[i].b_Mode =
			(unsigned char) (w_Temp >> 4) & 0x3F;

		w_Temp = w_EepromReadWord(w_PCIBoardEepromAddress,
			pc_PCIChipInformation,
			0x100 + w_Address + 8 + w_Size + 4);

		/* Read MinTiming */
		s_Header->s_TimerDetails[i].w_MinTiming = (w_Temp >> 6) & 0x3FF;

		/* Read Timebase */
		s_Header->s_TimerDetails[i].b_TimeBase = (unsigned char) (w_Temp) & 0x3F;
		w_Size += s_Header->s_TimerDetails[i].w_HeaderSize;
	}

	return 0;
}