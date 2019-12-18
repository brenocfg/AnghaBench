#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_object_t ;
typedef  int /*<<< orphan*/  vm_object_size_t ;
typedef  int /*<<< orphan*/  vm_object_offset_t ;
typedef  TYPE_2__* vm_named_entry_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_3__* ipc_port_t ;
struct TYPE_11__ {scalar_t__ ip_kobject; } ;
struct TYPE_9__ {scalar_t__ object; } ;
struct TYPE_10__ {int /*<<< orphan*/  size; int /*<<< orphan*/  offset; TYPE_1__ backing; scalar_t__ is_copy; scalar_t__ is_sub_map; } ;

/* Variables and functions */
 scalar_t__ IKOT_NAMED_ENTRY ; 
 int /*<<< orphan*/  IP_VALID (TYPE_3__*) ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 scalar_t__ VM_OBJECT_NULL ; 
 scalar_t__ ip_kotype (TYPE_3__*) ; 
 int /*<<< orphan*/  named_entry_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  named_entry_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_get_page_counts (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  vm_object_lock (scalar_t__) ; 
 int /*<<< orphan*/  vm_object_unlock (scalar_t__) ; 

kern_return_t
mach_memory_entry_get_page_counts(
	ipc_port_t	entry_port,
	unsigned int	*resident_page_count,
	unsigned int	*dirty_page_count)
{
	kern_return_t		kr;
	vm_named_entry_t	mem_entry;
	vm_object_t		object;
	vm_object_offset_t	offset;
	vm_object_size_t	size;

	if (!IP_VALID(entry_port) ||
	    ip_kotype(entry_port) != IKOT_NAMED_ENTRY) {
		return KERN_INVALID_ARGUMENT;
	}

	mem_entry = (vm_named_entry_t) entry_port->ip_kobject;

	named_entry_lock(mem_entry);

	if (mem_entry->is_sub_map ||
	    mem_entry->is_copy) {
		named_entry_unlock(mem_entry);
		return KERN_INVALID_ARGUMENT;
	}

	object = mem_entry->backing.object;
	if (object == VM_OBJECT_NULL) {
		named_entry_unlock(mem_entry);
		return KERN_INVALID_ARGUMENT;
	}

	vm_object_lock(object);

	offset = mem_entry->offset;
	size = mem_entry->size;

	named_entry_unlock(mem_entry);

	kr = vm_object_get_page_counts(object, offset, size, resident_page_count, dirty_page_count);

	vm_object_unlock(object);

	return kr;
}