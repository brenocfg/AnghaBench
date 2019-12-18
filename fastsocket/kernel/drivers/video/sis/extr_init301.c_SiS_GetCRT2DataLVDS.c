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
struct SiS_Private {int SiS_VBType; int SiS_RVBHCMAX; int SiS_RVBHCFACT; int SiS_RVBHRS; int SiS_VBInfo; unsigned short SiS_IF_DEF_LVDS; int SiS_LCDInfo; int SiS_SetFlag; int SiS_HDE; int PanelXRes; int SiS_VDE; int PanelYRes; scalar_t__ SiS_CustomT; int /*<<< orphan*/  SiS_VT; int /*<<< orphan*/  SiS_HT; int /*<<< orphan*/  SiS_VGAVT; int /*<<< orphan*/  SiS_VGAHT; struct SiS_LVDSData* SiS_CHTVSOPALData; struct SiS_LVDSData* SiS_CHTVOPALNData; struct SiS_LVDSData* SiS_CHTVUPALNData; struct SiS_LVDSData* SiS_CHTVOPALMData; struct SiS_LVDSData* SiS_CHTVUPALMData; struct SiS_LVDSData* SiS_CHTVOPALData; struct SiS_LVDSData* SiS_CHTVUPALData; struct SiS_LVDSData* SiS_CHTVONTSCData; struct SiS_LVDSData* SiS_CHTVUNTSCData; struct SiS_LVDSData* SiS_LVDS848x480Data_2; struct SiS_LVDSData* SiS_LVDS848x480Data_1; struct SiS_LVDSData* SiS_LVDSBARCO1024Data_1; struct SiS_LVDSData* SiS_LVDSBARCO1366Data_2; struct SiS_LVDSData* SiS_LVDSBARCO1366Data_1; struct SiS_LVDSData* SiS_LVDS1024x768Data_1; struct SiS_LVDSData* SiS_LVDS1024x600Data_1; struct SiS_LVDSData* SiS_LVDS800x600Data_1; struct SiS_LVDSData* SiS_LVDS640x480Data_1; struct SiS_LVDSData* SiS_LVDS320x240Data_2; struct SiS_LVDSData* SiS_LVDS320x240Data_1; scalar_t__ SiS_RVBHRS2; scalar_t__ SiS_RY4COE; scalar_t__ SiS_RY3COE; scalar_t__ SiS_RY2COE; scalar_t__ SiS_RY1COE; scalar_t__ SiS_NewFlickerMode; } ;
struct SiS_LVDSData {int /*<<< orphan*/  LCDVT; int /*<<< orphan*/  LCDHT; int /*<<< orphan*/  VGAVT; int /*<<< orphan*/  VGAHT; } ;

