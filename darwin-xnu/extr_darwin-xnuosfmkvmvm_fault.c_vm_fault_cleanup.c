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
typedef  scalar_t__ vm_page_t ;
typedef  int /*<<< orphan*/  vm_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_PAGE_FREE (scalar_t__) ; 
 scalar_t__ VM_PAGE_NULL ; 
 int /*<<< orphan*/  VM_PAGE_OBJECT (scalar_t__) ; 
 int /*<<< orphan*/  vm_object_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_paging_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_unlock (int /*<<< orphan*/ ) ; 

void
vm_fault_cleanup(
	vm_object_t	object,
	vm_page_t	top_page)
{
	vm_object_paging_end(object);
 	vm_object_unlock(object);

	if (top_page != VM_PAGE_NULL) {
	        object = VM_PAGE_OBJECT(top_page);

		vm_object_lock(object);
		VM_PAGE_FREE(top_page);
		vm_object_paging_end(object);
		vm_object_unlock(object);
	}
}