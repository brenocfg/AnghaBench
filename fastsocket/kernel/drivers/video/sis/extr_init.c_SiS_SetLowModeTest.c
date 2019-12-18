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
struct SiS_Private {int /*<<< orphan*/  SiS_SetFlag; } ;

/* Variables and functions */
 int /*<<< orphan*/  LowModeTests ; 
 scalar_t__ SiS_DoLowModeTest (struct SiS_Private*,unsigned short) ; 

__attribute__((used)) static void
SiS_SetLowModeTest(struct SiS_Private *SiS_Pr, unsigned short ModeNo)
{
   if(SiS_DoLowModeTest(SiS_Pr, ModeNo)) {
      SiS_Pr->SiS_SetFlag |= LowModeTests;
   }
}