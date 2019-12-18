#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  TYPE_1__* vm_object_t ;
typedef  int /*<<< orphan*/  ppnum_t ;
typedef  int /*<<< orphan*/  memory_object_offset_t ;
typedef  int /*<<< orphan*/  memory_object_control_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ boolean_t ;
typedef  int /*<<< orphan*/  addr64_t ;
struct TYPE_6__ {scalar_t__ private; } ;

/* Variables and functions */
 scalar_t__ KERN_FAILURE ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  kernel_pmap ; 
 TYPE_1__* memory_object_control_to_vm_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_find_phys (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_lock (TYPE_1__*) ; 
 scalar_t__ vm_object_populate_with_private (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_1__*) ; 

kern_return_t pager_map_to_phys_contiguous(
	memory_object_control_t	object,
	memory_object_offset_t	offset,
	addr64_t		base_vaddr,
	vm_size_t		size)
{
	ppnum_t page_num;
	boolean_t clobbered_private;
	kern_return_t retval;
	vm_object_t pager_object;

	page_num = pmap_find_phys(kernel_pmap, base_vaddr);

	if (!page_num) {
		retval = KERN_FAILURE;
		goto out;
	}

	pager_object = memory_object_control_to_vm_object(object);

	if (!pager_object) {
		retval = KERN_FAILURE;
		goto out;
	}

	clobbered_private = pager_object->private;
	if (pager_object->private != TRUE) {
		vm_object_lock(pager_object);
		pager_object->private = TRUE;
		vm_object_unlock(pager_object);
	}
	retval = vm_object_populate_with_private(pager_object, offset, page_num, size);

	if (retval != KERN_SUCCESS) {
		if (pager_object->private != clobbered_private) {
			vm_object_lock(pager_object);
			pager_object->private = clobbered_private;
			vm_object_unlock(pager_object);
		}
	}

out:
	return retval;
}