#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_shared_region_t ;
typedef  scalar_t__ mach_vm_offset_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_4__ {int sr_ref_count; scalar_t__ sr_base_address; scalar_t__ sr_first_mapping; scalar_t__ sr_mapping_in_progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ADDRESS ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  SHARED_REGION_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 scalar_t__ VM_KERNEL_ADDRPERM (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vm_shared_region_lock () ; 
 int /*<<< orphan*/  vm_shared_region_sleep (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_shared_region_unlock () ; 

kern_return_t
vm_shared_region_start_address(
	vm_shared_region_t	shared_region,
	mach_vm_offset_t	*start_address)
{
	kern_return_t		kr;
	mach_vm_offset_t	sr_base_address;
	mach_vm_offset_t	sr_first_mapping;

	SHARED_REGION_TRACE_DEBUG(
		("shared_region: -> start_address(%p)\n",
		 (void *)VM_KERNEL_ADDRPERM(shared_region)));
	assert(shared_region->sr_ref_count > 1);

	vm_shared_region_lock();

	/*
	 * Wait if there's another thread establishing a mapping
	 * in this shared region right when we're looking at it.
	 * We want a consistent view of the map...
	 */
	while (shared_region->sr_mapping_in_progress) {
		/* wait for our turn... */
		assert(shared_region->sr_ref_count > 1);
		vm_shared_region_sleep(&shared_region->sr_mapping_in_progress,
				       THREAD_UNINT);
	}
	assert(! shared_region->sr_mapping_in_progress);
	assert(shared_region->sr_ref_count > 1);
	
	sr_base_address = shared_region->sr_base_address;
	sr_first_mapping = shared_region->sr_first_mapping;

	if (sr_first_mapping == (mach_vm_offset_t) -1) {
		/* shared region is empty */
		kr = KERN_INVALID_ADDRESS;
	} else {
		kr = KERN_SUCCESS;
		*start_address = sr_base_address + sr_first_mapping;
	}

	vm_shared_region_unlock();
	
	SHARED_REGION_TRACE_DEBUG(
		("shared_region: start_address(%p) <- 0x%llx\n",
		 (void *)VM_KERNEL_ADDRPERM(shared_region),
		 (long long)shared_region->sr_base_address));

	return kr;
}