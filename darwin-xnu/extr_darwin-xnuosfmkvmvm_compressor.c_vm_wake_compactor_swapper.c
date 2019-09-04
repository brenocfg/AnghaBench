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
typedef  int /*<<< orphan*/  event_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  c_compressor_swap_trigger ; 
 int /*<<< orphan*/  c_list_lock ; 
 scalar_t__ c_minor_count ; 
 scalar_t__ c_segment_count ; 
 int compaction_swapper_awakened ; 
 scalar_t__ compaction_swapper_running ; 
 int /*<<< orphan*/  fastwake_warmup ; 
 int /*<<< orphan*/  lck_mtx_lock_spin_always (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock_always (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_compressor_needs_to_major_compact () ; 
 int /*<<< orphan*/  vm_wake_compactor_swapper_calls ; 

void
vm_wake_compactor_swapper(void)
{
	if (compaction_swapper_running || compaction_swapper_awakened || c_segment_count == 0)
		return;

	if (c_minor_count || vm_compressor_needs_to_major_compact()) {

		lck_mtx_lock_spin_always(c_list_lock);

		fastwake_warmup = FALSE;

		if (compaction_swapper_running == 0 && compaction_swapper_awakened == 0) {

			vm_wake_compactor_swapper_calls++;

			compaction_swapper_awakened = 1;
			thread_wakeup((event_t)&c_compressor_swap_trigger);
		}
		lck_mtx_unlock_always(c_list_lock);
	}
}