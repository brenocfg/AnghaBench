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
 scalar_t__ OSIncrementAtomicLong (int /*<<< orphan*/ *) ; 
 scalar_t__ __asan_option_detect_stack_use_after_return ; 
 int /*<<< orphan*/  suspend_count ; 
 scalar_t__ suspend_threshold ; 

void
kasan_fakestack_suspend(void)
{
	if (OSIncrementAtomicLong(&suspend_count) == suspend_threshold) {
		__asan_option_detect_stack_use_after_return = 0;
	}
}