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
 long OSDecrementAtomicLong (int /*<<< orphan*/ *) ; 
 int __asan_option_detect_stack_use_after_return ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ fakestack_enabled ; 
 int /*<<< orphan*/  suspend_count ; 
 long suspend_threshold ; 

void
kasan_fakestack_resume(void)
{
	long orig = OSDecrementAtomicLong(&suspend_count);
	assert(orig >= 0);

	if (fakestack_enabled && orig == suspend_threshold) {
		__asan_option_detect_stack_use_after_return = 1;
	}
}