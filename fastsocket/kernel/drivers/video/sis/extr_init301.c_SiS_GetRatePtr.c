#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct SiS_Private {scalar_t__ SiS_IF_DEF_CH70xx; int SiS_VBInfo; int SiS_SelectCRT2Rate; int SiS_SetFlag; int SiS_VBType; int SiS_LCDInfo; scalar_t__ ChipType; unsigned short SiS_ModeType; TYPE_3__* SiS_RefIndex; TYPE_2__* SiS_EModeIDTable; int /*<<< orphan*/  SiS_P3d4; TYPE_1__* SiS_SModeIDTable; } ;
struct TYPE_6__ {unsigned short ModeID; unsigned short Ext_InfoFlag; } ;
struct TYPE_5__ {unsigned short Ext_ModeFlag; unsigned short REFindex; int Ext_VESAID; } ;
struct TYPE_4__ {unsigned short St_ModeFlag; } ;

/* Variables and functions */
 int DisableCRT2Display ; 
 int DontExpandLCD ; 
 int DriverMode ; 
 unsigned short HalfDCLK ; 
 unsigned short InterlaceMode ; 
 unsigned short ModeTypeMask ; 
 int ProgrammingCRT2 ; 
 scalar_t__ SIS_315H ; 
 int SetCRT2ToLCD ; 
 int SetCRT2ToLCDA ; 
 int SetCRT2ToRAMDAC ; 
 int SetCRT2ToTV ; 
 int SetInSlaveMode ; 
 int /*<<< orphan*/  SiS_AdjustCRT2Rate (struct SiS_Private*,unsigned short,unsigned short,unsigned short,unsigned short*) ; 
 size_t SiS_GetBIOSLCDResInfo (struct SiS_Private*) ; 
 int SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 int VB_NoLCD ; 
 int VB_SISVB ; 

unsigned short
SiS_GetRatePtr(struct SiS_Private *SiS_Pr, unsigned short ModeNo, unsigned short ModeIdIndex)
{
   unsigned short RRTI,i,backup_i;
   unsigned short modeflag,index,temp,backupindex;
   static const unsigned short LCDRefreshIndex[] = {
		0x00, 0x00, 0x01, 0x01,
		0x01, 0x01, 0x01, 0x01,
		0x01, 0x01, 0x01, 0x01,
		0x01, 0x01, 0x01, 0x01,
		0x00, 0x00, 0x00, 0x00
   };

   /* Do NOT check for UseCustomMode here, will skrew up FIFO */
   if(ModeNo == 0xfe) return 0;

   if(ModeNo <= 0x13) {
      modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
   } else {
      modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
   }

   if(SiS_Pr->SiS_IF_DEF_CH70xx != 0) {
      if(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) {
	 if(modeflag & HalfDCLK) return 0;
      }
   }

   if(ModeNo < 0x14) return 0xFFFF;

   index = (SiS_GetReg(SiS_Pr->SiS_P3d4,0x33) >> SiS_Pr->SiS_SelectCRT2Rate) & 0x0F;
   backupindex = index;

   if(index > 0) index--;

   if(SiS_Pr->SiS_SetFlag & ProgrammingCRT2) {
      if(SiS_Pr->SiS_VBType & VB_SISVB) {
	 if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) {
	    if(SiS_Pr->SiS_VBType & VB_NoLCD)		 index = 0;
	    else if(SiS_Pr->SiS_LCDInfo & DontExpandLCD) index = backupindex = 0;
	 }
	 if(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) {
	    if(!(SiS_Pr->SiS_VBType & VB_NoLCD)) {
	       temp = LCDRefreshIndex[SiS_GetBIOSLCDResInfo(SiS_Pr)];
	       if(index > temp) index = temp;
	    }
	 }
      } else {
	 if(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) index = 0;
	 if(SiS_Pr->SiS_IF_DEF_CH70xx != 0) {
	    if(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) index = 0;
	 }
      }
   }

   RRTI = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].REFindex;
   ModeNo = SiS_Pr->SiS_RefIndex[RRTI].ModeID;

   if(SiS_Pr->ChipType >= SIS_315H) {
      if(!(SiS_Pr->SiS_VBInfo & DriverMode)) {
	 if( (SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_VESAID == 0x105) ||
	     (SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_VESAID == 0x107) ) {
	    if(backupindex <= 1) RRTI++;
	 }
      }
   }

   i = 0;
   do {
      if(SiS_Pr->SiS_RefIndex[RRTI + i].ModeID != ModeNo) break;
      temp = SiS_Pr->SiS_RefIndex[RRTI + i].Ext_InfoFlag;
      temp &= ModeTypeMask;
      if(temp < SiS_Pr->SiS_ModeType) break;
      i++;
      index--;
   } while(index != 0xFFFF);

   if(!(SiS_Pr->SiS_VBInfo & SetCRT2ToRAMDAC)) {
      if(SiS_Pr->SiS_VBInfo & SetInSlaveMode) {
	 temp = SiS_Pr->SiS_RefIndex[RRTI + i - 1].Ext_InfoFlag;
	 if(temp & InterlaceMode) i++;
      }
   }

   i--;

   if((SiS_Pr->SiS_SetFlag & ProgrammingCRT2) && (!(SiS_Pr->SiS_VBInfo & DisableCRT2Display))) {
      backup_i = i;
      if(!(SiS_AdjustCRT2Rate(SiS_Pr, ModeNo, ModeIdIndex, RRTI, &i))) {
	 i = backup_i;
      }
   }

   return (RRTI + i);
}