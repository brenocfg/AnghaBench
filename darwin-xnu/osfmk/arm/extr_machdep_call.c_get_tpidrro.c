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
 uintptr_t __builtin_arm_mrc (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

uintptr_t
get_tpidrro(void)
{
	uintptr_t	uthread;
#if __arm__
	uthread = __builtin_arm_mrc(15, 0, 13, 0, 3);	// TPIDRURO
#else
	__asm__ volatile("mrs %0, TPIDRRO_EL0" : "=r" (uthread));
#endif
	return uthread;
}