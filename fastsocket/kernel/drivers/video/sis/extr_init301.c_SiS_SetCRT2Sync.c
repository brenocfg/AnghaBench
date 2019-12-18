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
struct SiS_Private {unsigned short CInfoFlag; int SiS_IF_DEF_LVDS; int SiS_VBInfo; int SiS_LCDInfo; scalar_t__ SiS_CustomT; scalar_t__ ChipType; int SiS_VBType; scalar_t__ SiS_LCDResInfo; int /*<<< orphan*/  SiS_Part2Port; int /*<<< orphan*/  SiS_Part1Port; scalar_t__ SiS_P3ca; scalar_t__ UseCustomMode; int /*<<< orphan*/  SiS_P3d4; scalar_t__ SiS_IF_DEF_DSTN; scalar_t__ SiS_IF_DEF_FSTN; scalar_t__ SiS_IF_DEF_TRUMPION; TYPE_1__* SiS_RefIndex; } ;
struct TYPE_2__ {unsigned short Ext_InfoFlag; } ;

/* Variables and functions */
 scalar_t__ CUT_BARCO1024 ; 
 scalar_t__ CUT_BARCO1366 ; 
 scalar_t__ CUT_CLEVO1400 ; 
 scalar_t__ CUT_COMPAQ1280 ; 
 scalar_t__ CUT_PANEL848 ; 
 scalar_t__ CUT_PANEL856 ; 
 int LCDPass11 ; 
 int LCDRGB18Bit ; 
 int LCDSync ; 
 scalar_t__ Panel_1280x1024 ; 
 scalar_t__ Panel_1400x1050 ; 
 scalar_t__ SIS_315H ; 
 int SetCRT2ToLCD ; 
 int SetCRT2ToLCDA ; 
 int SetCRT2ToRAMDAC ; 
 int SetCRT2ToTV ; 
 unsigned short SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 unsigned short SiS_GetRegByte (scalar_t__) ; 
 int /*<<< orphan*/  SiS_SetRegANDOR (int /*<<< orphan*/ ,int,int,unsigned short) ; 
 int VB_NoLCD ; 
 int VB_SIS30xBLV ; 
 int VB_SIS30xC ; 
 int VB_SISLVDS ; 
 int VB_SISVB ; 

__attribute__((used)) static void
SiS_SetCRT2Sync(struct SiS_Private *SiS_Pr, unsigned short ModeNo, unsigned short RefreshRateTableIndex)
{
   unsigned short tempah=0, tempbl, infoflag;

   tempbl = 0xC0;

   if(SiS_Pr->UseCustomMode) {
      infoflag = SiS_Pr->CInfoFlag;
   } else {
      infoflag = SiS_Pr->SiS_RefIndex[RefreshRateTableIndex].Ext_InfoFlag;
   }

   if(SiS_Pr->SiS_IF_DEF_LVDS == 1) {					/* LVDS */

      if(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) {
	 tempah = 0;
      } else if((SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) && (SiS_Pr->SiS_LCDInfo & LCDSync)) {
	 tempah = SiS_Pr->SiS_LCDInfo;
      } else tempah = infoflag >> 8;
      tempah &= 0xC0;
      tempah |= 0x20;
      if(!(SiS_Pr->SiS_LCDInfo & LCDRGB18Bit)) tempah |= 0x10;
      if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) {
	 if((SiS_Pr->SiS_CustomT == CUT_BARCO1366) ||
	    (SiS_Pr->SiS_CustomT == CUT_BARCO1024)) {
	    tempah |= 0xf0;
	 }
	 if( (SiS_Pr->SiS_IF_DEF_FSTN) ||
	     (SiS_Pr->SiS_IF_DEF_DSTN) ||
	     (SiS_Pr->SiS_IF_DEF_TRUMPION) ||
	     (SiS_Pr->SiS_CustomT == CUT_PANEL848) ||
	     (SiS_Pr->SiS_CustomT == CUT_PANEL856) ) {
	    tempah |= 0x30;
	 }
	 if( (SiS_Pr->SiS_IF_DEF_FSTN) ||
	     (SiS_Pr->SiS_IF_DEF_DSTN) ) {
	    tempah &= ~0xc0;
	 }
      }
      if(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) {
	 if(SiS_Pr->ChipType >= SIS_315H) {
	    tempah >>= 3;
	    tempah &= 0x18;
	    SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x13,0xE7,tempah);
	    /* Don't care about 12/18/24 bit mode - TV is via VGA, not PL */
	 } else {
	    SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x19,0x0F,0xe0);
	 }
      } else {
	 SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x19,0x0F,tempah);
      }

   } else if(SiS_Pr->SiS_VBType & VB_SISVB) {

      if(SiS_Pr->ChipType < SIS_315H) {

#ifdef SIS300  /* ---- 300 series --- */

	 if(SiS_Pr->SiS_VBType & VB_SIS30xBLV) {			/* 630 - 301B(-DH) */

	    tempah = infoflag >> 8;
	    tempbl = 0;
	    if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) {
	       if(SiS_Pr->SiS_LCDInfo & LCDSync) {
		  tempah = SiS_Pr->SiS_LCDInfo;
		  tempbl = (tempah >> 6) & 0x03;
	       }
	    }
	    tempah &= 0xC0;
	    tempah |= 0x20;
	    if(!(SiS_Pr->SiS_LCDInfo & LCDRGB18Bit)) tempah |= 0x10;
	    tempah |= 0xc0;
	    SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x19,0x0F,tempah);
	    if((SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) && (!(SiS_Pr->SiS_VBType & VB_NoLCD))) {
	       SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x1a,0xf0,tempbl);
	    }

	 } else {							/* 630 - 301 */

	    tempah = ((infoflag >> 8) & 0xc0) | 0x20;
	    if(!(SiS_Pr->SiS_LCDInfo & LCDRGB18Bit)) tempah |= 0x10;
	    SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x19,0x0F,tempah);

	 }

