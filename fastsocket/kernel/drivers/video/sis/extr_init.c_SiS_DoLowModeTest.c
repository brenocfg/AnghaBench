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
struct SiS_Private {scalar_t__ ChipType; int /*<<< orphan*/  SiS_P3d4; } ;

/* Variables and functions */
 scalar_t__ SIS_300 ; 
 scalar_t__ SIS_315H ; 
 unsigned short SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetRegOR (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static bool
SiS_DoLowModeTest(struct SiS_Private *SiS_Pr, unsigned short ModeNo)
{
   unsigned short temp, temp1, temp2;

   if((ModeNo != 0x03) && (ModeNo != 0x10) && (ModeNo != 0x12))
      return true;
   temp = SiS_GetReg(SiS_Pr->SiS_P3d4,0x11);
   SiS_SetRegOR(SiS_Pr->SiS_P3d4,0x11,0x80);
   temp1 = SiS_GetReg(SiS_Pr->SiS_P3d4,0x00);
   SiS_SetReg(SiS_Pr->SiS_P3d4,0x00,0x55);
   temp2 = SiS_GetReg(SiS_Pr->SiS_P3d4,0x00);
   SiS_SetReg(SiS_Pr->SiS_P3d4,0x00,temp1);
   SiS_SetReg(SiS_Pr->SiS_P3d4,0x11,temp);
   if((SiS_Pr->ChipType >= SIS_315H) ||
      (SiS_Pr->ChipType == SIS_300)) {
      if(temp2 == 0x55) return false;
      else return true;
   } else {
      if(temp2 != 0x55) return true;
      else {
	 SiS_SetRegOR(SiS_Pr->SiS_P3d4,0x35,0x01);
	 return false;
      }
   }
}