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
typedef  int /*<<< orphan*/  uint32_t ;
struct vm_pageout_queue {scalar_t__ pgo_inited; scalar_t__ pgo_lowpriority; int /*<<< orphan*/  pgo_tid; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACE_VM (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  TASK_POLICY_EXTERNAL ; 
 int /*<<< orphan*/  TASK_POLICY_IO ; 
 int /*<<< orphan*/  THROTTLE_LEVEL_PAGEOUT_THROTTLED ; 
 int /*<<< orphan*/  THROTTLE_LEVEL_PAGEOUT_UNTHROTTLED ; 
 scalar_t__ TRUE ; 
 scalar_t__ hibernate_cleaning_in_progress ; 
 int /*<<< orphan*/  kernel_task ; 
 int /*<<< orphan*/  laundrythrottle ; 
 int /*<<< orphan*/  laundryunthrottle ; 
 int /*<<< orphan*/  proc_set_thread_policy_with_tid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_lock_queues () ; 
 int /*<<< orphan*/  vm_page_unlock_queues () ; 

__attribute__((used)) static void
vm_pageout_adjust_eq_iothrottle(struct vm_pageout_queue *eq, boolean_t req_lowpriority)
{
	uint32_t 	policy;

	if (hibernate_cleaning_in_progress == TRUE)
		req_lowpriority = FALSE;

	if (eq->pgo_inited == TRUE && eq->pgo_lowpriority != req_lowpriority) {

		vm_page_unlock_queues();

		if (req_lowpriority == TRUE) {
			policy = THROTTLE_LEVEL_PAGEOUT_THROTTLED;
			DTRACE_VM(laundrythrottle);
		} else {
			policy = THROTTLE_LEVEL_PAGEOUT_UNTHROTTLED;
			DTRACE_VM(laundryunthrottle);
		}
		proc_set_thread_policy_with_tid(kernel_task, eq->pgo_tid,
						TASK_POLICY_EXTERNAL, TASK_POLICY_IO, policy);

		eq->pgo_lowpriority = req_lowpriority;

		vm_page_lock_queues();
	}
}