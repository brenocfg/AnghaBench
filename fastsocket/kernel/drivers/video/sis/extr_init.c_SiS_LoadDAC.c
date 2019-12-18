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
struct SiS_Private {int SiS_VBInfo; int SiS_VBType; int SiS_SetFlag; scalar_t__ SiS_Part5Port; scalar_t__ SiS_P3c9; scalar_t__ SiS_P3c8; scalar_t__ SiS_P3c6; } ;
typedef  scalar_t__ SISIOADDRESS ;

/* Variables and functions */
 unsigned short DACInfoFlag ; 
 int ProgrammingCRT2 ; 
 int SetCRT2ToLCD ; 
 int SetCRT2ToLCDA ; 
 unsigned char* SiS_CGA_DAC ; 
 unsigned char* SiS_EGA_DAC ; 
 unsigned short SiS_GetModeFlag (struct SiS_Private*,unsigned short,unsigned short) ; 
 unsigned char* SiS_MDA_DAC ; 
 int /*<<< orphan*/  SiS_SetRegByte (scalar_t__,unsigned short) ; 
 unsigned char* SiS_VGA_DAC ; 
 int /*<<< orphan*/  SiS_WriteDAC (struct SiS_Private*,scalar_t__,unsigned short,unsigned short,unsigned char const,unsigned char const,unsigned char const) ; 
 int VB_NoLCD ; 

void
SiS_LoadDAC(struct SiS_Private *SiS_Pr, unsigned short ModeNo, unsigned short ModeIdIndex)
{
   unsigned short data, data2, time, i, j, k, m, n, o;
   unsigned short si, di, bx, sf;
   SISIOADDRESS DACAddr, DACData;
   const unsigned char *table = NULL;

   data = SiS_GetModeFlag(SiS_Pr, ModeNo, ModeIdIndex) & DACInfoFlag;

   j = time = 64;
   if(data == 0x00)      table = SiS_MDA_DAC;
   else if(data == 0x08) table = SiS_CGA_DAC;
   else if(data == 0x10) table = SiS_EGA_DAC;
   else if(data == 0x18) {
      j = 16;
      time = 256;
      table = SiS_VGA_DAC;
   }

   if( ( (SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) &&        /* 301B-DH LCD */
         (SiS_Pr->SiS_VBType & VB_NoLCD) )        ||
       (SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)       ||   /* LCDA */
       (!(SiS_Pr->SiS_SetFlag & ProgrammingCRT2)) ) {  /* Programming CRT1 */
      SiS_SetRegByte(SiS_Pr->SiS_P3c6,0xFF);
      DACAddr = SiS_Pr->SiS_P3c8;
      DACData = SiS_Pr->SiS_P3c9;
      sf = 0;
   } else {
      DACAddr = SiS_Pr->SiS_Part5Port;
      DACData = SiS_Pr->SiS_Part5Port + 1;
      sf = 2;
   }

   SiS_SetRegByte(DACAddr,0x00);

   for(i = 0; i < j; i++) {
      data = table[i];
      for(k = 0; k < 3; k++) {
	data2 = 0;
	if(data & 0x01) data2 += 0x2A;
	if(data & 0x02) data2 += 0x15;
	SiS_SetRegByte(DACData, (data2 << sf));
	data >>= 2;
      }
   }

   if(time == 256) {
      for(i = 16; i < 32; i++) {
	 data = table[i] << sf;
	 for(k = 0; k < 3; k++) SiS_SetRegByte(DACData, data);
      }
      si = 32;
      for(m = 0; m < 9; m++) {
	 di = si;
	 bx = si + 4;
	 for(n = 0; n < 3; n++) {
	    for(o = 0; o < 5; o++) {
	       SiS_WriteDAC(SiS_Pr, DACData, sf, n, table[di], table[bx], table[si]);
	       si++;
	    }
	    si -= 2;
	    for(o = 0; o < 3; o++) {
	       SiS_WriteDAC(SiS_Pr, DACData, sf, n, table[di], table[si], table[bx]);
	       si--;
	    }
	 }            /* for n < 3 */
	 si += 5;
      }               /* for m < 9 */
   }
}