#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ vm_object_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  VM_MAP_REMOVE_NO_FLAGS ; 
 scalar_t__ VM_OBJECT_NULL ; 
 scalar_t__ VM_PAGING_NUM_PAGES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  kernel_map ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  pmap_remove (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_wakeup (scalar_t__*) ; 
 scalar_t__ vm_map_remove (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_lock (scalar_t__) ; 
 int /*<<< orphan*/  vm_object_unlock (scalar_t__) ; 
 scalar_t__ vm_paging_base_address ; 
 int /*<<< orphan*/  vm_paging_lock ; 
 int /*<<< orphan*/ * vm_paging_page_inuse ; 
 scalar_t__ vm_paging_page_waiter ; 

void
vm_paging_unmap_object(
	vm_object_t	object,
	vm_map_offset_t	start,
	vm_map_offset_t	end)
{
	kern_return_t	kr;
	int		i;

	if ((vm_paging_base_address == 0) ||
	    (start < vm_paging_base_address) ||
	    (end > (vm_paging_base_address
		     + (VM_PAGING_NUM_PAGES * PAGE_SIZE)))) {
		/*
		 * We didn't use our pre-allocated pool of
		 * kernel virtual address.  Deallocate the
		 * virtual memory.
		 */
		if (object != VM_OBJECT_NULL) {
			vm_object_unlock(object);
		}
		kr = vm_map_remove(kernel_map, start, end,
				   VM_MAP_REMOVE_NO_FLAGS);
		if (object != VM_OBJECT_NULL) {
			vm_object_lock(object);
		}
		assert(kr == KERN_SUCCESS);
	} else {
		/*
		 * We used a kernel virtual address from our
		 * pre-allocated pool.  Put it back in the pool
		 * for next time.
		 */
		assert(end - start == PAGE_SIZE);
		i = (int) ((start - vm_paging_base_address) >> PAGE_SHIFT);
		assert(i >= 0 && i < VM_PAGING_NUM_PAGES);

		/* undo the pmap mapping */
		pmap_remove(kernel_pmap, start, end);

		simple_lock(&vm_paging_lock);
		vm_paging_page_inuse[i] = FALSE;
		if (vm_paging_page_waiter) {
			thread_wakeup(&vm_paging_page_waiter);
		}
		simple_unlock(&vm_paging_lock);
	}
}