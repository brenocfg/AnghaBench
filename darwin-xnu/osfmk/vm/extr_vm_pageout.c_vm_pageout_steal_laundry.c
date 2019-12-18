#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  vmp_free_when_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  vm_page_lockspin_queues () ; 
 int /*<<< orphan*/  vm_page_unlock_queues () ; 
 int /*<<< orphan*/  vm_pageout_throttle_up (TYPE_1__*) ; 

void
vm_pageout_steal_laundry(vm_page_t page, boolean_t queues_locked)
{
	if (!queues_locked) {
		vm_page_lockspin_queues();
	}

	page->vmp_free_when_done = FALSE;
	/*
	 * need to drop the laundry count...
	 * we may also need to remove it
	 * from the I/O paging queue...
	 * vm_pageout_throttle_up handles both cases
	 *
	 * the laundry and pageout_queue flags are cleared...
	 */
	vm_pageout_throttle_up(page);

	if (!queues_locked) {
		vm_page_unlock_queues();
	}
}