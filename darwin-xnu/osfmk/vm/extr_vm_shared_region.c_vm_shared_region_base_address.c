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
struct TYPE_4__ {int sr_ref_count; scalar_t__ sr_base_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHARED_REGION_TRACE_DEBUG (char*) ; 
 scalar_t__ VM_KERNEL_ADDRPERM (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 

mach_vm_offset_t
vm_shared_region_base_address(
	vm_shared_region_t	shared_region)
{
	SHARED_REGION_TRACE_DEBUG(
		("shared_region: -> base_address(%p)\n",
		 (void *)VM_KERNEL_ADDRPERM(shared_region)));
	assert(shared_region->sr_ref_count > 1);
	SHARED_REGION_TRACE_DEBUG(
		("shared_region: base_address(%p) <- 0x%llx\n",
		 (void *)VM_KERNEL_ADDRPERM(shared_region),
		 (long long)shared_region->sr_base_address));
	return shared_region->sr_base_address;
}