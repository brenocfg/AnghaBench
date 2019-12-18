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

/* Variables and functions */
 scalar_t__ COND_HI () ; 
 int /*<<< orphan*/  CYC_SCC_R_TRUE ; 
 int DY ; 
 int /*<<< orphan*/  USE_CYCLES (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void m68k_op_shi_8_d(void)
{
  if(COND_HI())
  {
    DY |= 0xff;
    USE_CYCLES(CYC_SCC_R_TRUE);
    return;
  }
  DY &= 0xffffff00;
}