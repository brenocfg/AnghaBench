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
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int KDP_FAULT_RESULT_FAULTED_IN ; 
 int KDP_FAULT_RESULT_PAGED_OUT ; 
 int KDP_FAULT_RESULT_TRIED_FAULT ; 
 scalar_t__ PAGE_MASK ; 
 scalar_t__ PHYSMAP_PTOV (scalar_t__) ; 
 scalar_t__ atop (scalar_t__) ; 
 int kThreadFaultedBT ; 
 int kThreadTriedFaultBT ; 
 int kThreadTruncatedBT ; 
 int /*<<< orphan*/  kasan_notify_address (scalar_t__,int) ; 
 scalar_t__ kdp_find_phys (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ phystokv (scalar_t__) ; 
 scalar_t__ prev_target_kva ; 
 scalar_t__ prev_target_page ; 
 int /*<<< orphan*/  stack_enable_faulting ; 
 scalar_t__ validate_next_addr ; 

vm_offset_t
machine_trace_thread_get_kva(vm_offset_t cur_target_addr, vm_map_t map, uint32_t *thread_trace_flags)
{
	vm_offset_t cur_target_page;
	vm_offset_t cur_phys_addr;
	vm_offset_t kern_virt_target_addr;
	uint32_t kdp_fault_results = 0;

	cur_target_page = atop(cur_target_addr);

	if ((cur_target_page != prev_target_page) || validate_next_addr) {

		/*
		 * Alright; it wasn't our previous page.  So
		 * we must validate that there is a page
		 * table entry for this address under the
		 * current pmap, and that it has default
		 * cache attributes (otherwise it may not be
		 * safe to access it).
		 */
		cur_phys_addr = kdp_find_phys(map, cur_target_addr, stack_enable_faulting, &kdp_fault_results);
		if (thread_trace_flags) {
			if (kdp_fault_results & KDP_FAULT_RESULT_PAGED_OUT) {
				*thread_trace_flags |= kThreadTruncatedBT;
			}

			if (kdp_fault_results & KDP_FAULT_RESULT_TRIED_FAULT) {
				*thread_trace_flags |= kThreadTriedFaultBT;
			}

			if (kdp_fault_results & KDP_FAULT_RESULT_FAULTED_IN) {
				*thread_trace_flags |= kThreadFaultedBT;
			}
		}

		if (cur_phys_addr == 0) {
			return 0;
		}
#if __x86_64__
		kern_virt_target_addr = (vm_offset_t) PHYSMAP_PTOV(cur_phys_addr);
#elif __arm__ || __arm64__
		kern_virt_target_addr = phystokv(cur_phys_addr);
#else
#error Oh come on... we should really unify the physical -> kernel virtual interface
#endif
		prev_target_page = cur_target_page;
		prev_target_kva = (kern_virt_target_addr & ~PAGE_MASK);
		validate_next_addr = FALSE;
	} else {
		/* We found a translation, so stash this page */
		kern_virt_target_addr = prev_target_kva + (cur_target_addr & PAGE_MASK);
	}

#if KASAN
	kasan_notify_address(kern_virt_target_addr, sizeof(uint64_t));
#endif
	return kern_virt_target_addr;
}