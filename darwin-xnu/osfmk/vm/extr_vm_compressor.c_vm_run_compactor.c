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
typedef  int /*<<< orphan*/  event_t ;
struct TYPE_2__ {scalar_t__ vm_restricted_to_single_processor; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 int /*<<< orphan*/  assert_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_list_lock ; 
 scalar_t__ c_minor_count ; 
 scalar_t__ c_segment_count ; 
 int compaction_swapper_running ; 
 scalar_t__ fastwake_warmup ; 
 int /*<<< orphan*/  lck_mtx_lock_spin_always (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock_always (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_compressor_do_delayed_compactions (scalar_t__) ; 
 TYPE_1__ vm_pageout_state ; 
 int /*<<< orphan*/  vm_run_compactor_already_running ; 
 int /*<<< orphan*/  vm_run_compactor_did_compact ; 
 int /*<<< orphan*/  vm_run_compactor_empty_minor_q ; 
 int /*<<< orphan*/  vm_run_compactor_waited ; 

void
vm_run_compactor(void)
{
	if (c_segment_count == 0)
		return;

	lck_mtx_lock_spin_always(c_list_lock);

	if (c_minor_count == 0) {
		vm_run_compactor_empty_minor_q++;

		lck_mtx_unlock_always(c_list_lock);
		return;
	}
	if (compaction_swapper_running) {

		if (vm_pageout_state.vm_restricted_to_single_processor == FALSE) {
			vm_run_compactor_already_running++;

			lck_mtx_unlock_always(c_list_lock);
			return;
		}
		vm_run_compactor_waited++;

		assert_wait((event_t)&compaction_swapper_running, THREAD_UNINT);

		lck_mtx_unlock_always(c_list_lock);
		
		thread_block(THREAD_CONTINUE_NULL);

		return;
	}
	vm_run_compactor_did_compact++;

	fastwake_warmup = FALSE;
	compaction_swapper_running = 1;

	vm_compressor_do_delayed_compactions(FALSE);

	compaction_swapper_running = 0;

	lck_mtx_unlock_always(c_list_lock);

	thread_wakeup((event_t)&compaction_swapper_running);
}