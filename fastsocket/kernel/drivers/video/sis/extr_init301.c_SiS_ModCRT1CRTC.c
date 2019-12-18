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
struct SiS_Private {scalar_t__ SiS_CustomT; int SiS_VBInfo; int SiS_VBType; int SiS_LCDInfo; scalar_t__ ChipType; int SiS_SetFlag; int /*<<< orphan*/  SiS_P3d4; TYPE_2__* SiS_EModeIDTable; TYPE_1__* SiS_SModeIDTable; int /*<<< orphan*/  SiS_P3c4; struct SiS_LVDSCRT1Data* SiS_CHTVCRT1SOPAL; struct SiS_LVDSCRT1Data* SiS_CHTVCRT1OPAL; struct SiS_LVDSCRT1Data* SiS_CHTVCRT1UPAL; struct SiS_LVDSCRT1Data* SiS_CHTVCRT1ONTSC; struct SiS_LVDSCRT1Data* SiS_CHTVCRT1UNTSC; struct SiS_LVDSCRT1Data* SiS_LVDSCRT11024x600_2_H; struct SiS_LVDSCRT1Data* SiS_LVDSCRT11024x600_2; struct SiS_LVDSCRT1Data* SiS_LVDSCRT11024x600_1_H; struct SiS_LVDSCRT1Data* SiS_LVDSCRT11024x600_1; struct SiS_LVDSCRT1Data* SiS_LVDSCRT1640x480_1_H; struct SiS_LVDSCRT1Data* SiS_LVDSCRT1640x480_1; struct SiS_LVDSCRT1Data* SiS_LVDSCRT1320x240_3_H; struct SiS_LVDSCRT1Data* SiS_LVDSCRT1320x240_3; struct SiS_LVDSCRT1Data* SiS_LVDSCRT1320x240_2_H; struct SiS_LVDSCRT1Data* SiS_LVDSCRT1320x240_2; struct SiS_LVDSCRT1Data* SiS_LVDSCRT1320x240_1; scalar_t__ SiS_IF_DEF_LVDS; } ;
struct SiS_LVDSCRT1Data {unsigned short* CR; } ;
struct TYPE_4__ {unsigned short Ext_ModeFlag; } ;
struct TYPE_3__ {unsigned short St_ModeFlag; } ;

