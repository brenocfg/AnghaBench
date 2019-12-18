#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct SiS_Private {unsigned char* VirtualRomBase; unsigned short CInfoFlag; scalar_t__ SiS_ModeType; scalar_t__ ChipType; unsigned short* SiS_SR15; int SiS_SysFlags; unsigned short CSRClock; int /*<<< orphan*/  SiS_P3d4; int /*<<< orphan*/  SiS_P3c4; TYPE_1__* SiS_VCLKData; scalar_t__ UseCustomMode; scalar_t__ SiS_UseROM; scalar_t__ SiS_ROMNew; TYPE_2__* SiS_RefIndex; } ;
struct TYPE_4__ {unsigned short Ext_InfoFlag; } ;
struct TYPE_3__ {unsigned short CLOCK; } ;

/* Variables and functions */
 unsigned short HalfDCLK ; 
 unsigned short InterlaceMode ; 
 unsigned short LineCompareOff ; 
 scalar_t__ Mode16Bpp ; 
 scalar_t__ ModeEGA ; 
 scalar_t__ ModeText ; 
 int ModeVGA ; 
 int SF_760LFB ; 
 scalar_t__ SIS_300 ; 
 scalar_t__ SIS_315H ; 
 scalar_t__ SIS_315PRO ; 
 scalar_t__ SIS_330 ; 
 scalar_t__ SIS_661 ; 
 int SiS_Get310DRAMType (struct SiS_Private*) ; 
 int SiS_GetColorDepth (struct SiS_Private*,unsigned short,unsigned short) ; 
 int SiS_GetMCLK (struct SiS_Private*) ; 
 unsigned short SiS_GetModeFlag (struct SiS_Private*,unsigned short,unsigned short) ; 
 int SiS_GetOffset (struct SiS_Private*,unsigned short,unsigned short,unsigned short) ; 
 int SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 unsigned short SiS_GetResInfo (struct SiS_Private*,unsigned short,unsigned short) ; 
 unsigned short SiS_GetVCLK2Ptr (struct SiS_Private*,unsigned short,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegAND (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegANDOR (int /*<<< orphan*/ ,int,int,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetRegOR (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetVCLKState (struct SiS_Private*,unsigned short,unsigned short,unsigned short) ; 
 scalar_t__ XGI_20 ; 
 scalar_t__ XGI_40 ; 

__attribute__((used)) static void
SiS_SetCRT1ModeRegs(struct SiS_Private *SiS_Pr, unsigned short ModeNo,
		unsigned short ModeIdIndex, unsigned short RRTI)
{
   unsigned short data, infoflag = 0, modeflag, resindex;
#ifdef SIS315H
   unsigned char  *ROMAddr  = SiS_Pr->VirtualRomBase;
   unsigned short data2, data3;
#endif

   modeflag = SiS_GetModeFlag(SiS_Pr, ModeNo, ModeIdIndex);

   if(SiS_Pr->UseCustomMode) {
      infoflag = SiS_Pr->CInfoFlag;
   } else {
      resindex = SiS_GetResInfo(SiS_Pr, ModeNo, ModeIdIndex);
      if(ModeNo > 0x13) {
	 infoflag = SiS_Pr->SiS_RefIndex[RRTI].Ext_InfoFlag;
      }
   }

   /* Disable DPMS */
   SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x1F,0x3F);

   data = 0;
   if(ModeNo > 0x13) {
      if(SiS_Pr->SiS_ModeType > ModeEGA) {
         data |= 0x02;
         data |= ((SiS_Pr->SiS_ModeType - ModeVGA) << 2);
      }
      if(infoflag & InterlaceMode) data |= 0x20;
   }
   SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x06,0xC0,data);

   if(SiS_Pr->ChipType != SIS_300) {
      data = 0;
      if(infoflag & InterlaceMode) {
	 /* data = (Hsync / 8) - ((Htotal / 8) / 2) + 3 */
	 int hrs = (SiS_GetReg(SiS_Pr->SiS_P3d4,0x04) |
		    ((SiS_GetReg(SiS_Pr->SiS_P3c4,0x0b) & 0xc0) << 2)) - 3;
	 int hto = (SiS_GetReg(SiS_Pr->SiS_P3d4,0x00) |
		    ((SiS_GetReg(SiS_Pr->SiS_P3c4,0x0b) & 0x03) << 8)) + 5;
	 data = hrs - (hto >> 1) + 3;
      }
      SiS_SetReg(SiS_Pr->SiS_P3d4,0x19,data);
      SiS_SetRegANDOR(SiS_Pr->SiS_P3d4,0x1a,0xFC,((data >> 8) & 0x03));
   }

   if(modeflag & HalfDCLK) {
      SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x01,0x08);
   }

   data = 0;
   if(modeflag & LineCompareOff) data = 0x08;
   if(SiS_Pr->ChipType == SIS_300) {
      SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x0F,0xF7,data);
   } else {
      if(SiS_Pr->ChipType >= XGI_20) data |= 0x20;
      if(SiS_Pr->SiS_ModeType == ModeEGA) {
	 if(ModeNo > 0x13) {
	    data |= 0x40;
	 }
      }
      SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x0F,0xB7,data);
   }

