#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ peak; } ;
typedef  TYPE_1__ vm_allocation_zone_total_t ;
typedef  int /*<<< orphan*/  vm_allocation_site_t ;
typedef  size_t uint32_t ;

/* Variables and functions */
 size_t VM_KERN_COUNTER_COUNT ; 
 size_t VM_MAX_TAG_VALUE ; 
 size_t VM_MAX_TAG_ZONES ; 
 int /*<<< orphan*/  lck_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** vm_allocation_sites ; 
 int /*<<< orphan*/  vm_allocation_sites_lock ; 
 TYPE_1__** vm_allocation_zone_totals ; 

uint32_t
vm_page_diagnose_estimate(void)
{
    vm_allocation_site_t * site;
    uint32_t               count;
    uint32_t               idx;

	lck_spin_lock(&vm_allocation_sites_lock);
	for (count = idx = 0; idx < VM_MAX_TAG_VALUE; idx++)
    {
		site = vm_allocation_sites[idx];
		if (!site) continue;
		count++;
#if VM_MAX_TAG_ZONES
		if (vm_allocation_zone_totals)
		{
			vm_allocation_zone_total_t * zone;
			zone = vm_allocation_zone_totals[idx];
			if (!zone) continue;
			for (uint32_t zidx = 0; zidx < VM_MAX_TAG_ZONES; zidx++) if (zone[zidx].peak) count++;
		}
#endif
    }
	lck_spin_unlock(&vm_allocation_sites_lock);

    /* some slop for new tags created */
    count += 8;
    count += VM_KERN_COUNTER_COUNT;

    return (count);
}