/* Variables and functions */
 scalar_t__ CUT_BARCO1024 ; 
 scalar_t__ CUT_BARCO1366 ; 
 scalar_t__ CUT_PANEL848 ; 
 scalar_t__ CUT_PANEL856 ; 
 unsigned short DoubleScanMode ; 
 int LCDPass11 ; 
 scalar_t__ SIS_315H ; 
 int SetCRT2ToLCDA ; 
 int SetDOSMode ; 
 int SetInSlaveMode ; 
 int /*<<< orphan*/  SiS_CalcLCDACRT1Timing (struct SiS_Private*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_GetLVDSCRT1Ptr (struct SiS_Private*,unsigned short,unsigned short,unsigned short,unsigned short*,unsigned short*) ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,unsigned short const,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetRegAND (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegANDOR (int /*<<< orphan*/ ,int,int,unsigned short) ; 
 int VB_SISVB ; 

__attribute__((used)) static void
SiS_ModCRT1CRTC(struct SiS_Private *SiS_Pr, unsigned short ModeNo, unsigned short ModeIdIndex,
                unsigned short RefreshRateTableIndex)
{
  unsigned short tempah, i, modeflag, j, ResIndex, DisplayType;
  const struct SiS_LVDSCRT1Data *LVDSCRT1Ptr=NULL;
  static const unsigned short CRIdx[] = {
	0x00, 0x02, 0x03, 0x04, 0x05, 0x06,
	0x07, 0x10, 0x11, 0x15, 0x16
  };

  if((SiS_Pr->SiS_CustomT == CUT_BARCO1366) ||
     (SiS_Pr->SiS_CustomT == CUT_BARCO1024) ||
     (SiS_Pr->SiS_CustomT == CUT_PANEL848)  ||
     (SiS_Pr->SiS_CustomT == CUT_PANEL856) )
     return;

  if(SiS_Pr->SiS_IF_DEF_LVDS) {
     if(!(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)) {
        if(!(SiS_Pr->SiS_VBInfo & SetInSlaveMode)) return;
     }
  } else if(SiS_Pr->SiS_VBType & VB_SISVB) {
     if(!(SiS_Pr->SiS_VBInfo & SetInSlaveMode)) return;
  } else return;

  if(SiS_Pr->SiS_LCDInfo & LCDPass11) return;

  if(SiS_Pr->ChipType < SIS_315H) {
     if(SiS_Pr->SiS_SetFlag & SetDOSMode) return;
  }

  if(!(SiS_GetLVDSCRT1Ptr(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex,
                          &ResIndex, &DisplayType))) {
     return;
  }

  switch(DisplayType) {
    case 50: LVDSCRT1Ptr = SiS_Pr->SiS_LVDSCRT1320x240_1;           break; /* xSTN */
    case 14: LVDSCRT1Ptr = SiS_Pr->SiS_LVDSCRT1320x240_2;           break; /* xSTN */
    case 15: LVDSCRT1Ptr = SiS_Pr->SiS_LVDSCRT1320x240_2_H;         break; /* xSTN */
    case 18: LVDSCRT1Ptr = SiS_Pr->SiS_LVDSCRT1320x240_3;           break; /* xSTN */
    case 19: LVDSCRT1Ptr = SiS_Pr->SiS_LVDSCRT1320x240_3_H;         break; /* xSTN */
    case 10: LVDSCRT1Ptr = SiS_Pr->SiS_LVDSCRT1640x480_1;           break;
    case 11: LVDSCRT1Ptr = SiS_Pr->SiS_LVDSCRT1640x480_1_H;         break;
#if 0 /* Works better with calculated numbers */
    case 26: LVDSCRT1Ptr = SiS_Pr->SiS_LVDSCRT11024x600_1;          break;
    case 27: LVDSCRT1Ptr = SiS_Pr->SiS_LVDSCRT11024x600_1_H;        break;
    case 28: LVDSCRT1Ptr = SiS_Pr->SiS_LVDSCRT11024x600_2;          break;
    case 29: LVDSCRT1Ptr = SiS_Pr->SiS_LVDSCRT11024x600_2_H;        break;
#endif
    case 80: LVDSCRT1Ptr = SiS_Pr->SiS_CHTVCRT1UNTSC;               break;
    case 81: LVDSCRT1Ptr = SiS_Pr->SiS_CHTVCRT1ONTSC;               break;
    case 82: LVDSCRT1Ptr = SiS_Pr->SiS_CHTVCRT1UPAL;                break;
    case 83: LVDSCRT1Ptr = SiS_Pr->SiS_CHTVCRT1OPAL;                break;
    case 84: LVDSCRT1Ptr = SiS_Pr->SiS_CHTVCRT1SOPAL;               break;
  }

  if(LVDSCRT1Ptr) {

     SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x11,0x7f);

     for(i = 0; i <= 10; i++) {
        tempah = (LVDSCRT1Ptr + ResIndex)->CR[i];
        SiS_SetReg(SiS_Pr->SiS_P3d4,CRIdx[i],tempah);
     }

     for(i = 0x0A, j = 11; i <= 0x0C; i++, j++) {
        tempah = (LVDSCRT1Ptr + ResIndex)->CR[j];
        SiS_SetReg(SiS_Pr->SiS_P3c4,i,tempah);
     }

     tempah = (LVDSCRT1Ptr + ResIndex)->CR[14] & 0xE0;
     SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x0E,0x1f,tempah);

     if(ModeNo <= 0x13) modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
     else               modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;

     tempah = ((LVDSCRT1Ptr + ResIndex)->CR[14] & 0x01) << 5;
     if(modeflag & DoubleScanMode) tempah |= 0x80;
     SiS_SetRegANDOR(SiS_Pr->SiS_P3d4,0x09,~0x020,tempah);

  } else {

     SiS_CalcLCDACRT1Timing(SiS_Pr, ModeNo, ModeIdIndex);

  }
}