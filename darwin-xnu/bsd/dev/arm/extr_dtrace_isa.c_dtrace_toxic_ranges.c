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
 uintptr_t VM_MAX_KERNEL_ADDRESS ; 
 uintptr_t VM_MIN_KERNEL_ADDRESS ; 

void
dtrace_toxic_ranges(void (*func)(uintptr_t base, uintptr_t limit))
{
	/* XXX ARMTODO check copied from ppc/x86*/
 	/*
	 * "base" is the smallest toxic address in the range, "limit" is the first
	 * VALID address greater than "base".
	 */ 
	func(0x0, VM_MIN_KERNEL_ADDRESS);
	if (VM_MAX_KERNEL_ADDRESS < ~(uintptr_t)0)
			func(VM_MAX_KERNEL_ADDRESS + 1, ~(uintptr_t)0);
}