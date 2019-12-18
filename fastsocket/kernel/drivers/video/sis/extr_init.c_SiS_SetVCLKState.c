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
struct SiS_Private {unsigned short CSRClock; scalar_t__ ChipType; int /*<<< orphan*/  SiS_P3c4; TYPE_1__* SiS_VCLKData; scalar_t__ UseCustomMode; } ;
struct TYPE_2__ {unsigned short CLOCK; } ;

/* Variables and functions */
 scalar_t__ SIS_315H ; 
 scalar_t__ SIS_315PRO ; 
 scalar_t__ SIS_540 ; 
 scalar_t__ SIS_661 ; 
 int SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 unsigned short SiS_GetVCLK2Ptr (struct SiS_Private*,unsigned short,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetRegAND (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegANDOR (int /*<<< orphan*/ ,int,int,unsigned short) ; 
 scalar_t__ XGI_20 ; 

__attribute__((used)) static void
SiS_SetVCLKState(struct SiS_Private *SiS_Pr, unsigned short ModeNo,
		unsigned short RefreshRateTableIndex, unsigned short ModeIdIndex)
{
   unsigned short data = 0, VCLK = 0, index = 0;

   if(ModeNo > 0x13) {
      if(SiS_Pr->UseCustomMode) {
         VCLK = SiS_Pr->CSRClock;
      } else {
         index = SiS_GetVCLK2Ptr(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
         VCLK = SiS_Pr->SiS_VCLKData[index].CLOCK;
      }
   }

   if(SiS_Pr->ChipType < SIS_315H) {
#ifdef SIS300
      if(VCLK > 150) data |= 0x80;
      SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x07,0x7B,data);

      data = 0x00;
      if(VCLK >= 150) data |= 0x08;
      SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x32,0xF7,data);
#endif
   } else if(SiS_Pr->ChipType < XGI_20) {
#ifdef SIS315H
      if(VCLK >= 166) data |= 0x0c;
      SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x32,0xf3,data);

      if(VCLK >= 166) {
         SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x1f,0xe7);
      }
#endif
   } else {
#ifdef SIS315H
      if(VCLK >= 200) data |= 0x0c;
      if(SiS_Pr->ChipType == XGI_20) data &= ~0x04;
      SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x32,0xf3,data);
      if(SiS_Pr->ChipType != XGI_20) {
         data = SiS_GetReg(SiS_Pr->SiS_P3c4,0x1f) & 0xe7;
	 if(VCLK < 200) data |= 0x10;
	 SiS_SetReg(SiS_Pr->SiS_P3c4,0x1f,data);
      }
#endif
   }

   /* DAC speed */
   if(SiS_Pr->ChipType >= SIS_661) {

      SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x07,0xE8,0x10);

   } else {

      data = 0x03;
      if(VCLK >= 260)      data = 0x00;
      else if(VCLK >= 160) data = 0x01;
      else if(VCLK >= 135) data = 0x02;

      if(SiS_Pr->ChipType == SIS_540) {
         if((VCLK == 203) || (VCLK < 234)) data = 0x02;
      }

      if(SiS_Pr->ChipType < SIS_315H) {
         SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x07,0xFC,data);
      } else {
         if(SiS_Pr->ChipType > SIS_315PRO) {
            if(ModeNo > 0x13) data &= 0xfc;
         }
         SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x07,0xF8,data);
      }

   }
}