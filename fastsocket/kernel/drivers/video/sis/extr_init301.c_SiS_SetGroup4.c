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
struct SiS_Private {unsigned short CModeFlag; scalar_t__ ChipType; int SiS_VBType; int SiS_VBInfo; int SiS_RVBHCFACT; unsigned short SiS_RVBHCMAX; int SiS_VGAHT; int SiS_VGAVT; unsigned short SiS_VGAHDE; int SiS_TVMode; unsigned short Init_P4_0E; scalar_t__ SiS_LCDResInfo; unsigned int SiS_VGAVDE; unsigned int SiS_VDE; unsigned short SiS_RVBHRS; int SiS_HT; int /*<<< orphan*/  SiS_Part4Port; TYPE_2__* SiS_EModeIDTable; scalar_t__ UseCustomMode; TYPE_1__* SiS_SModeIDTable; } ;
struct TYPE_4__ {unsigned short Ext_ModeFlag; unsigned short Ext_RESINFO; } ;
struct TYPE_3__ {unsigned short St_ModeFlag; unsigned short St_ResInfo; } ;

/* Variables and functions */
 unsigned short HalfDCLK ; 
 scalar_t__ Panel_1280x1024 ; 
 scalar_t__ SIS_315H ; 
 unsigned short SIS_RI_1024x576 ; 
 unsigned short SIS_RI_1024x768 ; 
 unsigned short SIS_RI_1280x1024 ; 
 unsigned short SIS_RI_1280x720 ; 
 int SetCRT2ToHiVision ; 
 int SetCRT2ToLCD ; 
 int SetCRT2ToLCDA ; 
 int SetCRT2ToTV ; 
 int SetInSlaveMode ; 
 scalar_t__ SiS_IsDualLink (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_SetCRT2VCLK (struct SiS_Private*,unsigned short,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetDualLinkEtc (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegAND (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegANDOR (int /*<<< orphan*/ ,int,int,unsigned short) ; 
 int TVSetHiVision ; 
 int TVSetNTSC1024 ; 
 int TVSetTVSimuMode ; 
 int TVSetYPbPr525p ; 
 int TVSetYPbPr750p ; 
 int VB_SIS301 ; 
 int VB_SIS302LV ; 
 int VB_SIS30xBLV ; 
 int VB_SIS30xCLV ; 
 int VB_SISLVDS ; 

__attribute__((used)) static void
SiS_SetGroup4(struct SiS_Private *SiS_Pr, unsigned short ModeNo, unsigned short ModeIdIndex,
		unsigned short RefreshRateTableIndex)
{
  unsigned short tempax, tempcx, tempbx, modeflag, temp, resinfo;
  unsigned int   tempebx, tempeax, templong;

  if(ModeNo <= 0x13) {
     modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
     resinfo = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ResInfo;
  } else if(SiS_Pr->UseCustomMode) {
     modeflag = SiS_Pr->CModeFlag;
     resinfo = 0;
  } else {
     modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
     resinfo = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_RESINFO;
  }

  if(SiS_Pr->ChipType >= SIS_315H) {
     if(SiS_Pr->SiS_VBType & VB_SISLVDS) {
	if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) {
	   SiS_SetReg(SiS_Pr->SiS_Part4Port,0x24,0x0e);
	}
     }
  }

  if(SiS_Pr->SiS_VBType & (VB_SIS30xCLV | VB_SIS302LV)) {
     if(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) {
	SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x10,0x9f);
     }
  }

  if(SiS_Pr->ChipType >= SIS_315H) {
     if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) {
	SiS_SetDualLinkEtc(SiS_Pr);
	return;
     }
  }

  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x13,SiS_Pr->SiS_RVBHCFACT);

  tempbx = SiS_Pr->SiS_RVBHCMAX;
  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x14,tempbx);

  temp = (tempbx >> 1) & 0x80;

  tempcx = SiS_Pr->SiS_VGAHT - 1;
  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x16,tempcx);

  temp |= ((tempcx >> 5) & 0x78);

  tempcx = SiS_Pr->SiS_VGAVT - 1;
  if(!(SiS_Pr->SiS_VBInfo & SetCRT2ToTV)) tempcx -= 5;
  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x17,tempcx);

  temp |= ((tempcx >> 8) & 0x07);
  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x15,temp);

  tempbx = SiS_Pr->SiS_VGAHDE;
  if(modeflag & HalfDCLK)    tempbx >>= 1;
  if(SiS_IsDualLink(SiS_Pr)) tempbx >>= 1;

  if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) {
     temp = 0;
     if(tempbx > 800)        temp = 0x60;
  } else if(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) {
     temp = 0;
     if(tempbx > 1024)       temp = 0xC0;
     else if(tempbx >= 960)  temp = 0xA0;
  } else if(SiS_Pr->SiS_TVMode & (TVSetYPbPr525p | TVSetYPbPr750p)) {
     temp = 0;
     if(tempbx >= 1280)      temp = 0x40;
     else if(tempbx >= 1024) temp = 0x20;
  } else {
     temp = 0x80;
     if(tempbx >= 1024)      temp = 0xA0;
  }

  temp |= SiS_Pr->Init_P4_0E;

  if(SiS_Pr->SiS_VBType & VB_SIS301) {
     if(SiS_Pr->SiS_LCDResInfo != Panel_1280x1024) {
        temp &= 0xf0;
        temp |= 0x0A;
     }
  }

  SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x0E,0x10,temp);

  tempeax = SiS_Pr->SiS_VGAVDE;
  tempebx = SiS_Pr->SiS_VDE;
  if(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) {
     if(!(temp & 0xE0)) tempebx >>=1;
  }

  tempcx = SiS_Pr->SiS_RVBHRS;
  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x18,tempcx);
  tempcx >>= 8;
  tempcx |= 0x40;

  if(tempeax <= tempebx) {
     tempcx ^= 0x40;
  } else {
     tempeax -= tempebx;
  }

  tempeax *= (256 * 1024);
  templong = tempeax % tempebx;
  tempeax /= tempebx;
  if(templong) tempeax++;

  temp = (unsigned short)(tempeax & 0x000000FF);
  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x1B,temp);
  temp = (unsigned short)((tempeax & 0x0000FF00) >> 8);
  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x1A,temp);
  temp = (unsigned short)((tempeax >> 12) & 0x70); /* sic! */
  temp |= (tempcx & 0x4F);
  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x19,temp);

  if(SiS_Pr->SiS_VBType & VB_SIS30xBLV) {

     SiS_SetReg(SiS_Pr->SiS_Part4Port,0x1C,0x28);

     /* Calc Linebuffer max address and set/clear decimode */
     tempbx = 0;
     if(SiS_Pr->SiS_TVMode & (TVSetHiVision | TVSetYPbPr750p)) tempbx = 0x08;
     tempax = SiS_Pr->SiS_VGAHDE;
     if(modeflag & HalfDCLK)    tempax >>= 1;
     if(SiS_IsDualLink(SiS_Pr)) tempax >>= 1;
     if(tempax > 800) {
        if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) {
	   tempax -= 800;
	} else {
	   tempbx = 0x08;
	   if(tempax == 960)	   tempax *= 25; /* Correct */
           else if(tempax == 1024) tempax *= 25;
           else			   tempax *= 20;
	   temp = tempax % 32;
	   tempax /= 32;
	   if(temp) tempax++;
	   tempax++;
	   if(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) {
	      if(resinfo == SIS_RI_1024x768 ||
	         resinfo == SIS_RI_1024x576 ||
		 resinfo == SIS_RI_1280x1024 ||
		 resinfo == SIS_RI_1280x720) {
	         /* Otherwise white line or garbage at right edge */
	         tempax = (tempax & 0xff00) | 0x20;
	      }
	   }
	}
     }
     tempax--;
     temp = ((tempax >> 4) & 0x30) | tempbx;
     SiS_SetReg(SiS_Pr->SiS_Part4Port,0x1D,tempax);
     SiS_SetReg(SiS_Pr->SiS_Part4Port,0x1E,temp);

     temp = 0x0036; tempbx = 0xD0;
     if((SiS_Pr->ChipType >= SIS_315H) && (SiS_Pr->SiS_VBType & VB_SISLVDS)) {
	temp = 0x0026; tempbx = 0xC0; /* See En/DisableBridge() */
     }
     if(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) {
        if(!(SiS_Pr->SiS_TVMode & (TVSetNTSC1024 | TVSetHiVision | TVSetYPbPr750p | TVSetYPbPr525p))) {
	   temp |= 0x01;
	   if(SiS_Pr->SiS_VBInfo & SetInSlaveMode) {
	      if(!(SiS_Pr->SiS_TVMode & TVSetTVSimuMode)) {
  	         temp &= ~0x01;
	      }
	   }
	}
     }
     SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x1F,tempbx,temp);

     tempbx = SiS_Pr->SiS_HT >> 1;
     if(SiS_IsDualLink(SiS_Pr)) tempbx >>= 1;
     tempbx -= 2;
     SiS_SetReg(SiS_Pr->SiS_Part4Port,0x22,tempbx);
     temp = (tempbx >> 5) & 0x38;
     SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x21,0xC0,temp);

     if(SiS_Pr->SiS_VBType & VB_SISLVDS) {
	if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) {
           SiS_SetReg(SiS_Pr->SiS_Part4Port,0x24,0x0e);
	   /* LCD-too-dark-error-source, see FinalizeLCD() */
	}
     }

     SiS_SetDualLinkEtc(SiS_Pr);

  }  /* 301B */

  SiS_SetCRT2VCLK(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
}