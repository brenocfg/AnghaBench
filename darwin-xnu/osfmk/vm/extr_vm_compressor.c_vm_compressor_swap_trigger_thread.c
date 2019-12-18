#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_continue_t ;
typedef  int /*<<< orphan*/  event_t ;
struct TYPE_5__ {int /*<<< orphan*/  options; } ;
struct TYPE_4__ {scalar_t__ vm_restricted_to_single_processor; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 int /*<<< orphan*/  TH_OPT_VMPRIV ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_compressor_swap_trigger ; 
 int /*<<< orphan*/  c_list_lock ; 
 int /*<<< orphan*/  compaction_swap_trigger_thread_awakened ; 
 scalar_t__ compaction_swapper_awakened ; 
 scalar_t__ compaction_swapper_init_now ; 
 int compaction_swapper_running ; 
 TYPE_2__* current_thread () ; 
 int /*<<< orphan*/  lck_mtx_lock_spin_always (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock_always (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_set_thread_name (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  thread_vm_bind_group_add () ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_compaction_swapper_do_init () ; 
 int /*<<< orphan*/  vm_compressor_compact_and_swap (int /*<<< orphan*/ ) ; 
 TYPE_1__ vm_pageout_state ; 

__attribute__((used)) static void
vm_compressor_swap_trigger_thread(void)
{
	current_thread()->options |= TH_OPT_VMPRIV;

	/*
	 * compaction_swapper_init_now is set when the first call to
	 * vm_consider_waking_compactor_swapper is made from 
	 * vm_pageout_scan... since this function is called upon 
	 * thread creation, we want to make sure to delay adjusting
	 * the tuneables until we are awakened via vm_pageout_scan
	 * so that we are at a point where the vm_swapfile_open will
	 * be operating on the correct directory (in case the default
	 * of /var/vm/  is overridden by the dymanic_pager 
	 */
	if (compaction_swapper_init_now) {
		vm_compaction_swapper_do_init();

		if (vm_pageout_state.vm_restricted_to_single_processor == TRUE)
			thread_vm_bind_group_add();
		thread_set_thread_name(current_thread(), "VM_cswap_trigger");
		compaction_swapper_init_now = 0;
	}
	lck_mtx_lock_spin_always(c_list_lock);

	compaction_swap_trigger_thread_awakened++;
	compaction_swapper_awakened = 0;

	if (compaction_swapper_running == 0) {

		compaction_swapper_running = 1;

		vm_compressor_compact_and_swap(FALSE);

		compaction_swapper_running = 0;
	}
	assert_wait((event_t)&c_compressor_swap_trigger, THREAD_UNINT);

	if (compaction_swapper_running == 0)
		thread_wakeup((event_t)&compaction_swapper_running);

	lck_mtx_unlock_always(c_list_lock);
		
	thread_block((thread_continue_t)vm_compressor_swap_trigger_thread);
	
	/* NOTREACHED */
}