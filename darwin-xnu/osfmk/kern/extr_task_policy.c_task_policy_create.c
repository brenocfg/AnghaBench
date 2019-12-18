#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* task_t ;
struct TYPE_13__ {scalar_t__ trp_apptype; scalar_t__ trp_boosted; int /*<<< orphan*/  trp_qos_clamp; int /*<<< orphan*/  trp_terminated; int /*<<< orphan*/  trp_bg_iotier; int /*<<< orphan*/  trp_ext_iopassive; int /*<<< orphan*/  trp_int_iopassive; int /*<<< orphan*/  trp_ext_iotier; int /*<<< orphan*/  trp_int_iotier; int /*<<< orphan*/  trp_ext_darwinbg; int /*<<< orphan*/  trp_int_darwinbg; } ;
struct TYPE_14__ {int /*<<< orphan*/  priority; TYPE_1__ requested_policy; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  FALSE ; 
 int IMPORTANCE_CODE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IMP_UPDATE ; 
 int IMP_UPDATE_TASK_CREATE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TASK_APPTYPE_DAEMON_ADAPTIVE ; 
 scalar_t__ TASK_APPTYPE_DAEMON_BACKGROUND ; 
 scalar_t__ TASK_APPTYPE_DAEMON_INTERACTIVE ; 
 int TASK_POLICY_TASK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  task_importance_mark_donor (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_importance_mark_receiver (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_importance_update_live_donor (TYPE_2__*) ; 
 int /*<<< orphan*/  task_is_exec_copy (TYPE_2__*) ; 
 int /*<<< orphan*/  task_pid (TYPE_2__*) ; 
 int /*<<< orphan*/  task_policy_update_internal_locked (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  teffective_0 (TYPE_2__*) ; 
 int /*<<< orphan*/  teffective_1 (TYPE_2__*) ; 

void
task_policy_create(task_t task, task_t parent_task)
{
	task->requested_policy.trp_apptype          = parent_task->requested_policy.trp_apptype;

	task->requested_policy.trp_int_darwinbg     = parent_task->requested_policy.trp_int_darwinbg;
	task->requested_policy.trp_ext_darwinbg     = parent_task->requested_policy.trp_ext_darwinbg;
	task->requested_policy.trp_int_iotier       = parent_task->requested_policy.trp_int_iotier;
	task->requested_policy.trp_ext_iotier       = parent_task->requested_policy.trp_ext_iotier;
	task->requested_policy.trp_int_iopassive    = parent_task->requested_policy.trp_int_iopassive;
	task->requested_policy.trp_ext_iopassive    = parent_task->requested_policy.trp_ext_iopassive;
	task->requested_policy.trp_bg_iotier        = parent_task->requested_policy.trp_bg_iotier;
	task->requested_policy.trp_terminated       = parent_task->requested_policy.trp_terminated;
	task->requested_policy.trp_qos_clamp        = parent_task->requested_policy.trp_qos_clamp;

	if (task->requested_policy.trp_apptype == TASK_APPTYPE_DAEMON_ADAPTIVE && !task_is_exec_copy(task)) {
		/* Do not update the apptype for exec copy task */
		if (parent_task->requested_policy.trp_boosted) {
			task->requested_policy.trp_apptype = TASK_APPTYPE_DAEMON_INTERACTIVE;
			task_importance_mark_donor(task, TRUE);
		} else {
			task->requested_policy.trp_apptype = TASK_APPTYPE_DAEMON_BACKGROUND;
			task_importance_mark_receiver(task, FALSE);
		}
	}

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
	                          (IMPORTANCE_CODE(IMP_UPDATE, (IMP_UPDATE_TASK_CREATE | TASK_POLICY_TASK))) | DBG_FUNC_START,
	                          task_pid(task), teffective_0(task),
	                          teffective_1(task), task->priority, 0);

	task_policy_update_internal_locked(task, TRUE, NULL);

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
	                          (IMPORTANCE_CODE(IMP_UPDATE, (IMP_UPDATE_TASK_CREATE | TASK_POLICY_TASK))) | DBG_FUNC_END,
	                          task_pid(task), teffective_0(task),
	                          teffective_1(task), task->priority, 0);

	task_importance_update_live_donor(task);
}