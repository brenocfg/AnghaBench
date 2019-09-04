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
 int /*<<< orphan*/  OSCompareAndSwap64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ _COMM_PAGE_CONT_TIMEBASE ; 
 scalar_t__ _COMM_PAGE_RW_OFFSET ; 
 scalar_t__ commPagePtr ; 

void
commpage_update_mach_continuous_time(uint64_t sleeptime)
{
	if (commPagePtr) {
#ifdef __arm64__
		*((uint64_t *)(_COMM_PAGE_CONT_TIMEBASE + _COMM_PAGE_RW_OFFSET)) = sleeptime;
#else
		uint64_t *c_time_base = (uint64_t *)(_COMM_PAGE_CONT_TIMEBASE + _COMM_PAGE_RW_OFFSET);
		uint64_t old;
		do {
			old = *c_time_base;
		} while(!OSCompareAndSwap64(old, sleeptime, c_time_base));
#endif /* __arm64__ */
	}
}