#endif /* SIS300 */

      } else {

#ifdef SIS315H  /* ------- 315 series ------ */

	 if(SiS_Pr->SiS_VBType & VB_SISLVDS) {	  		/* 315 - LVDS */

	    tempbl = 0;
	    if((SiS_Pr->SiS_CustomT == CUT_COMPAQ1280) &&
	       (SiS_Pr->SiS_LCDResInfo == Panel_1280x1024)) {
	       tempah = infoflag >> 8;
	       if(SiS_Pr->SiS_LCDInfo & LCDSync) {
		 tempbl = ((SiS_Pr->SiS_LCDInfo & 0xc0) >> 6);
	       }
	    } else if((SiS_Pr->SiS_CustomT == CUT_CLEVO1400)  &&
		      (SiS_Pr->SiS_LCDResInfo == Panel_1400x1050)) {
	       tempah = infoflag >> 8;
	       tempbl = 0x03;
	    } else {
	       tempah = SiS_GetReg(SiS_Pr->SiS_P3d4,0x37);
	       tempbl = (tempah >> 6) & 0x03;
	       tempbl |= 0x08;
	       if(!(SiS_Pr->SiS_LCDInfo & LCDRGB18Bit)) tempbl |= 0x04;
	    }
	    tempah &= 0xC0;
	    tempah |= 0x20;
	    if(!(SiS_Pr->SiS_LCDInfo & LCDRGB18Bit)) tempah |= 0x10;
	    if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)   tempah |= 0xc0;
	    SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x19,0x0F,tempah);
	    if(SiS_Pr->SiS_VBType & VB_SIS30xBLV) {
	       if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) {
		  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x1a,0xf0,tempbl);
	       }
	    }

	 } else {							/* 315 - TMDS */

	    tempah = tempbl = infoflag >> 8;
	    if(!SiS_Pr->UseCustomMode) {
	       tempbl = 0;
	       if((SiS_Pr->SiS_VBType & VB_SIS30xC) && (SiS_Pr->SiS_VBInfo & SetCRT2ToRAMDAC)) {
		  if(ModeNo <= 0x13) {
		     tempah = SiS_GetRegByte((SiS_Pr->SiS_P3ca+0x02));
		  }
	       }
	       if(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) {
		  if(!(SiS_Pr->SiS_LCDInfo & LCDPass11)) {
		    if(SiS_Pr->SiS_LCDInfo & LCDSync) {
		       tempah = SiS_Pr->SiS_LCDInfo;
		       tempbl = (tempah >> 6) & 0x03;
		    }
		  }
	       }
	    }
	    tempah &= 0xC0;
	    tempah |= 0x20;
	    if(!(SiS_Pr->SiS_LCDInfo & LCDRGB18Bit)) tempah |= 0x10;
	    if(SiS_Pr->SiS_VBType & VB_NoLCD) {
	       /* Imitate BIOS bug */
	       if(SiS_Pr->SiS_VBInfo & SetCRT2ToTV)  tempah |= 0xc0;
	    }
	    if((SiS_Pr->SiS_VBType & VB_SIS30xC) && (SiS_Pr->SiS_VBInfo & SetCRT2ToRAMDAC)) {
	       tempah >>= 3;
	       tempah &= 0x18;
	       SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x13,0xe7,tempah);
	    } else {
	       SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x19,0x0F,tempah);
	       if(SiS_Pr->SiS_VBType & VB_SIS30xBLV) {
		  if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) {
		     SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x1a,0xf0,tempbl);
		  }
	       }
	    }

         }
#endif  /* SIS315H */
      }
   }
}