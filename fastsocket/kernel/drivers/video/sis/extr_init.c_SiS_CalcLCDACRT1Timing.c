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
struct SiS_Private {unsigned short SiS_VGAHDE; int SiS_LCDInfo; unsigned short CHDisplay; unsigned short CHBlankStart; unsigned short CVDisplay; unsigned short SiS_VGAVDE; unsigned short CVBlankStart; scalar_t__ ChipType; unsigned short SiS_VGAHT; unsigned short PanelHT; unsigned short PanelXRes; unsigned short CHTotal; unsigned short CHBlankEnd; int CHSyncStart; int PanelHRS; int CHSyncEnd; int PanelHRE; unsigned short PanelVT; unsigned short PanelYRes; scalar_t__ SiS_LCDResInfo; unsigned short SiS_VGAVT; unsigned short CVTotal; unsigned short CVBlankEnd; unsigned short CVSyncStart; unsigned short CVSyncEnd; int* CCRT1CRTC; int /*<<< orphan*/  SiS_P3d4; int /*<<< orphan*/  SiS_P3c4; scalar_t__ PanelVRE; scalar_t__ PanelVRS; } ;

/* Variables and functions */
 int DontExpandLCD ; 
 unsigned short DoubleScanMode ; 
 unsigned short HalfDCLK ; 
 int LCDPass11 ; 
 scalar_t__ Panel_1024x600 ; 
 scalar_t__ Panel_1024x768 ; 
 scalar_t__ Panel_800x600 ; 
 scalar_t__ SIS_315H ; 
 int /*<<< orphan*/  SiS_CalcCRRegisters (struct SiS_Private*,int) ; 
 unsigned short SiS_GetModeFlag (struct SiS_Private*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegAND (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegANDOR (int /*<<< orphan*/ ,int,int,unsigned short) ; 
 int /*<<< orphan*/  X_INFO ; 
 int /*<<< orphan*/  xf86DrvMsg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 

void
SiS_CalcLCDACRT1Timing(struct SiS_Private *SiS_Pr, unsigned short ModeNo,
		unsigned short ModeIdIndex)
{
   unsigned short modeflag, tempax, tempbx = 0, remaining = 0;
   unsigned short VGAHDE = SiS_Pr->SiS_VGAHDE;
   int i, j;

   /* 1:1 data: use data set by setcrt1crtc() */
   if(SiS_Pr->SiS_LCDInfo & LCDPass11) return;

   modeflag = SiS_GetModeFlag(SiS_Pr, ModeNo, ModeIdIndex);

   if(modeflag & HalfDCLK) VGAHDE >>= 1;

   SiS_Pr->CHDisplay = VGAHDE;
   SiS_Pr->CHBlankStart = VGAHDE;

   SiS_Pr->CVDisplay = SiS_Pr->SiS_VGAVDE;
   SiS_Pr->CVBlankStart = SiS_Pr->SiS_VGAVDE;

   if(SiS_Pr->ChipType < SIS_315H) {
#ifdef SIS300
      tempbx = SiS_Pr->SiS_VGAHT;
      if(SiS_Pr->SiS_LCDInfo & DontExpandLCD) {
         tempbx = SiS_Pr->PanelHT;
      }
      if(modeflag & HalfDCLK) tempbx >>= 1;
      remaining = tempbx % 8;
#endif
   } else {
#ifdef SIS315H
      /* OK for LCDA, LVDS */
      tempbx = SiS_Pr->PanelHT - SiS_Pr->PanelXRes;
      tempax = SiS_Pr->SiS_VGAHDE;  /* not /2 ! */
      if(SiS_Pr->SiS_LCDInfo & DontExpandLCD) {
         tempax = SiS_Pr->PanelXRes;
      }
      tempbx += tempax;
      if(modeflag & HalfDCLK) tempbx -= VGAHDE;
#endif
   }
   SiS_Pr->CHTotal = SiS_Pr->CHBlankEnd = tempbx;

   if(SiS_Pr->ChipType < SIS_315H) {
#ifdef SIS300
      if(SiS_Pr->SiS_VGAHDE == SiS_Pr->PanelXRes) {
	 SiS_Pr->CHSyncStart = SiS_Pr->SiS_VGAHDE + ((SiS_Pr->PanelHRS + 1) & ~1);
	 SiS_Pr->CHSyncEnd = SiS_Pr->CHSyncStart + SiS_Pr->PanelHRE;
	 if(modeflag & HalfDCLK) {
	    SiS_Pr->CHSyncStart >>= 1;
	    SiS_Pr->CHSyncEnd >>= 1;
	 }
      } else if(SiS_Pr->SiS_LCDInfo & DontExpandLCD) {
	 tempax = (SiS_Pr->PanelXRes - SiS_Pr->SiS_VGAHDE) >> 1;
	 tempbx = (SiS_Pr->PanelHRS + 1) & ~1;
	 if(modeflag & HalfDCLK) {
	    tempax >>= 1;
	    tempbx >>= 1;
	 }
	 SiS_Pr->CHSyncStart = (VGAHDE + tempax + tempbx + 7) & ~7;
	 tempax = SiS_Pr->PanelHRE + 7;
	 if(modeflag & HalfDCLK) tempax >>= 1;
	 SiS_Pr->CHSyncEnd = (SiS_Pr->CHSyncStart + tempax) & ~7;
      } else {
	 SiS_Pr->CHSyncStart = SiS_Pr->SiS_VGAHDE;
	 if(modeflag & HalfDCLK) {
	    SiS_Pr->CHSyncStart >>= 1;
	    tempax = ((SiS_Pr->CHTotal - SiS_Pr->CHSyncStart) / 3) << 1;
	    SiS_Pr->CHSyncEnd = SiS_Pr->CHSyncStart + tempax;
	 } else {
	    SiS_Pr->CHSyncEnd = (SiS_Pr->CHSyncStart + (SiS_Pr->CHTotal / 10) + 7) & ~7;
	    SiS_Pr->CHSyncStart += 8;
	 }
      }
#endif
   } else {
#ifdef SIS315H
      tempax = VGAHDE;
      if(SiS_Pr->SiS_LCDInfo & DontExpandLCD) {
	 tempbx = SiS_Pr->PanelXRes;
	 if(modeflag & HalfDCLK) tempbx >>= 1;
	 tempax += ((tempbx - tempax) >> 1);
      }
      tempax += SiS_Pr->PanelHRS;
      SiS_Pr->CHSyncStart = tempax;
      tempax += SiS_Pr->PanelHRE;
      SiS_Pr->CHSyncEnd = tempax;
#endif
   }

   tempbx = SiS_Pr->PanelVT - SiS_Pr->PanelYRes;
   tempax = SiS_Pr->SiS_VGAVDE;
   if(SiS_Pr->SiS_LCDInfo & DontExpandLCD) {
      tempax = SiS_Pr->PanelYRes;
   } else if(SiS_Pr->ChipType < SIS_315H) {
#ifdef SIS300
      /* Stupid hack for 640x400/320x200 */
      if(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) {
	 if((tempax + tempbx) == 438) tempbx += 16;
      } else if((SiS_Pr->SiS_LCDResInfo == Panel_800x600) ||
		(SiS_Pr->SiS_LCDResInfo == Panel_1024x600)) {
	 tempax = 0;
	 tempbx = SiS_Pr->SiS_VGAVT;
      }
#endif
   }
   SiS_Pr->CVTotal = SiS_Pr->CVBlankEnd = tempbx + tempax;

   tempax = SiS_Pr->SiS_VGAVDE;
   if(SiS_Pr->SiS_LCDInfo & DontExpandLCD) {
      tempax += (SiS_Pr->PanelYRes - tempax) >> 1;
   }
   tempax += SiS_Pr->PanelVRS;
   SiS_Pr->CVSyncStart = tempax;
   tempax += SiS_Pr->PanelVRE;
   SiS_Pr->CVSyncEnd = tempax;
   if(SiS_Pr->ChipType < SIS_315H) {
      SiS_Pr->CVSyncStart--;
      SiS_Pr->CVSyncEnd--;
   }

   SiS_CalcCRRegisters(SiS_Pr, 8);
   SiS_Pr->CCRT1CRTC[15] &= ~0xF8;
   SiS_Pr->CCRT1CRTC[15] |= (remaining << 4);
   SiS_Pr->CCRT1CRTC[16] &= ~0xE0;

   SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x11,0x7f);

   for(i = 0, j = 0; i <= 7; i++, j++) {
      SiS_SetReg(SiS_Pr->SiS_P3d4,j,SiS_Pr->CCRT1CRTC[i]);
   }
   for(j = 0x10; i <= 10; i++, j++) {
      SiS_SetReg(SiS_Pr->SiS_P3d4,j,SiS_Pr->CCRT1CRTC[i]);
   }
   for(j = 0x15; i <= 12; i++, j++) {
      SiS_SetReg(SiS_Pr->SiS_P3d4,j,SiS_Pr->CCRT1CRTC[i]);
   }
   for(j = 0x0A; i <= 15; i++, j++) {
      SiS_SetReg(SiS_Pr->SiS_P3c4,j,SiS_Pr->CCRT1CRTC[i]);
   }

   tempax = SiS_Pr->CCRT1CRTC[16] & 0xE0;
   SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x0E,0x1F,tempax);

   tempax = (SiS_Pr->CCRT1CRTC[16] & 0x01) << 5;
   if(modeflag & DoubleScanMode) tempax |= 0x80;
   SiS_SetRegANDOR(SiS_Pr->SiS_P3d4,0x09,0x5F,tempax);

#ifdef SIS_XORG_XF86
#ifdef TWDEBUG
   xf86DrvMsg(0, X_INFO, "%d %d %d %d  %d %d %d %d  (%d %d %d %d)\n",
	SiS_Pr->CHDisplay, SiS_Pr->CHSyncStart, SiS_Pr->CHSyncEnd, SiS_Pr->CHTotal,
	SiS_Pr->CVDisplay, SiS_Pr->CVSyncStart, SiS_Pr->CVSyncEnd, SiS_Pr->CVTotal,
	SiS_Pr->CHBlankStart, SiS_Pr->CHBlankEnd, SiS_Pr->CVBlankStart, SiS_Pr->CVBlankEnd);
   xf86DrvMsg(0, X_INFO, " {{0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,\n",
	SiS_Pr->CCRT1CRTC[0], SiS_Pr->CCRT1CRTC[1],
	SiS_Pr->CCRT1CRTC[2], SiS_Pr->CCRT1CRTC[3],
	SiS_Pr->CCRT1CRTC[4], SiS_Pr->CCRT1CRTC[5],
	SiS_Pr->CCRT1CRTC[6], SiS_Pr->CCRT1CRTC[7]);
   xf86DrvMsg(0, X_INFO, "   0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,\n",
	SiS_Pr->CCRT1CRTC[8], SiS_Pr->CCRT1CRTC[9],
	SiS_Pr->CCRT1CRTC[10], SiS_Pr->CCRT1CRTC[11],
	SiS_Pr->CCRT1CRTC[12], SiS_Pr->CCRT1CRTC[13],
	SiS_Pr->CCRT1CRTC[14], SiS_Pr->CCRT1CRTC[15]);
   xf86DrvMsg(0, X_INFO, "   0x%02x}},\n", SiS_Pr->CCRT1CRTC[16]);
#endif
#endif
}