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
struct SiS_Private {int SiS_VBType; int SiS_VBInfo; int /*<<< orphan*/  SiS_P3c4; TYPE_1__* SiS_StandTable; scalar_t__ SiS_IF_DEF_LVDS; } ;
struct TYPE_2__ {int* SR; } ;

/* Variables and functions */
 int SetCRT2ToLCD ; 
 int SetCRT2ToLCDA ; 
 int SetCRT2ToTV ; 
 int SetInSlaveMode ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,unsigned char) ; 
 int VB_SISVB ; 

__attribute__((used)) static void
SiS_SetSeqRegs(struct SiS_Private *SiS_Pr, unsigned short StandTableIndex)
{
   unsigned char SRdata;
   int i;

   SiS_SetReg(SiS_Pr->SiS_P3c4,0x00,0x03);

   /* or "display off"  */
   SRdata = SiS_Pr->SiS_StandTable[StandTableIndex].SR[0] | 0x20;

   /* determine whether to force x8 dotclock */
   if((SiS_Pr->SiS_VBType & VB_SISVB) || (SiS_Pr->SiS_IF_DEF_LVDS)) {

      if(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToTV)) {
         if(SiS_Pr->SiS_VBInfo & SetInSlaveMode)    SRdata |= 0x01;
      } else if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) SRdata |= 0x01;

   }

   SiS_SetReg(SiS_Pr->SiS_P3c4,0x01,SRdata);

   for(i = 2; i <= 4; i++) {
      SRdata = SiS_Pr->SiS_StandTable[StandTableIndex].SR[i - 1];
      SiS_SetReg(SiS_Pr->SiS_P3c4,i,SRdata);
   }
}