#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_continue_t ;
typedef  int /*<<< orphan*/  event_t ;
typedef  void* clock_sec_t ;
typedef  int /*<<< orphan*/  clock_nsec_t ;
struct TYPE_2__ {int /*<<< orphan*/  options; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HIBLOG (char*,unsigned long) ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 int /*<<< orphan*/  TH_OPT_VMPRIV ; 
 scalar_t__ TRUE ; 
 scalar_t__ VM_SWAP_SHOULD_CREATE (void*) ; 
 int /*<<< orphan*/  assert_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clock_get_system_nanotime (void**,int /*<<< orphan*/ *) ; 
 TYPE_1__* current_thread () ; 
 scalar_t__ hibernate_in_progress_with_pinned_swap ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_swap_create_file () ; 
 int /*<<< orphan*/  vm_swap_data_lock ; 
 int /*<<< orphan*/  vm_swap_handle_delayed_trims (scalar_t__) ; 
 int /*<<< orphan*/  vm_swapfile_create_needed ; 
 int /*<<< orphan*/  vm_swapfile_create_thread_awakened ; 
 int vm_swapfile_create_thread_running ; 
 void* vm_swapfile_last_failed_to_create_ts ; 
 void* vm_swapfile_last_successful_create_ts ; 

__attribute__((used)) static void
vm_swapfile_create_thread(void)
{
	clock_sec_t	sec;
	clock_nsec_t	nsec;

	current_thread()->options |= TH_OPT_VMPRIV;

	vm_swapfile_create_thread_awakened++;
	vm_swapfile_create_thread_running = 1;

	while (TRUE) {
		/*
		 * walk through the list of swap files
		 * and do the delayed frees/trims for
		 * any swap file whose count of delayed
		 * frees is above the batch limit
		 */
		vm_swap_handle_delayed_trims(FALSE);

		lck_mtx_lock(&vm_swap_data_lock);

		if (hibernate_in_progress_with_pinned_swap == TRUE)
			break;

		clock_get_system_nanotime(&sec, &nsec);

		if (VM_SWAP_SHOULD_CREATE(sec) == 0)
			break;

		lck_mtx_unlock(&vm_swap_data_lock);

		if (vm_swap_create_file() == FALSE) {
			vm_swapfile_last_failed_to_create_ts = sec;
			HIBLOG("vm_swap_create_file failed @ %lu secs\n", (unsigned long)sec);

		} else
			vm_swapfile_last_successful_create_ts = sec;
	}
	vm_swapfile_create_thread_running = 0;

	if (hibernate_in_progress_with_pinned_swap == TRUE)
		thread_wakeup((event_t)&hibernate_in_progress_with_pinned_swap);

	assert_wait((event_t)&vm_swapfile_create_needed, THREAD_UNINT);

	lck_mtx_unlock(&vm_swap_data_lock);

	thread_block((thread_continue_t)vm_swapfile_create_thread);
	
	/* NOTREACHED */
}