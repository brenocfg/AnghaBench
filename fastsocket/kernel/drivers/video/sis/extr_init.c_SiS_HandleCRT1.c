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
struct SiS_Private {int /*<<< orphan*/  SiS_MyCR63; int /*<<< orphan*/  SiS_P3d4; int /*<<< orphan*/  SiS_P3c4; } ;

/* Variables and functions */
 int SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SiS_SetRegAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SiS_SetRegOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
SiS_HandleCRT1(struct SiS_Private *SiS_Pr)
{
   /* Enable CRT1 gating */
   SiS_SetRegAND(SiS_Pr->SiS_P3d4,SiS_Pr->SiS_MyCR63,0xbf);
#if 0
   if(!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x15) & 0x01)) {
      if((SiS_GetReg(SiS_Pr->SiS_P3c4,0x15) & 0x0a) ||
         (SiS_GetReg(SiS_Pr->SiS_P3c4,0x16) & 0x01)) {
         SiS_SetRegOR(SiS_Pr->SiS_P3d4,SiS_Pr->SiS_MyCR63,0x40);
      }
   }
#endif
}