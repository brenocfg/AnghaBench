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
struct SiS_Private {int SiS_SensibleSR11; int SiS_MyCR63; scalar_t__ ChipType; int /*<<< orphan*/  SiS_SysFlags; int /*<<< orphan*/  SiS_P3d4; } ;

/* Variables and functions */
 int /*<<< orphan*/  SF_760LFB ; 
 int /*<<< orphan*/  SF_760UMA ; 
 int /*<<< orphan*/  SF_Is651 ; 
 int /*<<< orphan*/  SF_Is652 ; 
 int /*<<< orphan*/  SF_IsM650 ; 
 int /*<<< orphan*/  SF_IsM652 ; 
 int /*<<< orphan*/  SF_IsM653 ; 
 scalar_t__ SIS_330 ; 
 scalar_t__ SIS_650 ; 
 scalar_t__ SIS_661 ; 
 scalar_t__ SIS_760 ; 
 scalar_t__ SIS_761 ; 
 int SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SiS_SetRegAND (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegOR (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
SiS_GetSysFlags(struct SiS_Private *SiS_Pr)
{
   unsigned char cr5f, temp1, temp2;

   /* 661 and newer: NEVER write non-zero to SR11[7:4] */
   /* (SR11 is used for DDC and in enable/disablebridge) */
   SiS_Pr->SiS_SensibleSR11 = false;
   SiS_Pr->SiS_MyCR63 = 0x63;
   if(SiS_Pr->ChipType >= SIS_330) {
      SiS_Pr->SiS_MyCR63 = 0x53;
      if(SiS_Pr->ChipType >= SIS_661) {
         SiS_Pr->SiS_SensibleSR11 = true;
      }
   }

   /* You should use the macros, not these flags directly */

   SiS_Pr->SiS_SysFlags = 0;
   if(SiS_Pr->ChipType == SIS_650) {
      cr5f = SiS_GetReg(SiS_Pr->SiS_P3d4,0x5f) & 0xf0;
      SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x5c,0x07);
      temp1 = SiS_GetReg(SiS_Pr->SiS_P3d4,0x5c) & 0xf8;
      SiS_SetRegOR(SiS_Pr->SiS_P3d4,0x5c,0xf8);
      temp2 = SiS_GetReg(SiS_Pr->SiS_P3d4,0x5c) & 0xf8;
      if((!temp1) || (temp2)) {
	 switch(cr5f) {
	    case 0x80:
	    case 0x90:
	    case 0xc0:
	       SiS_Pr->SiS_SysFlags |= SF_IsM650;
	       break;
	    case 0xa0:
	    case 0xb0:
	    case 0xe0:
	       SiS_Pr->SiS_SysFlags |= SF_Is651;
	       break;
	 }
      } else {
	 switch(cr5f) {
	    case 0x90:
	       temp1 = SiS_GetReg(SiS_Pr->SiS_P3d4,0x5c) & 0xf8;
	       switch(temp1) {
		  case 0x00: SiS_Pr->SiS_SysFlags |= SF_IsM652; break;
		  case 0x40: SiS_Pr->SiS_SysFlags |= SF_IsM653; break;
		  default:   SiS_Pr->SiS_SysFlags |= SF_IsM650; break;
	       }
	       break;
	    case 0xb0:
	       SiS_Pr->SiS_SysFlags |= SF_Is652;
	       break;
	    default:
	       SiS_Pr->SiS_SysFlags |= SF_IsM650;
	       break;
	 }
      }
   }

   if(SiS_Pr->ChipType >= SIS_760 && SiS_Pr->ChipType <= SIS_761) {
      if(SiS_GetReg(SiS_Pr->SiS_P3d4,0x78) & 0x30) {
         SiS_Pr->SiS_SysFlags |= SF_760LFB;
      }
      if(SiS_GetReg(SiS_Pr->SiS_P3d4,0x79) & 0xf0) {
         SiS_Pr->SiS_SysFlags |= SF_760UMA;
      }
   }
}