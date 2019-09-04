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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */

void
commpage_update_mach_approximate_time(uint64_t abstime)
{
#ifdef CONFIG_MACH_APPROXIMATE_TIME
	uintptr_t approx_time_base = (uintptr_t)(_COMM_PAGE_APPROX_TIME + _COMM_PAGE_RW_OFFSET);
	uint64_t saved_data;

	if (commPagePtr) {
		saved_data = atomic_load_explicit((_Atomic uint64_t *)approx_time_base,
			memory_order_relaxed);
		if (saved_data < abstime) {
			/* ignoring the success/fail return value assuming that
			 * if the value has been updated since we last read it,
			 * "someone" has a newer timestamp than us and ours is
			 * now invalid. */
			atomic_compare_exchange_strong_explicit((_Atomic uint64_t *)approx_time_base, 
				&saved_data, abstime, memory_order_relaxed, memory_order_relaxed);
		}
	}
#else
#pragma unused (abstime)
#endif
}