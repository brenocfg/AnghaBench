#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_purgable_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  TYPE_3__* vm_named_entry_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_4__* ipc_port_t ;
struct TYPE_17__ {scalar_t__ ip_kobject; } ;
struct TYPE_14__ {TYPE_2__* object; } ;
struct TYPE_16__ {scalar_t__ offset; scalar_t__ size; TYPE_1__ backing; scalar_t__ is_copy; scalar_t__ is_sub_map; } ;
struct TYPE_15__ {scalar_t__ vo_size; } ;

/* Variables and functions */
 scalar_t__ IKOT_NAMED_ENTRY ; 
 int /*<<< orphan*/  IP_VALID (TYPE_4__*) ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 TYPE_2__* VM_OBJECT_NULL ; 
 int VM_PURGABLE_ALL_MASKS ; 
 int /*<<< orphan*/  VM_PURGABLE_GET_STATE ; 
 int /*<<< orphan*/  VM_PURGABLE_SET_STATE ; 
 int /*<<< orphan*/  VM_PURGABLE_SET_STATE_FROM_KERNEL ; 
 int VM_PURGABLE_STATE_MASK ; 
 scalar_t__ ip_kotype (TYPE_4__*) ; 
 int /*<<< orphan*/  named_entry_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  named_entry_unlock (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_object_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_purgable_control (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_2__*) ; 

kern_return_t
memory_entry_purgeable_control_internal(
	ipc_port_t	entry_port,
	vm_purgable_t	control,
	int		*state)
{
	kern_return_t		kr;
	vm_named_entry_t	mem_entry;
	vm_object_t		object;

	if (!IP_VALID(entry_port) ||
	    ip_kotype(entry_port) != IKOT_NAMED_ENTRY) {
		return KERN_INVALID_ARGUMENT;
	}
	if (control != VM_PURGABLE_SET_STATE &&
	    control != VM_PURGABLE_GET_STATE &&
	    control != VM_PURGABLE_SET_STATE_FROM_KERNEL)
		return(KERN_INVALID_ARGUMENT);

	if ((control == VM_PURGABLE_SET_STATE ||
	     control == VM_PURGABLE_SET_STATE_FROM_KERNEL) &&
	    (((*state & ~(VM_PURGABLE_ALL_MASKS)) != 0) ||
	     ((*state & VM_PURGABLE_STATE_MASK) > VM_PURGABLE_STATE_MASK)))
		return(KERN_INVALID_ARGUMENT);

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

	/* check that named entry covers entire object ? */
	if (mem_entry->offset != 0 || object->vo_size != mem_entry->size) {
		vm_object_unlock(object);
		named_entry_unlock(mem_entry);
		return KERN_INVALID_ARGUMENT;
	}

	named_entry_unlock(mem_entry);

	kr = vm_object_purgable_control(object, control, state);

	vm_object_unlock(object);

	return kr;
}