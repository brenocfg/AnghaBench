#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_offset_t ;
typedef  TYPE_1__* vm_map_t ;
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  ppnum_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_7__ {scalar_t__ sfs_time_spent_faulting; scalar_t__ sfs_system_max_fault_time; int /*<<< orphan*/  sfs_pages_faulted_in; scalar_t__ sfs_stopped_faulting; } ;
struct TYPE_6__ {int /*<<< orphan*/  pmap; } ;

/* Variables and functions */
 int KDP_FAULT_RESULT_FAULTED_IN ; 
 int KDP_FAULT_RESULT_PAGED_OUT ; 
 int KDP_FAULT_RESULT_TRIED_FAULT ; 
 int PAGE_MASK ; 
 scalar_t__ TRUE ; 
 TYPE_1__* VM_MAP_NULL ; 
 unsigned int VM_WIMG_DEFAULT ; 
 unsigned int VM_WIMG_MASK ; 
 scalar_t__ atop (int) ; 
 TYPE_4__ fault_stats ; 
 int kdp_lightweight_fault (TYPE_1__*,int) ; 
 int kdp_vtophys (int /*<<< orphan*/ ,int) ; 
 scalar_t__ mach_absolute_time () ; 
 int /*<<< orphan*/  panic_stackshot ; 
 unsigned int pmap_cache_attributes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_valid_page (int /*<<< orphan*/ ) ; 

vm_offset_t
kdp_find_phys(vm_map_t map, vm_offset_t target_addr, boolean_t try_fault, uint32_t *kdp_fault_results)
{
	vm_offset_t cur_phys_addr;
	unsigned cur_wimg_bits;
	uint64_t fault_start_time = 0;

	if (map == VM_MAP_NULL) {
		return 0;
	}

	cur_phys_addr = kdp_vtophys(map->pmap, target_addr);
	if (!pmap_valid_page((ppnum_t) atop(cur_phys_addr))) {
		if (!try_fault || fault_stats.sfs_stopped_faulting) {
			if (kdp_fault_results)
				*kdp_fault_results |= KDP_FAULT_RESULT_PAGED_OUT;

			return 0;
		}

		/*
		 * The pmap doesn't have a valid page so we start at the top level
		 * vm map and try a lightweight fault. Update fault path usage stats.
		 */
		fault_start_time = mach_absolute_time();
		cur_phys_addr = kdp_lightweight_fault(map, (target_addr & ~PAGE_MASK));
		fault_stats.sfs_time_spent_faulting += (mach_absolute_time() - fault_start_time);

		if ((fault_stats.sfs_time_spent_faulting >= fault_stats.sfs_system_max_fault_time) && !panic_stackshot) {
			fault_stats.sfs_stopped_faulting = (uint8_t) TRUE;
		}

		cur_phys_addr += (target_addr & PAGE_MASK);

		if (!pmap_valid_page((ppnum_t) atop(cur_phys_addr))) {
			if (kdp_fault_results)
				*kdp_fault_results |= (KDP_FAULT_RESULT_TRIED_FAULT | KDP_FAULT_RESULT_PAGED_OUT);

			return 0;
		}

		if (kdp_fault_results)
			*kdp_fault_results |= KDP_FAULT_RESULT_FAULTED_IN;

		fault_stats.sfs_pages_faulted_in++;
	} else {
		/*
		 * This check is done in kdp_lightweight_fault for the fault path.
		 */
		cur_wimg_bits = pmap_cache_attributes((ppnum_t) atop(cur_phys_addr));

		if ((cur_wimg_bits & VM_WIMG_MASK) != VM_WIMG_DEFAULT) {
			return 0;
		}
	}

	return cur_phys_addr;
}