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
 scalar_t__ _COMM_PAGE_BOOTTIME_USEC ; 
 scalar_t__ _COMM_PAGE_RW_OFFSET ; 
 scalar_t__ commPagePtr ; 

void
commpage_update_boottime(uint64_t value)
{
	if (commPagePtr) {
#ifdef __arm64__
		*((uint64_t *)(_COMM_PAGE_BOOTTIME_USEC + _COMM_PAGE_RW_OFFSET)) = value;
#else
		uint64_t *cp = (uint64_t *)(_COMM_PAGE_BOOTTIME_USEC + _COMM_PAGE_RW_OFFSET);
		uint64_t old_value;
		do {
			old_value = *cp;
		} while (!OSCompareAndSwap64(old_value, value, cp));
#endif /* __arm64__ */
	}
}