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
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  int /*<<< orphan*/ * vm_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
#define  VM_PAGEOUT_PB_CONSIDER_WAKING_COMPACTOR_SWAPPER 130 
#define  VM_PAGEOUT_PB_NO_ACTION 129 
#define  VM_PAGEOUT_PB_THREAD_YIELD 128 
 int /*<<< orphan*/  thread_yield_internal (int) ; 
 int /*<<< orphan*/  vm_consider_waking_compactor_swapper () ; 
 int /*<<< orphan*/  vm_object_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_free_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_lock_queues () ; 
 int /*<<< orphan*/  vm_page_unlock_queues () ; 

__attribute__((used)) static void
vm_pageout_prepare_to_block(vm_object_t *object, int *delayed_unlock,
			    vm_page_t *local_freeq, int *local_freed, int action)
{
	vm_page_unlock_queues();

	if (*object != NULL) {
		vm_object_unlock(*object);
		*object = NULL;
	}
	if (*local_freeq) {

		vm_page_free_list(*local_freeq, TRUE);

		*local_freeq = NULL;
		*local_freed = 0;
	}
	*delayed_unlock = 1;

	switch (action) {

	case VM_PAGEOUT_PB_CONSIDER_WAKING_COMPACTOR_SWAPPER:
		vm_consider_waking_compactor_swapper();
		break;
	case VM_PAGEOUT_PB_THREAD_YIELD:
		thread_yield_internal(1);
		break;
	case VM_PAGEOUT_PB_NO_ACTION:
	default:
		break;
	}
	vm_page_lock_queues();
}