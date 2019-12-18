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
 int /*<<< orphan*/  __builtin_arm_mcr (int,int /*<<< orphan*/ ,uintptr_t,int,int /*<<< orphan*/ ,int) ; 

void
set_tpidrro(uintptr_t uthread)
{
#if __arm__
	 __builtin_arm_mcr(15, 0, uthread, 13, 0, 3);	// TPIDRURO
#else
	__asm__ volatile("msr TPIDRRO_EL0, %0" : : "r" (uthread));
#endif
}