#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_prot_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  int /*<<< orphan*/  vm_object_offset_t ;
typedef  TYPE_3__* vm_named_entry_t ;
typedef  scalar_t__ memory_object_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
typedef  scalar_t__ host_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_10__ {TYPE_2__* object; } ;
struct TYPE_12__ {int protection; int ref_count; scalar_t__ internal; TYPE_1__ backing; int /*<<< orphan*/  is_sub_map; scalar_t__ offset; int /*<<< orphan*/  size; } ;
struct TYPE_11__ {scalar_t__ copy_strategy; scalar_t__ internal; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 unsigned int GET_MAP_MEM (int) ; 
 scalar_t__ HOST_NULL ; 
 scalar_t__ KERN_FAILURE ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_INVALID_HOST ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ MEMORY_OBJECT_COPY_DELAY ; 
 scalar_t__ MEMORY_OBJECT_COPY_SYMMETRIC ; 
 scalar_t__ MEMORY_OBJECT_NULL ; 
 int /*<<< orphan*/  SET_MAP_MEM (unsigned int,int) ; 
 TYPE_2__* VM_OBJECT_NULL ; 
 int VM_PROT_ALL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ mach_memory_entry_allocate (TYPE_3__**,int /*<<< orphan*/ *) ; 
 TYPE_2__* memory_object_to_vm_object (scalar_t__) ; 
 TYPE_2__* vm_object_allocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_deallocate (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_reference (TYPE_2__*) ; 

kern_return_t
mach_memory_object_memory_entry_64(
	host_t			host,
	boolean_t		internal,
	vm_object_offset_t	size,
	vm_prot_t		permission,
 	memory_object_t		pager,
	ipc_port_t		*entry_handle)
{
	unsigned int		access;
	vm_named_entry_t	user_entry;
	ipc_port_t		user_handle;
	vm_object_t		object;

        if (host == HOST_NULL)
                return(KERN_INVALID_HOST);

	if (pager == MEMORY_OBJECT_NULL && internal) {
		object = vm_object_allocate(size);
		if (object->copy_strategy == MEMORY_OBJECT_COPY_SYMMETRIC) {
			object->copy_strategy = MEMORY_OBJECT_COPY_DELAY;
		}
	} else {
		object = memory_object_to_vm_object(pager);
		if (object != VM_OBJECT_NULL) {
			vm_object_reference(object);
		}
	}
	if (object == VM_OBJECT_NULL) {
		return KERN_INVALID_ARGUMENT;
	}

	if (mach_memory_entry_allocate(&user_entry, &user_handle)
	    != KERN_SUCCESS) {
		vm_object_deallocate(object);
		return KERN_FAILURE;
	}

	user_entry->size = size;
	user_entry->offset = 0;
	user_entry->protection = permission & VM_PROT_ALL;
	access = GET_MAP_MEM(permission);
	SET_MAP_MEM(access, user_entry->protection);
	user_entry->is_sub_map = FALSE;
	assert(user_entry->ref_count == 1);

	user_entry->backing.object = object;
	user_entry->internal = object->internal;
	assert(object->internal == internal);

	*entry_handle = user_handle;
	return KERN_SUCCESS;
}