#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* task_t ;
typedef  TYPE_2__* task_pend_token_t ;
struct TYPE_8__ {scalar_t__ tpt_update_coal_sfi; scalar_t__ tpt_update_live_donor; scalar_t__ tpt_update_watchers; scalar_t__ tpt_update_timers; scalar_t__ tpt_update_sockets; } ;
struct TYPE_7__ {int /*<<< orphan*/ * coalition; int /*<<< orphan*/  bsd_info; } ;

/* Variables and functions */
 size_t COALITION_TYPE_RESOURCE ; 
 int /*<<< orphan*/  THREAD_NULL ; 
 int /*<<< orphan*/  apply_appstate_watchers (TYPE_1__*) ; 
 int /*<<< orphan*/  coalition_for_each_task (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ml_timer_evaluate () ; 
 int /*<<< orphan*/  proc_apply_task_networkbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_importance_update_live_donor (TYPE_1__*) ; 
 int /*<<< orphan*/  task_sfi_reevaluate_cb ; 

void
task_policy_update_complete_unlocked(task_t task, task_pend_token_t pend_token)
{
#ifdef MACH_BSD
	if (pend_token->tpt_update_sockets)
		proc_apply_task_networkbg(task->bsd_info, THREAD_NULL);
#endif /* MACH_BSD */

	/* The timer throttle has been removed or reduced, we need to look for expired timers and fire them */
	if (pend_token->tpt_update_timers)
		ml_timer_evaluate();

#if CONFIG_EMBEDDED
	if (pend_token->tpt_update_watchers)
		apply_appstate_watchers(task);
#endif /* CONFIG_EMBEDDED */

	if (pend_token->tpt_update_live_donor)
		task_importance_update_live_donor(task);

#if CONFIG_SCHED_SFI
	/* use the resource coalition for SFI re-evaluation */
	if (pend_token->tpt_update_coal_sfi)
		coalition_for_each_task(task->coalition[COALITION_TYPE_RESOURCE],
					(void *)task, task_sfi_reevaluate_cb);
#endif /* CONFIG_SCHED_SFI */

}