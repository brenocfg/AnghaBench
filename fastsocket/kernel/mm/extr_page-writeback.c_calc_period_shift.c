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
 int PAGE_SIZE ; 
 int determine_dirtyable_memory () ; 
 int ilog2 (unsigned long) ; 
 int vm_dirty_bytes ; 
 int vm_dirty_ratio ; 

__attribute__((used)) static int calc_period_shift(void)
{
	unsigned long dirty_total;

	if (vm_dirty_bytes)
		dirty_total = vm_dirty_bytes / PAGE_SIZE;
	else
		dirty_total = (vm_dirty_ratio * determine_dirtyable_memory()) /
				100;
	/*
	 * RHEL6: When an user sets vm.dirty_ratio=0 we trigger havoc that
	 * creates the barbed wire which leads to the kernel panic described
	 * at  BZ#871599.
	 *
	 * As dirty_total is from unsigned long type, doing dirty total - 1
	 * means we're calling for ilog2(ULONG_MAX), thus calc_periodic_shift()
	 * will return 66.
	 * Also, if we are unlucky enough to get dirty_total becoming 1, we
	 * can potentially trigger unexpected behavior, as  ilog2(0) == NaN.
	 *
	 * That's why we need to certify the lower limit of dirty_total never
	 * gets smaller than 2, as ilog2(1) == 0, and for such cases
	 * calc_periodic_shift() will always return the smaller period shift
	 * expected (2).
	 */
	if (dirty_total < 2)
		dirty_total = 2;

	return 2 + ilog2(dirty_total - 1);
}