#ifdef SIS315H
   if(SiS_Pr->ChipType >= SIS_315H) {
      SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x31,0xfb);
   }

   if(SiS_Pr->ChipType == SIS_315PRO) {

      data = SiS_Pr->SiS_SR15[(2 * 4) + SiS_Get310DRAMType(SiS_Pr)];
      if(SiS_Pr->SiS_ModeType == ModeText) {
	 data &= 0xc7;
      } else {
	 data2 = SiS_GetOffset(SiS_Pr, ModeNo, ModeIdIndex, RRTI) >> 1;
	 if(infoflag & InterlaceMode) data2 >>= 1;
	 data3 = SiS_GetColorDepth(SiS_Pr, ModeNo, ModeIdIndex) >> 1;
	 if(data3) data2 /= data3;
	 if(data2 >= 0x50) {
	    data &= 0x0f;
	    data |= 0x50;
	 }
      }
      SiS_SetReg(SiS_Pr->SiS_P3c4,0x17,data);

   } else if((SiS_Pr->ChipType == SIS_330) || (SiS_Pr->SiS_SysFlags & SF_760LFB)) {

      data = SiS_Get310DRAMType(SiS_Pr);
      if(SiS_Pr->ChipType == SIS_330) {
	 data = SiS_Pr->SiS_SR15[(2 * 4) + data];
      } else {
	 if(SiS_Pr->SiS_ROMNew)	     data = ROMAddr[0xf6];
	 else if(SiS_Pr->SiS_UseROM) data = ROMAddr[0x100 + data];
	 else			     data = 0xba;
      }
      if(SiS_Pr->SiS_ModeType <= ModeEGA) {
	 data &= 0xc7;
      } else {
	 if(SiS_Pr->UseCustomMode) {
	    data2 = SiS_Pr->CSRClock;
	 } else {
	    data2 = SiS_GetVCLK2Ptr(SiS_Pr, ModeNo, ModeIdIndex, RRTI);
	    data2 = SiS_Pr->SiS_VCLKData[data2].CLOCK;
	 }

	 data3 = SiS_GetColorDepth(SiS_Pr, ModeNo, ModeIdIndex) >> 1;
	 if(data3) data2 *= data3;

	 data2 = ((unsigned int)(SiS_GetMCLK(SiS_Pr) * 1024)) / data2;

	 if(SiS_Pr->ChipType == SIS_330) {
	    if(SiS_Pr->SiS_ModeType != Mode16Bpp) {
	       if     (data2 >= 0x19c) data = 0xba;
	       else if(data2 >= 0x140) data = 0x7a;
	       else if(data2 >= 0x101) data = 0x3a;
	       else if(data2 >= 0xf5)  data = 0x32;
	       else if(data2 >= 0xe2)  data = 0x2a;
	       else if(data2 >= 0xc4)  data = 0x22;
	       else if(data2 >= 0xac)  data = 0x1a;
	       else if(data2 >= 0x9e)  data = 0x12;
	       else if(data2 >= 0x8e)  data = 0x0a;
	       else                    data = 0x02;
	    } else {
	       if(data2 >= 0x127)      data = 0xba;
	       else                    data = 0x7a;
	    }
	 } else {  /* 76x+LFB */
	    if     (data2 >= 0x190) data = 0xba;
	    else if(data2 >= 0xff)  data = 0x7a;
	    else if(data2 >= 0xd3)  data = 0x3a;
	    else if(data2 >= 0xa9)  data = 0x1a;
	    else if(data2 >= 0x93)  data = 0x0a;
	    else                    data = 0x02;
	 }
      }
      SiS_SetReg(SiS_Pr->SiS_P3c4,0x17,data);

   }
      /* XGI: Nothing. */
      /* TODO: Check SiS340 */
#endif

   data = 0x60;
   if(SiS_Pr->SiS_ModeType != ModeText) {
      data ^= 0x60;
      if(SiS_Pr->SiS_ModeType != ModeEGA) {
         data ^= 0xA0;
      }
   }
   SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x21,0x1F,data);

   SiS_SetVCLKState(SiS_Pr, ModeNo, RRTI, ModeIdIndex);

#ifdef SIS315H
   if(((SiS_Pr->ChipType >= SIS_315H) && (SiS_Pr->ChipType < SIS_661)) ||
       (SiS_Pr->ChipType == XGI_40)) {
      if(SiS_GetReg(SiS_Pr->SiS_P3d4,0x31) & 0x40) {
         SiS_SetReg(SiS_Pr->SiS_P3d4,0x52,0x2c);
      } else {
         SiS_SetReg(SiS_Pr->SiS_P3d4,0x52,0x6c);
      }
   } else if(SiS_Pr->ChipType == XGI_20) {
      if(SiS_GetReg(SiS_Pr->SiS_P3d4,0x31) & 0x40) {
         SiS_SetReg(SiS_Pr->SiS_P3d4,0x52,0x33);
      } else {
         SiS_SetReg(SiS_Pr->SiS_P3d4,0x52,0x73);
      }
      SiS_SetReg(SiS_Pr->SiS_P3d4,0x51,0x02);
   }
#endif
}