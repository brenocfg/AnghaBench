#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_prot_t ;
typedef  TYPE_1__* vm_object_t ;
typedef  int /*<<< orphan*/  memory_object_size_t ;
typedef  int /*<<< orphan*/  memory_object_return_t ;
typedef  int /*<<< orphan*/  memory_object_offset_t ;
typedef  int /*<<< orphan*/  memory_object_control_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_10__ {scalar_t__ paging_offset; scalar_t__ copy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int MEMORY_OBJECT_DATA_FLUSH ; 
 int MEMORY_OBJECT_DATA_FLUSH_ALL ; 
 int /*<<< orphan*/  MEMORY_OBJECT_RETURN_NONE ; 
 int /*<<< orphan*/  REAP_DATA_FLUSH ; 
 TYPE_1__* VM_OBJECT_NULL ; 
 int VM_PROT_ALL ; 
 int VM_PROT_NO_CHANGE ; 
 TYPE_1__* memory_object_control_to_vm_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_page_64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_paging_begin (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_paging_end (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_reap_pages (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_update (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int,int) ; 

kern_return_t
memory_object_lock_request(
	memory_object_control_t		control,
	memory_object_offset_t		offset,
	memory_object_size_t		size,
	memory_object_offset_t	*	resid_offset,
	int			*	io_errno,
	memory_object_return_t		should_return,
	int				flags,
	vm_prot_t			prot)
{
	vm_object_t	object;

        /*
	 *	Check for bogus arguments.
	 */
	object = memory_object_control_to_vm_object(control);
	if (object == VM_OBJECT_NULL)
		return (KERN_INVALID_ARGUMENT);

	if ((prot & ~VM_PROT_ALL) != 0 && prot != VM_PROT_NO_CHANGE)
		return (KERN_INVALID_ARGUMENT);

	size = round_page_64(size);

	/*
	 *	Lock the object, and acquire a paging reference to
	 *	prevent the memory_object reference from being released.
	 */
	vm_object_lock(object);
	vm_object_paging_begin(object);

	if (flags & MEMORY_OBJECT_DATA_FLUSH_ALL) {
		if ((should_return != MEMORY_OBJECT_RETURN_NONE) || offset || object->copy) {
			flags &= ~MEMORY_OBJECT_DATA_FLUSH_ALL;
			flags |= MEMORY_OBJECT_DATA_FLUSH;
		}
	}
	offset -= object->paging_offset;

	if (flags & MEMORY_OBJECT_DATA_FLUSH_ALL)
		vm_object_reap_pages(object, REAP_DATA_FLUSH);
	else
		(void)vm_object_update(object, offset, size, resid_offset,
				       io_errno, should_return, flags, prot);

	vm_object_paging_end(object);
	vm_object_unlock(object);

	return (KERN_SUCCESS);
}