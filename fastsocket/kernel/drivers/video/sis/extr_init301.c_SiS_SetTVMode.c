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
struct SiS_Private {unsigned char* VirtualRomBase; unsigned char* pSiS_OutputSelect; int SiS_TVMode; int SiS_VBInfo; scalar_t__ ChipType; int SiS_VBType; scalar_t__ SiS_YPbPr; int SiS_IF_DEF_CH70xx; int SiS_CHOverScan; int /*<<< orphan*/  SiS_P3d4; scalar_t__ SiS_CHSOverScan; int /*<<< orphan*/  SiS_ROMNew; scalar_t__ SiS_UseROM; TYPE_1__* SiS_EModeIDTable; scalar_t__ UseCustomMode; } ;
struct TYPE_2__ {unsigned short Ext_RESINFO; } ;

/* Variables and functions */
 unsigned short EnableNTSCJ ; 
 unsigned short EnablePALM ; 
 unsigned char EnablePALMN ; 
 unsigned short EnablePALN ; 
 scalar_t__ SIS_315H ; 
 scalar_t__ SIS_330 ; 
 scalar_t__ SIS_630 ; 
 scalar_t__ SIS_661 ; 
 scalar_t__ SIS_730 ; 
 unsigned short SIS_RI_1024x576 ; 
 unsigned short SIS_RI_1024x768 ; 
 unsigned short SIS_RI_1280x720 ; 
 unsigned short SIS_RI_800x480 ; 
 int SetCRT2ToHiVision ; 
 int SetCRT2ToSCART ; 
 int SetCRT2ToTV ; 
 int SetCRT2ToYPbPr525750 ; 
 int SetInSlaveMode ; 
 int SetNotSimuMode ; 
 int SetPALTV ; 
 unsigned short SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SiS_SetRegAND (int /*<<< orphan*/ ,unsigned short,int) ; 
 int TVAspect169 ; 
 int TVAspect43 ; 
 int TVAspect43LB ; 
 unsigned short TVOverScan ; 
 int TVRPLLDIV2XO ; 
 int TVSet525p1024 ; 
 int TVSetCHOverScan ; 
 int TVSetHiVision ; 
 int TVSetNTSC1024 ; 
 int TVSetNTSCJ ; 
 int TVSetPAL ; 
 int TVSetPALM ; 
 int TVSetPALN ; 
 int TVSetTVSimuMode ; 
 int TVSetYPbPr525i ; 
 int TVSetYPbPr525p ; 
 int TVSetYPbPr750p ; 
 int VB_SIS30xBLV ; 
 int VB_SISVB ; 
 scalar_t__ XGI_20 ; 
 int /*<<< orphan*/  X_INFO ; 
 scalar_t__ YPbPr525p ; 
 scalar_t__ YPbPr750p ; 
 scalar_t__ YPbPrHiVision ; 
 int /*<<< orphan*/  xf86DrvMsg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 

