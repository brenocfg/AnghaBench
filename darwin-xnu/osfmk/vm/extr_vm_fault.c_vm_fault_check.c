#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wait_interrupt_t ;
typedef  scalar_t__ vm_page_t ;
typedef  TYPE_1__* vm_object_t ;
typedef  int /*<<< orphan*/  vm_fault_return_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_5__ {scalar_t__ shadow_severed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC_NONE ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VMF_CHECK_ZFDELAY ; 
 int /*<<< orphan*/  VM_DEBUG_EVENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_FAULT_INTERRUPTED ; 
 int /*<<< orphan*/  VM_FAULT_MEMORY_ERROR ; 
 int /*<<< orphan*/  VM_FAULT_MEMORY_SHORTAGE ; 
 int /*<<< orphan*/  VM_FAULT_SUCCESS ; 
 scalar_t__ VM_OBJECT_PURGEABLE_FAULT_ERROR (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_PAGE_FREE (scalar_t__) ; 
 scalar_t__ VM_PAGE_NULL ; 
 scalar_t__ current_thread_aborted () ; 
 int /*<<< orphan*/  delay (int) ; 
 int /*<<< orphan*/  thread_interrupt_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_fault_cleanup (TYPE_1__*,scalar_t__) ; 
 int vm_page_throttled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmf_check_zfdelay ; 

__attribute__((used)) static vm_fault_return_t
vm_fault_check(vm_object_t object, vm_page_t m, vm_page_t first_m, wait_interrupt_t interruptible_state, boolean_t page_throttle)
{
	int throttle_delay;

        if (object->shadow_severed ||
	    VM_OBJECT_PURGEABLE_FAULT_ERROR(object)) {
	        /*
		 * Either:
		 * 1. the shadow chain was severed,
		 * 2. the purgeable object is volatile or empty and is marked
		 *    to fault on access while volatile.
		 * Just have to return an error at this point
		 */
	        if (m != VM_PAGE_NULL)
		        VM_PAGE_FREE(m);
		vm_fault_cleanup(object, first_m);

		thread_interrupt_level(interruptible_state);

		return (VM_FAULT_MEMORY_ERROR);
	}
	if (page_throttle == TRUE) {
		if ((throttle_delay = vm_page_throttled(FALSE))) {
			/*
			 * we're throttling zero-fills...
			 * treat this as if we couldn't grab a page
			 */
			if (m != VM_PAGE_NULL)
				VM_PAGE_FREE(m);
			vm_fault_cleanup(object, first_m);

			VM_DEBUG_EVENT(vmf_check_zfdelay, VMF_CHECK_ZFDELAY, DBG_FUNC_NONE, throttle_delay, 0, 0, 0);

			delay(throttle_delay);

			if (current_thread_aborted()) {
				thread_interrupt_level(interruptible_state);
				return VM_FAULT_INTERRUPTED;
			}
			thread_interrupt_level(interruptible_state);

			return (VM_FAULT_MEMORY_SHORTAGE);
		}
	}
	return (VM_FAULT_SUCCESS);
}