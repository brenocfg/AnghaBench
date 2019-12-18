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
struct str_AnalogInputHeader {unsigned short w_Nchannel; unsigned short b_HasDma; unsigned short b_Resolution; void* w_MinDelayTiming; void* w_MinConvertTiming; } ;

/* Variables and functions */
 void* w_EepromReadWord (unsigned short,char*,int) ; 

int i_EepromReadAnlogInputHeader(unsigned short w_PCIBoardEepromAddress,
	char *pc_PCIChipInformation, unsigned short w_Address,
	struct str_AnalogInputHeader *s_Header)
{
	unsigned short w_Temp, w_Offset;
	w_Temp = w_EepromReadWord(w_PCIBoardEepromAddress,
		pc_PCIChipInformation, 0x100 + w_Address + 10);
	s_Header->w_Nchannel = (w_Temp >> 4) & 0x03FF;
	s_Header->w_MinConvertTiming =
		w_EepromReadWord(w_PCIBoardEepromAddress, pc_PCIChipInformation,
		0x100 + w_Address + 16);
	s_Header->w_MinDelayTiming =
		w_EepromReadWord(w_PCIBoardEepromAddress, pc_PCIChipInformation,
		0x100 + w_Address + 30);
	w_Temp = w_EepromReadWord(w_PCIBoardEepromAddress,
		pc_PCIChipInformation, 0x100 + w_Address + 20);
	s_Header->b_HasDma = (w_Temp >> 13) & 0x01;	/*  whether dma present or not */

	w_Temp = w_EepromReadWord(w_PCIBoardEepromAddress, pc_PCIChipInformation, 0x100 + w_Address + 72);	/*  reading Y */
	w_Temp = w_Temp & 0x00FF;
	if (w_Temp)		/* Y>0 */
	{
		w_Offset = 74 + (2 * w_Temp) + (10 * (1 + (w_Temp / 16)));	/*  offset of first analog input single header */
		w_Offset = w_Offset + 2;	/*  resolution */
	} else			/* Y=0 */
	{
		w_Offset = 74;
		w_Offset = w_Offset + 2;	/*  resolution */
	}

/* read Resolution */
	w_Temp = w_EepromReadWord(w_PCIBoardEepromAddress,
		pc_PCIChipInformation, 0x100 + w_Address + w_Offset);
	s_Header->b_Resolution = w_Temp & 0x001F;	/*  last 5 bits */

	return 0;
}