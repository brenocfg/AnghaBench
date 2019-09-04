#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_shared_region_t ;
typedef  TYPE_3__* vm_named_entry_t ;
typedef  TYPE_2__* vm_map_t ;
typedef  TYPE_5__* ipc_port_t ;
struct TYPE_12__ {scalar_t__ ip_kobject; } ;
struct TYPE_9__ {TYPE_2__* map; } ;
struct TYPE_11__ {int is_sub_map; TYPE_1__ backing; } ;
struct TYPE_10__ {int sr_ref_count; TYPE_5__* sr_mem_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHARED_REGION_TRACE_DEBUG (char*) ; 
 scalar_t__ VM_KERNEL_ADDRPERM (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 

vm_map_t
vm_shared_region_vm_map(
	vm_shared_region_t	shared_region)
{
	ipc_port_t		sr_handle;
	vm_named_entry_t	sr_mem_entry;
	vm_map_t		sr_map;

	SHARED_REGION_TRACE_DEBUG(
		("shared_region: -> vm_map(%p)\n",
		 (void *)VM_KERNEL_ADDRPERM(shared_region)));
	assert(shared_region->sr_ref_count > 1);

	sr_handle = shared_region->sr_mem_entry;
	sr_mem_entry = (vm_named_entry_t) sr_handle->ip_kobject;
	sr_map = sr_mem_entry->backing.map;
	assert(sr_mem_entry->is_sub_map);

	SHARED_REGION_TRACE_DEBUG(
		("shared_region: vm_map(%p) <- %p\n",
		 (void *)VM_KERNEL_ADDRPERM(shared_region),
		 (void *)VM_KERNEL_ADDRPERM(sr_map)));
	return sr_map;
}