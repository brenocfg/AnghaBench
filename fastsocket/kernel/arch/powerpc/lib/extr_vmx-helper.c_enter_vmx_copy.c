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
 int /*<<< orphan*/  enable_kernel_altivec () ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  preempt_disable () ; 

int enter_vmx_copy(void)
{
	if (in_interrupt())
		return 0;

	preempt_disable();

	enable_kernel_altivec();

	return 1;
}