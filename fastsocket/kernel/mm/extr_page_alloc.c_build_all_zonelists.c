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
 int MIGRATE_TYPES ; 
 scalar_t__ SYSTEM_BOOTING ; 
 int /*<<< orphan*/  __build_all_zonelists (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpuset_init_current_mems_allowed () ; 
 size_t current_zonelist_order ; 
 int /*<<< orphan*/  mminit_verify_zonelist () ; 
 int nr_free_pagecache_pages () ; 
 int /*<<< orphan*/  nr_online_nodes ; 
 int page_group_by_mobility_disabled ; 
 int pageblock_nr_pages ; 
 size_t policy_zone ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  set_zonelist_order () ; 
 int /*<<< orphan*/  stop_machine (int /*<<< orphan*/  (*) (int /*<<< orphan*/ *),void*,int /*<<< orphan*/ *) ; 
 scalar_t__ system_state ; 
 int vm_total_pages ; 
 int /*<<< orphan*/ * zone_names ; 
 int /*<<< orphan*/ * zonelist_order_name ; 

void build_all_zonelists(void *data)
{
	set_zonelist_order();

	if (system_state == SYSTEM_BOOTING) {
		__build_all_zonelists(NULL);
		mminit_verify_zonelist();
		cpuset_init_current_mems_allowed();
	} else {
		/* we have to stop all cpus to guarantee there is no user
		   of zonelist */
		stop_machine(__build_all_zonelists, data, NULL);
		/* cpuset refresh routine should be here */
	}
	vm_total_pages = nr_free_pagecache_pages();
	/*
	 * Disable grouping by mobility if the number of pages in the
	 * system is too low to allow the mechanism to work. It would be
	 * more accurate, but expensive to check per-zone. This check is
	 * made on memory-hotadd so a system can start with mobility
	 * disabled and enable it later
	 */
	if (vm_total_pages < (pageblock_nr_pages * MIGRATE_TYPES))
		page_group_by_mobility_disabled = 1;
	else
		page_group_by_mobility_disabled = 0;

	printk("Built %i zonelists in %s order, mobility grouping %s.  "
		"Total pages: %ld\n",
			nr_online_nodes,
			zonelist_order_name[current_zonelist_order],
			page_group_by_mobility_disabled ? "off" : "on",
			vm_total_pages);
#ifdef CONFIG_NUMA
	printk("Policy zone: %s\n", zone_names[policy_zone]);
#endif
}