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
 int ENOSPC ; 
 unsigned int NR_PMB_ENTRIES ; 
 unsigned long PMB_C ; 
 unsigned int PMB_NO_ENTRY ; 
 unsigned long PMB_V ; 
 unsigned long PMB_WT ; 
 int /*<<< orphan*/  ctrl_outl (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned int find_first_zero_bit (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ likely (unsigned long) ; 
 int /*<<< orphan*/  mk_pmb_addr (unsigned int) ; 
 int /*<<< orphan*/  mk_pmb_data (unsigned int) ; 
 int /*<<< orphan*/  pmb_map ; 
 scalar_t__ test_and_set_bit (unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int __set_pmb_entry(unsigned long vpn, unsigned long ppn,
		    unsigned long flags, int *entry)
{
	unsigned int pos = *entry;

	if (unlikely(pos == PMB_NO_ENTRY))
		pos = find_first_zero_bit(&pmb_map, NR_PMB_ENTRIES);

repeat:
	if (unlikely(pos > NR_PMB_ENTRIES))
		return -ENOSPC;

	if (test_and_set_bit(pos, &pmb_map)) {
		pos = find_first_zero_bit(&pmb_map, NR_PMB_ENTRIES);
		goto repeat;
	}

	ctrl_outl(vpn | PMB_V, mk_pmb_addr(pos));

#ifdef CONFIG_CACHE_WRITETHROUGH
	/*
	 * When we are in 32-bit address extended mode, CCR.CB becomes
	 * invalid, so care must be taken to manually adjust cacheable
	 * translations.
	 */
	if (likely(flags & PMB_C))
		flags |= PMB_WT;
#endif

	ctrl_outl(ppn | flags | PMB_V, mk_pmb_data(pos));

	*entry = pos;

	return 0;
}