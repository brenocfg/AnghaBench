#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  TYPE_4__* task_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_9__ {int tep_darwinbg; int tep_sup_active; scalar_t__ tep_tal_engaged; } ;
struct TYPE_8__ {scalar_t__ trp_role; int trp_boosted; } ;
struct TYPE_11__ {TYPE_3__* task_imp_base; int /*<<< orphan*/  bsd_info; TYPE_2__ effective_policy; TYPE_1__ requested_policy; scalar_t__ frozen; scalar_t__ pidsuspended; int /*<<< orphan*/  active; } ;
struct TYPE_10__ {scalar_t__ iit_live_donor; scalar_t__ iit_donor; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TASK_FOREGROUND_APPLICATION ; 
 int kFrozen ; 
 int kPidSuspended ; 
 int kTaskAllowIdleExit ; 
 int kTaskDarwinBG ; 
 int kTaskIsBoosted ; 
 int kTaskIsDirty ; 
 int kTaskIsDirtyTracked ; 
 int kTaskIsForeground ; 
 int kTaskIsImpDonor ; 
 int kTaskIsLiveImpDonor ; 
 int kTaskIsSuppressed ; 
 int kTaskTALEngaged ; 
 int kTerminatedSnapshot ; 
 int kUser64_p ; 
 int /*<<< orphan*/  memorystatus_proc_flags_unsafe (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ proc_exiting (int /*<<< orphan*/ ) ; 
 scalar_t__ task_has_64Bit_addr (TYPE_4__*) ; 
 scalar_t__ task_is_a_corpse (TYPE_4__*) ; 
 int workqueue_get_pwq_state_kdp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
kcdata_get_task_ss_flags(task_t task)
{
	uint64_t ss_flags = 0;
	boolean_t task_64bit_addr = task_has_64Bit_addr(task);

	if (task_64bit_addr)
		ss_flags |= kUser64_p;
	if (!task->active || task_is_a_corpse(task) || proc_exiting(task->bsd_info))
		ss_flags |= kTerminatedSnapshot;
	if (task->pidsuspended)
		ss_flags |= kPidSuspended;
	if (task->frozen)
		ss_flags |= kFrozen;
	if (task->effective_policy.tep_darwinbg == 1)
		ss_flags |= kTaskDarwinBG;
	if (task->requested_policy.trp_role == TASK_FOREGROUND_APPLICATION)
		ss_flags |= kTaskIsForeground;
	if (task->requested_policy.trp_boosted == 1)
		ss_flags |= kTaskIsBoosted;
	if (task->effective_policy.tep_sup_active == 1)
		ss_flags |= kTaskIsSuppressed;
#if CONFIG_MEMORYSTATUS

	boolean_t dirty = FALSE, dirty_tracked = FALSE, allow_idle_exit = FALSE;
	memorystatus_proc_flags_unsafe(task->bsd_info, &dirty, &dirty_tracked, &allow_idle_exit);
	if (dirty)
		ss_flags |= kTaskIsDirty;
	if (dirty_tracked)
		ss_flags |= kTaskIsDirtyTracked;
	if (allow_idle_exit)
		ss_flags |= kTaskAllowIdleExit;

#endif
	if (task->effective_policy.tep_tal_engaged)
		ss_flags |= kTaskTALEngaged;

	ss_flags |= (0x7 & workqueue_get_pwq_state_kdp(task->bsd_info)) << 17;

#if IMPORTANCE_INHERITANCE
	if (task->task_imp_base) {
		if (task->task_imp_base->iit_donor)
			ss_flags |= kTaskIsImpDonor;
		if (task->task_imp_base->iit_live_donor)
			ss_flags |= kTaskIsLiveImpDonor;
	}
#endif
	return ss_flags;
}