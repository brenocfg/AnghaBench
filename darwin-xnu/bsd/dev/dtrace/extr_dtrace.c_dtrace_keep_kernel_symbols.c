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
 scalar_t__ DTRACE_KERNEL_SYMBOLS_ALWAYS_FROM_KERNEL ; 
 int /*<<< orphan*/  dtrace_are_restrictions_relaxed () ; 
 scalar_t__ dtrace_is_restricted () ; 
 scalar_t__ dtrace_kernel_symbol_mode ; 

int
dtrace_keep_kernel_symbols(void)
{
	if (dtrace_is_restricted() && !dtrace_are_restrictions_relaxed()) {
		return 0;
	}

	if (dtrace_kernel_symbol_mode == DTRACE_KERNEL_SYMBOLS_ALWAYS_FROM_KERNEL)
		return 1;

	return 0;
}