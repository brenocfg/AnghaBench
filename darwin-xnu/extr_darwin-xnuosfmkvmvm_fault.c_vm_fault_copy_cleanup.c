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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  vm_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_WAKEUP_DONE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PAGE_OBJECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PAGE_PAGEABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_fault_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_activate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_lockspin_queues () ; 
 int /*<<< orphan*/  vm_page_unlock_queues () ; 

__attribute__((used)) static void
vm_fault_copy_cleanup(
	vm_page_t	page,
	vm_page_t	top_page)
{
	vm_object_t	object = VM_PAGE_OBJECT(page);

	vm_object_lock(object);
	PAGE_WAKEUP_DONE(page);
	if ( !VM_PAGE_PAGEABLE(page)) {
		vm_page_lockspin_queues();
		if ( !VM_PAGE_PAGEABLE(page)) {
			vm_page_activate(page);
		}
		vm_page_unlock_queues();
	}
	vm_fault_cleanup(object, top_page);
}