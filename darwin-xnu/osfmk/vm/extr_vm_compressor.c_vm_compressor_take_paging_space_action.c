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
typedef  int /*<<< orphan*/  UInt32 ;

/* Variables and functions */
 scalar_t__ OSCompareAndSwap (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 scalar_t__ kill_on_no_paging_space ; 
 int /*<<< orphan*/  memorystatus_send_low_swap_note () ; 
 scalar_t__ no_paging_space_action () ; 
 scalar_t__ no_paging_space_action_in_progress ; 

__attribute__((used)) static void
vm_compressor_take_paging_space_action(void)
{
	if (no_paging_space_action_in_progress == 0) {

		if (OSCompareAndSwap(0, 1, (UInt32 *)&no_paging_space_action_in_progress)) {

			if (no_paging_space_action()) {
#if DEVELOPMENT || DEBUG
				if (kill_on_no_paging_space == TRUE) {
					/*
					 * Since we are choosing to always kill a process, we don't need the
					 * "out of application memory" dialog box in this mode. And, hence we won't
					 * send the knote.
					 */
					no_paging_space_action_in_progress = 0;
					return;
				}
#endif /* DEVELOPMENT || DEBUG */
				memorystatus_send_low_swap_note();
			}

			no_paging_space_action_in_progress = 0;
		}
	}
}