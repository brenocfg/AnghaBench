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
	uint64_t saved_data;
	char *cp;
	
	cp = commPagePtr32;
	if ( cp ) {
		cp += (_COMM_PAGE_APPROX_TIME - _COMM_PAGE32_BASE_ADDRESS);
		saved_data = atomic_load_explicit((_Atomic uint64_t *)(uintptr_t)cp, memory_order_relaxed);
		if (saved_data < abstime) {
			/* ignoring the success/fail return value assuming that
			 * if the value has been updated since we last read it,
			 * "someone" has a newer timestamp than us and ours is
			 * now invalid. */
			atomic_compare_exchange_strong_explicit((_Atomic uint64_t *)(uintptr_t)cp, 
				&saved_data, abstime, memory_order_relaxed, memory_order_relaxed);
		}
	}
	cp = commPagePtr64;
	if ( cp ) {
		cp += (_COMM_PAGE_APPROX_TIME - _COMM_PAGE32_START_ADDRESS);
		saved_data = atomic_load_explicit((_Atomic uint64_t *)(uintptr_t)cp, memory_order_relaxed);
		if (saved_data < abstime) {
			/* ignoring the success/fail return value assuming that
			 * if the value has been updated since we last read it,
			 * "someone" has a newer timestamp than us and ours is
			 * now invalid. */
			atomic_compare_exchange_strong_explicit((_Atomic uint64_t *)(uintptr_t)cp, 
				&saved_data, abstime, memory_order_relaxed, memory_order_relaxed);
		}
	}
#else
#pragma unused (abstime)
#endif
}