void
SiS_SetTVMode(struct SiS_Private *SiS_Pr, unsigned short ModeNo, unsigned short ModeIdIndex)
{
   unsigned char  *ROMAddr = SiS_Pr->VirtualRomBase;
   unsigned short temp, temp1, resinfo = 0, romindex = 0;
   unsigned char  OutputSelect = *SiS_Pr->pSiS_OutputSelect;

   SiS_Pr->SiS_TVMode = 0;

   if(!(SiS_Pr->SiS_VBInfo & SetCRT2ToTV)) return;
   if(SiS_Pr->UseCustomMode) return;

   if(ModeNo > 0x13) {
      resinfo = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_RESINFO;
   }

   if(SiS_Pr->ChipType < SIS_661) {

      if(SiS_Pr->SiS_VBInfo & SetPALTV) SiS_Pr->SiS_TVMode |= TVSetPAL;

      if(SiS_Pr->SiS_VBType & VB_SISVB) {
	 temp = 0;
	 if((SiS_Pr->ChipType == SIS_630) ||
	    (SiS_Pr->ChipType == SIS_730)) {
	    temp = 0x35;
	    romindex = 0xfe;
	 } else if(SiS_Pr->ChipType >= SIS_315H) {
	    temp = 0x38;
	    if(SiS_Pr->ChipType < XGI_20) {
	       romindex = 0xf3;
	       if(SiS_Pr->ChipType >= SIS_330) romindex = 0x11b;
	    }
	 }
	 if(temp) {
	    if(romindex && SiS_Pr->SiS_UseROM && (!(SiS_Pr->SiS_ROMNew))) {
	       OutputSelect = ROMAddr[romindex];
	       if(!(OutputSelect & EnablePALMN)) {
		  SiS_SetRegAND(SiS_Pr->SiS_P3d4,temp,0x3F);
	       }
	    }
	    temp1 = SiS_GetReg(SiS_Pr->SiS_P3d4,temp);
	    if(SiS_Pr->SiS_TVMode & TVSetPAL) {
	       if(temp1 & EnablePALM) {		/* 0x40 */
		  SiS_Pr->SiS_TVMode |= TVSetPALM;
		  SiS_Pr->SiS_TVMode &= ~TVSetPAL;
	       } else if(temp1 & EnablePALN) {	/* 0x80 */
		  SiS_Pr->SiS_TVMode |= TVSetPALN;
	       }
	    } else {
	       if(temp1 & EnableNTSCJ) {	/* 0x40 */
		  SiS_Pr->SiS_TVMode |= TVSetNTSCJ;
	       }
	    }
	 }
	 /* Translate HiVision/YPbPr to our new flags */
	 if(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) {
	    if(SiS_Pr->SiS_YPbPr == YPbPr750p)          SiS_Pr->SiS_TVMode |= TVSetYPbPr750p;
	    else if(SiS_Pr->SiS_YPbPr == YPbPr525p)     SiS_Pr->SiS_TVMode |= TVSetYPbPr525p;
	    else if(SiS_Pr->SiS_YPbPr == YPbPrHiVision) SiS_Pr->SiS_TVMode |= TVSetHiVision;
	    else				        SiS_Pr->SiS_TVMode |= TVSetYPbPr525i;
	    if(SiS_Pr->SiS_TVMode & (TVSetYPbPr750p | TVSetYPbPr525p | TVSetYPbPr525i)) {
	       SiS_Pr->SiS_VBInfo &= ~SetCRT2ToHiVision;
	       SiS_Pr->SiS_VBInfo |= SetCRT2ToYPbPr525750;
	    } else if(SiS_Pr->SiS_TVMode & TVSetHiVision) {
	       SiS_Pr->SiS_TVMode |= TVSetPAL;
	    }
	 }
      } else if(SiS_Pr->SiS_IF_DEF_CH70xx != 0) {
	 if(SiS_Pr->SiS_CHOverScan) {
	    if(SiS_Pr->SiS_IF_DEF_CH70xx == 1) {
	       temp = SiS_GetReg(SiS_Pr->SiS_P3d4,0x35);
	       if((temp & TVOverScan) || (SiS_Pr->SiS_CHOverScan == 1)) {
		  SiS_Pr->SiS_TVMode |= TVSetCHOverScan;
	       }
	    } else if(SiS_Pr->SiS_IF_DEF_CH70xx == 2) {
	       temp = SiS_GetReg(SiS_Pr->SiS_P3d4,0x79);
	       if((temp & 0x80) || (SiS_Pr->SiS_CHOverScan == 1)) {
		  SiS_Pr->SiS_TVMode |= TVSetCHOverScan;
	       }
	    }
	    if(SiS_Pr->SiS_CHSOverScan) {
	       SiS_Pr->SiS_TVMode |= TVSetCHOverScan;
	    }
	 }
	 if(SiS_Pr->SiS_IF_DEF_CH70xx == 2) {
	    temp = SiS_GetReg(SiS_Pr->SiS_P3d4,0x38);
	    if(SiS_Pr->SiS_TVMode & TVSetPAL) {
	       if(temp & EnablePALM)      SiS_Pr->SiS_TVMode |= TVSetPALM;
	       else if(temp & EnablePALN) SiS_Pr->SiS_TVMode |= TVSetPALN;
	    } else {
	       if(temp & EnableNTSCJ) {
		  SiS_Pr->SiS_TVMode |= TVSetNTSCJ;
	       }
	    }
	 }
      }

   } else {  /* 661 and later */

      temp1 = SiS_GetReg(SiS_Pr->SiS_P3d4,0x35);
      if(temp1 & 0x01) {
	 SiS_Pr->SiS_TVMode |= TVSetPAL;
	 if(temp1 & 0x08) {
	    SiS_Pr->SiS_TVMode |= TVSetPALN;
	 } else if(temp1 & 0x04) {
	    if(SiS_Pr->SiS_VBType & VB_SISVB) {
	       SiS_Pr->SiS_TVMode &= ~TVSetPAL;
	    }
	    SiS_Pr->SiS_TVMode |= TVSetPALM;
	 }
      } else {
	 if(temp1 & 0x02) {
	    SiS_Pr->SiS_TVMode |= TVSetNTSCJ;
	 }
      }
      if(SiS_Pr->SiS_IF_DEF_CH70xx == 2) {
	 if(SiS_Pr->SiS_CHOverScan) {
	    if((temp1 & 0x10) || (SiS_Pr->SiS_CHOverScan == 1)) {
	       SiS_Pr->SiS_TVMode |= TVSetCHOverScan;
	    }
	 }
      }
      if(SiS_Pr->SiS_VBType & VB_SISVB) {
	 if(SiS_Pr->SiS_VBInfo & SetCRT2ToYPbPr525750) {
	    temp1 &= 0xe0;
	    if(temp1 == 0x00)      SiS_Pr->SiS_TVMode |= TVSetYPbPr525i;
	    else if(temp1 == 0x20) SiS_Pr->SiS_TVMode |= TVSetYPbPr525p;
	    else if(temp1 == 0x40) SiS_Pr->SiS_TVMode |= TVSetYPbPr750p;
	 } else if(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) {
	    SiS_Pr->SiS_TVMode |= (TVSetHiVision | TVSetPAL);
	 }
	 if(SiS_Pr->SiS_VBInfo & (SetCRT2ToYPbPr525750 | SetCRT2ToHiVision)) {
	    if(resinfo == SIS_RI_800x480 || resinfo == SIS_RI_1024x576 || resinfo == SIS_RI_1280x720) {
	       SiS_Pr->SiS_TVMode |= TVAspect169;
	    } else {
	       temp1 = SiS_GetReg(SiS_Pr->SiS_P3d4,0x39);
	       if(temp1 & 0x02) {
		  if(SiS_Pr->SiS_TVMode & (TVSetYPbPr750p | TVSetHiVision)) {
		     SiS_Pr->SiS_TVMode |= TVAspect169;
		  } else {
		     SiS_Pr->SiS_TVMode |= TVAspect43LB;
		  }
	       } else {
		  SiS_Pr->SiS_TVMode |= TVAspect43;
	       }
	    }
	 }
      }
   }

   if(SiS_Pr->SiS_VBInfo & SetCRT2ToSCART) SiS_Pr->SiS_TVMode |= TVSetPAL;

   if(SiS_Pr->SiS_VBType & VB_SISVB) {

      if(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) {
	 SiS_Pr->SiS_TVMode |= TVSetPAL;
	 SiS_Pr->SiS_TVMode &= ~(TVSetPALM | TVSetPALN | TVSetNTSCJ);
      } else if(SiS_Pr->SiS_VBInfo & SetCRT2ToYPbPr525750) {
	 if(SiS_Pr->SiS_TVMode & (TVSetYPbPr525i | TVSetYPbPr525p | TVSetYPbPr750p)) {
	    SiS_Pr->SiS_TVMode &= ~(TVSetPAL | TVSetNTSCJ | TVSetPALM | TVSetPALN);
	 }
      }

      if(SiS_Pr->SiS_VBInfo & SetInSlaveMode) {
	 if(!(SiS_Pr->SiS_VBInfo & SetNotSimuMode)) {
	    SiS_Pr->SiS_TVMode |= TVSetTVSimuMode;
	 }
      }

      if(!(SiS_Pr->SiS_TVMode & TVSetPAL)) {
	 if(resinfo == SIS_RI_1024x768) {
	    if(SiS_Pr->SiS_TVMode & TVSetYPbPr525p) {
	       SiS_Pr->SiS_TVMode |= TVSet525p1024;
	    } else if(!(SiS_Pr->SiS_TVMode & (TVSetHiVision | TVSetYPbPr750p))) {
	       SiS_Pr->SiS_TVMode |= TVSetNTSC1024;
	    }
	 }
      }

      SiS_Pr->SiS_TVMode |= TVRPLLDIV2XO;
      if((SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) &&
	 (SiS_Pr->SiS_VBInfo & SetInSlaveMode)) {
	 SiS_Pr->SiS_TVMode &= ~TVRPLLDIV2XO;
      } else if(SiS_Pr->SiS_TVMode & (TVSetYPbPr525p | TVSetYPbPr750p)) {
	 SiS_Pr->SiS_TVMode &= ~TVRPLLDIV2XO;
      } else if(!(SiS_Pr->SiS_VBType & VB_SIS30xBLV)) {
	 if(SiS_Pr->SiS_TVMode & TVSetTVSimuMode) {
	    SiS_Pr->SiS_TVMode &= ~TVRPLLDIV2XO;
	 }
      }

   }

   SiS_Pr->SiS_VBInfo &= ~SetPALTV;

#ifdef SIS_XORG_XF86
#ifdef TWDEBUG
   xf86DrvMsg(0, X_INFO, "(init301: TVMode %x, VBInfo %x)\n", SiS_Pr->SiS_TVMode, SiS_Pr->SiS_VBInfo);
#endif
#endif
}