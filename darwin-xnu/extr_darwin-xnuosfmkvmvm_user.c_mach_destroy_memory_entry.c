#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_named_entry_t ;
struct vm_named_entry {int dummy; } ;
typedef  TYPE_3__* ipc_port_t ;
struct TYPE_10__ {scalar_t__ ip_kobject; } ;
struct TYPE_8__ {int /*<<< orphan*/  object; int /*<<< orphan*/  copy; int /*<<< orphan*/  map; } ;
struct TYPE_9__ {int ref_count; TYPE_1__ backing; scalar_t__ is_copy; scalar_t__ is_sub_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (void*,int) ; 
 int /*<<< orphan*/  named_entry_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  named_entry_lock_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  named_entry_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_copy_discard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_deallocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ ) ; 

void
mach_destroy_memory_entry(
	ipc_port_t	port)
{
	vm_named_entry_t	named_entry;
#if MACH_ASSERT
	assert(ip_kotype(port) == IKOT_NAMED_ENTRY);
#endif /* MACH_ASSERT */
	named_entry = (vm_named_entry_t)port->ip_kobject;

	named_entry_lock(named_entry);
	named_entry->ref_count -= 1;

	if(named_entry->ref_count == 0) {
		if (named_entry->is_sub_map) {
			vm_map_deallocate(named_entry->backing.map);
		} else if (named_entry->is_copy) {
			vm_map_copy_discard(named_entry->backing.copy);
		} else {
			/* release the VM object we've been pointing to */
			vm_object_deallocate(named_entry->backing.object);
		}

		named_entry_unlock(named_entry);
		named_entry_lock_destroy(named_entry);

#if VM_NAMED_ENTRY_LIST
		lck_mtx_lock_spin(&vm_named_entry_list_lock_data);
		queue_remove(&vm_named_entry_list, named_entry,
			     vm_named_entry_t, named_entry_list);
		assert(vm_named_entry_count > 0);
		vm_named_entry_count--;
		lck_mtx_unlock(&vm_named_entry_list_lock_data);
#endif /* VM_NAMED_ENTRY_LIST */

		kfree((void *) port->ip_kobject,
		      sizeof (struct vm_named_entry));
	} else
		named_entry_unlock(named_entry);
}