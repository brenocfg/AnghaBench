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
struct swapfile {int swp_flags; int /*<<< orphan*/  swp_queue; } ;
typedef  int /*<<< orphan*/  queue_entry_t ;
typedef  int /*<<< orphan*/  event_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int SWAP_READY ; 
 int SWAP_RECLAIM ; 
 scalar_t__ TRUE ; 
 scalar_t__ VM_SWAP_SHOULD_RECLAIM () ; 
 scalar_t__ VM_SWAP_SHOULD_TRIM (struct swapfile*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ delayed_trim_handling_in_progress ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ queue_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ queue_first (int /*<<< orphan*/ *) ; 
 scalar_t__ queue_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swf_global_queue ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_swap_data_lock ; 
 int /*<<< orphan*/  vm_swap_do_delayed_trim (struct swapfile*) ; 
 int /*<<< orphan*/  vm_swapfile_gc_needed ; 
 int /*<<< orphan*/  vm_swapfile_gc_thread_running ; 

__attribute__((used)) static void
vm_swap_handle_delayed_trims(boolean_t force_now)
{
	struct swapfile *swf = NULL;

	/*
	 * serialize the race between us and vm_swap_reclaim...
	 * if vm_swap_reclaim wins it will turn off SWAP_READY
	 * on the victim it has chosen... we can just skip over
	 * that file since vm_swap_reclaim will first process
	 * all of the delayed trims associated with it
	 */
	lck_mtx_lock(&vm_swap_data_lock);

	delayed_trim_handling_in_progress = TRUE;

	lck_mtx_unlock(&vm_swap_data_lock);

	/*
	 * no need to hold the lock to walk the swf list since
	 * vm_swap_create (the only place where we add to this list)
	 * is run on the same thread as this function
	 * and vm_swap_reclaim doesn't remove items from this list
	 * instead marking them with SWAP_REUSE for future re-use
	 */
	swf = (struct swapfile*) queue_first(&swf_global_queue);

	while (queue_end(&swf_global_queue, (queue_entry_t)swf) == FALSE) {

		if ((swf->swp_flags & SWAP_READY) && (force_now == TRUE || VM_SWAP_SHOULD_TRIM(swf))) {

			assert(!(swf->swp_flags & SWAP_RECLAIM));
			vm_swap_do_delayed_trim(swf);
		}
		swf = (struct swapfile*) queue_next(&swf->swp_queue);
	}
	lck_mtx_lock(&vm_swap_data_lock);

	delayed_trim_handling_in_progress = FALSE;
	thread_wakeup((event_t) &delayed_trim_handling_in_progress);

	if (VM_SWAP_SHOULD_RECLAIM() && !vm_swapfile_gc_thread_running)
		thread_wakeup((event_t) &vm_swapfile_gc_needed);

	lck_mtx_unlock(&vm_swap_data_lock);

}