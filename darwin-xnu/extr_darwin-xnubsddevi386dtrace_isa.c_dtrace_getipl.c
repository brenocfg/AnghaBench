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
 scalar_t__ ml_at_interrupt_context () ; 

int
dtrace_getipl(void)
{
	/*
	 * XXX Drat, get_interrupt_level is MACH_KERNEL_PRIVATE
	 * in osfmk/kern/cpu_data.h
	 */
	/* return get_interrupt_level(); */
	return (ml_at_interrupt_context() ? 1: 0);
}