/* Variables and functions */
 scalar_t__ CUT_BARCO1366 ; 
 int DontExpandLCD ; 
 int LCDPass11 ; 
 int SetCRT2ToLCD ; 
 int SetCRT2ToLCDA ; 
 int SetDOSMode ; 
 int /*<<< orphan*/  SiS_CalcLCDACRT1Timing (struct SiS_Private*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_CalcPanelLinkTiming (struct SiS_Private*,unsigned short,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_GetCRT2Ptr (struct SiS_Private*,unsigned short,unsigned short,unsigned short,unsigned short*,unsigned short*) ; 
 int /*<<< orphan*/  SiS_GetCRT2ResInfo (struct SiS_Private*,unsigned short,unsigned short) ; 
 int VB_NoLCD ; 
 int VB_SISVB ; 

__attribute__((used)) static void
SiS_GetCRT2DataLVDS(struct SiS_Private *SiS_Pr, unsigned short ModeNo, unsigned short ModeIdIndex,
                    unsigned short RefreshRateTableIndex)
{
   unsigned short CRT2Index, ResIndex, backup;
   const struct SiS_LVDSData *LVDSData = NULL;

   SiS_GetCRT2ResInfo(SiS_Pr, ModeNo, ModeIdIndex);

   if(SiS_Pr->SiS_VBType & VB_SISVB) {
      SiS_Pr->SiS_RVBHCMAX  = 1;
      SiS_Pr->SiS_RVBHCFACT = 1;
      SiS_Pr->SiS_NewFlickerMode = 0;
      SiS_Pr->SiS_RVBHRS = 50;
      SiS_Pr->SiS_RY1COE = 0;
      SiS_Pr->SiS_RY2COE = 0;
      SiS_Pr->SiS_RY3COE = 0;
      SiS_Pr->SiS_RY4COE = 0;
      SiS_Pr->SiS_RVBHRS2 = 0;
   }

   if((SiS_Pr->SiS_VBType & VB_SISVB) && (SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)) {

#ifdef SIS315H
      SiS_CalcPanelLinkTiming(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
      SiS_CalcLCDACRT1Timing(SiS_Pr, ModeNo, ModeIdIndex);
#endif

   } else {

      /* 301BDH needs LVDS Data */
      backup = SiS_Pr->SiS_IF_DEF_LVDS;
      if((SiS_Pr->SiS_VBType & VB_NoLCD) && (SiS_Pr->SiS_VBInfo & SetCRT2ToLCD)) {
	 SiS_Pr->SiS_IF_DEF_LVDS = 1;
      }

      SiS_GetCRT2Ptr(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex,
                     		            &CRT2Index, &ResIndex);

      SiS_Pr->SiS_IF_DEF_LVDS = backup;

      switch(CRT2Index) {
	 case 10: LVDSData = SiS_Pr->SiS_LVDS320x240Data_1;    break;
	 case 14: LVDSData = SiS_Pr->SiS_LVDS320x240Data_2;    break;
	 case 12: LVDSData = SiS_Pr->SiS_LVDS640x480Data_1;    break;
	 case 16: LVDSData = SiS_Pr->SiS_LVDS800x600Data_1;    break;
	 case 18: LVDSData = SiS_Pr->SiS_LVDS1024x600Data_1;   break;
	 case 20: LVDSData = SiS_Pr->SiS_LVDS1024x768Data_1;   break;
#ifdef SIS300
	 case 80: LVDSData = SiS_Pr->SiS_LVDSBARCO1366Data_1;  break;
	 case 81: LVDSData = SiS_Pr->SiS_LVDSBARCO1366Data_2;  break;
	 case 82: LVDSData = SiS_Pr->SiS_LVDSBARCO1024Data_1;  break;
	 case 84: LVDSData = SiS_Pr->SiS_LVDS848x480Data_1;    break;
	 case 85: LVDSData = SiS_Pr->SiS_LVDS848x480Data_2;    break;
#endif
	 case 90: LVDSData = SiS_Pr->SiS_CHTVUNTSCData;        break;
	 case 91: LVDSData = SiS_Pr->SiS_CHTVONTSCData;        break;
	 case 92: LVDSData = SiS_Pr->SiS_CHTVUPALData;         break;
	 case 93: LVDSData = SiS_Pr->SiS_CHTVOPALData;         break;
	 case 94: LVDSData = SiS_Pr->SiS_CHTVUPALMData;        break;
	 case 95: LVDSData = SiS_Pr->SiS_CHTVOPALMData;        break;
	 case 96: LVDSData = SiS_Pr->SiS_CHTVUPALNData;        break;
	 case 97: LVDSData = SiS_Pr->SiS_CHTVOPALNData;        break;
	 case 99: LVDSData = SiS_Pr->SiS_CHTVSOPALData;	       break;
      }

      if(LVDSData) {
	 SiS_Pr->SiS_VGAHT = (LVDSData+ResIndex)->VGAHT;
	 SiS_Pr->SiS_VGAVT = (LVDSData+ResIndex)->VGAVT;
	 SiS_Pr->SiS_HT    = (LVDSData+ResIndex)->LCDHT;
	 SiS_Pr->SiS_VT    = (LVDSData+ResIndex)->LCDVT;
      } else {
	 SiS_CalcPanelLinkTiming(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
      }

      if( (!(SiS_Pr->SiS_VBType & VB_SISVB)) &&
	  (SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) &&
	  (!(SiS_Pr->SiS_LCDInfo & LCDPass11)) ) {
	 if( (!(SiS_Pr->SiS_LCDInfo & DontExpandLCD)) ||
	     (SiS_Pr->SiS_SetFlag & SetDOSMode) ) {
	    SiS_Pr->SiS_HDE = SiS_Pr->PanelXRes;
            SiS_Pr->SiS_VDE = SiS_Pr->PanelYRes;
#ifdef SIS300
	    if(SiS_Pr->SiS_CustomT == CUT_BARCO1366) {
	       if(ResIndex < 0x08) {
		  SiS_Pr->SiS_HDE = 1280;
		  SiS_Pr->SiS_VDE = 1024;
	       }
	    }
#endif
         }
      }
   }
}