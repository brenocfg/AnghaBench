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
 unsigned short EnableDualEdge ; 
 scalar_t__ SIS_315H ; 
 unsigned short SetToLCDA ; 
 unsigned short SiS_GetReg (int /*<<< orphan*/ ,int) ; 

bool
SiS_IsVAMode(struct SiS_Private *SiS_Pr)
{
#ifdef SIS315H
   unsigned short flag;

   if(SiS_Pr->ChipType >= SIS_315H) {
      flag = SiS_GetReg(SiS_Pr->SiS_P3d4,0x38);
      if((flag & EnableDualEdge) && (flag & SetToLCDA)) return true;
   }
#endif
   return false;
}