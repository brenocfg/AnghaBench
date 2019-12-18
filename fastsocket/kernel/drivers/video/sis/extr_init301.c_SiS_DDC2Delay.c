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
struct SiS_Private {int /*<<< orphan*/  SiS_P3c4; } ;

/* Variables and functions */
 int /*<<< orphan*/  SiS_GetReg (int /*<<< orphan*/ ,int) ; 

void
SiS_DDC2Delay(struct SiS_Private *SiS_Pr, unsigned int delaytime)
{
   while (delaytime-- > 0)
      SiS_GetReg(SiS_Pr->SiS_P3c4, 0x05);
}