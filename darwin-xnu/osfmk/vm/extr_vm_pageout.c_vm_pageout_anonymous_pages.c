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

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ VM_CONFIG_COMPRESSOR_IS_PRESENT ; 
 scalar_t__ VM_CONFIG_SWAP_IS_PRESENT ; 
 int /*<<< orphan*/  vm_consider_swapping () ; 
 int /*<<< orphan*/  vm_page_active_count ; 
 int /*<<< orphan*/  vm_page_anonymous_count ; 
 int /*<<< orphan*/  vm_page_lock_queues () ; 
 int /*<<< orphan*/  vm_page_queue_active ; 
 int /*<<< orphan*/  vm_page_queue_anonymous ; 
 int /*<<< orphan*/  vm_page_queue_throttled ; 
 int /*<<< orphan*/  vm_page_throttled_count ; 
 int /*<<< orphan*/  vm_page_unlock_queues () ; 
 scalar_t__ vm_pageout_anonymous_pages_active ; 
 int /*<<< orphan*/  vm_pageout_page_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
vm_pageout_anonymous_pages()
{
	if (VM_CONFIG_COMPRESSOR_IS_PRESENT) {

		vm_page_lock_queues();

		if (vm_pageout_anonymous_pages_active == TRUE) {
			vm_page_unlock_queues();
			return;
		}
		vm_pageout_anonymous_pages_active = TRUE;
		vm_page_unlock_queues();

		vm_pageout_page_queue(&vm_page_queue_throttled, vm_page_throttled_count);
		vm_pageout_page_queue(&vm_page_queue_anonymous, vm_page_anonymous_count);
		vm_pageout_page_queue(&vm_page_queue_active, vm_page_active_count);

		if (VM_CONFIG_SWAP_IS_PRESENT)
			vm_consider_swapping();

		vm_page_lock_queues();
		vm_pageout_anonymous_pages_active = FALSE;
		vm_page_unlock_queues();
	}
}