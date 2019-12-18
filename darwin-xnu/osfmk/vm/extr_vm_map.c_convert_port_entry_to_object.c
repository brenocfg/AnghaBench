#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_object_t ;
typedef  TYPE_2__* vm_named_entry_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_3__* ipc_port_t ;
struct TYPE_13__ {scalar_t__ ip_kobject; } ;
struct TYPE_11__ {int /*<<< orphan*/  object; } ;
struct TYPE_12__ {int protection; TYPE_1__ backing; int /*<<< orphan*/  is_copy; int /*<<< orphan*/  is_sub_map; int /*<<< orphan*/  Lock; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 scalar_t__ IKOT_NAMED_ENTRY ; 
 scalar_t__ IP_VALID (TYPE_3__*) ; 
 int /*<<< orphan*/  VM_OBJECT_NULL ; 
 int VM_PROT_WRITE ; 
 scalar_t__ ip_active (TYPE_3__*) ; 
 scalar_t__ ip_kotype (TYPE_3__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_3__*) ; 
 int /*<<< orphan*/  lck_mtx_try_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mach_destroy_memory_entry (TYPE_3__*) ; 
 int /*<<< orphan*/  mutex_pause (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_reference (int /*<<< orphan*/ ) ; 

vm_object_t
convert_port_entry_to_object(
	ipc_port_t	port)
{
	vm_object_t		object = VM_OBJECT_NULL;
	vm_named_entry_t	named_entry;
	uint32_t		try_failed_count = 0;

	if (IP_VALID(port) &&
	    (ip_kotype(port) == IKOT_NAMED_ENTRY)) {
	try_again:
		ip_lock(port);
		if (ip_active(port) &&
		    (ip_kotype(port) == IKOT_NAMED_ENTRY)) {
			named_entry = (vm_named_entry_t)port->ip_kobject;
			if (!(lck_mtx_try_lock(&(named_entry)->Lock))) {
				ip_unlock(port);
				try_failed_count++;
				mutex_pause(try_failed_count);
                       		goto try_again;
			}
			named_entry->ref_count++;
			lck_mtx_unlock(&(named_entry)->Lock);
			ip_unlock(port);
			if (!(named_entry->is_sub_map) &&
			    !(named_entry->is_copy) &&
			    (named_entry->protection & VM_PROT_WRITE)) {
				object = named_entry->backing.object;
				vm_object_reference(object);
			}
			mach_destroy_memory_entry(port);
		}
	}

	return object;
}