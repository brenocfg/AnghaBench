#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* task_t ;
struct task_pend_token {int tpt_update_live_donor; } ;
typedef  int /*<<< orphan*/ * ipc_port_t ;
struct TYPE_18__ {int trp_tal_enabled; int trp_apptype; int trp_role; int trp_qos_clamp; } ;
struct TYPE_19__ {TYPE_1__ requested_policy; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  FALSE ; 
 int IMPORTANCE_CODE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IMP_TASK_APPTYPE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
#define  TASK_APPTYPE_APP_DEFAULT 134 
#define  TASK_APPTYPE_APP_TAL 133 
#define  TASK_APPTYPE_DAEMON_ADAPTIVE 132 
#define  TASK_APPTYPE_DAEMON_BACKGROUND 131 
#define  TASK_APPTYPE_DAEMON_INTERACTIVE 130 
#define  TASK_APPTYPE_DAEMON_STANDARD 129 
#define  TASK_APPTYPE_NONE 128 
 int TASK_FOREGROUND_APPLICATION ; 
 int TASK_UNSPECIFIED ; 
 int THREAD_QOS_UNSPECIFIED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ipc_importance_interactive_receiver ; 
 int /*<<< orphan*/  task_add_importance_watchport (TYPE_2__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  task_importance_hold_internal_assertion (TYPE_2__*,int) ; 
 int /*<<< orphan*/  task_importance_mark_denap_receiver (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_importance_mark_donor (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_importance_mark_live_donor (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_importance_mark_receiver (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int task_is_importance_receiver (TYPE_2__*) ; 
 int /*<<< orphan*/  task_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  task_pid (TYPE_2__*) ; 
 int /*<<< orphan*/  task_policy_update_complete_unlocked (TYPE_2__*,struct task_pend_token*) ; 
 int /*<<< orphan*/  task_policy_update_locked (TYPE_2__*,struct task_pend_token*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  trequested_0 (TYPE_2__*) ; 
 int /*<<< orphan*/  trequested_1 (TYPE_2__*) ; 

void
proc_set_task_spawnpolicy(task_t task, int apptype, int qos_clamp, int role,
                          ipc_port_t * portwatch_ports, int portwatch_count)
{
	struct task_pend_token pend_token = {};

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
				  (IMPORTANCE_CODE(IMP_TASK_APPTYPE, apptype)) | DBG_FUNC_START,
				  task_pid(task), trequested_0(task), trequested_1(task),
				  apptype, 0);

	switch (apptype) {
		case TASK_APPTYPE_APP_TAL:
		case TASK_APPTYPE_APP_DEFAULT:
			/* Apps become donors via the 'live-donor' flag instead of the static donor flag */
			task_importance_mark_donor(task, FALSE);
			task_importance_mark_live_donor(task, TRUE);
			task_importance_mark_receiver(task, FALSE);
#if CONFIG_EMBEDDED
			task_importance_mark_denap_receiver(task, FALSE);
#else
			/* Apps are de-nap recievers on desktop for suppression behaviors */
			task_importance_mark_denap_receiver(task, TRUE);
#endif /* CONFIG_EMBEDDED */
			break;

		case TASK_APPTYPE_DAEMON_INTERACTIVE:
			task_importance_mark_donor(task, TRUE);
			task_importance_mark_live_donor(task, FALSE);

			/* 
			 * A boot arg controls whether interactive daemons are importance receivers.
			 * Normally, they are not.  But for testing their behavior as an adaptive
			 * daemon, the boot-arg can be set.
			 *
			 * TODO: remove this when the interactive daemon audit period is over.
			 */
			task_importance_mark_receiver(task, /* FALSE */ ipc_importance_interactive_receiver);
			task_importance_mark_denap_receiver(task, FALSE);
			break;

		case TASK_APPTYPE_DAEMON_STANDARD:
			task_importance_mark_donor(task, TRUE);
			task_importance_mark_live_donor(task, FALSE);
			task_importance_mark_receiver(task, FALSE);
			task_importance_mark_denap_receiver(task, FALSE);
			break;

		case TASK_APPTYPE_DAEMON_ADAPTIVE:
			task_importance_mark_donor(task, FALSE);
			task_importance_mark_live_donor(task, FALSE);
			task_importance_mark_receiver(task, TRUE);
			task_importance_mark_denap_receiver(task, FALSE);
			break;

		case TASK_APPTYPE_DAEMON_BACKGROUND:
			task_importance_mark_donor(task, FALSE);
			task_importance_mark_live_donor(task, FALSE);
			task_importance_mark_receiver(task, FALSE);
			task_importance_mark_denap_receiver(task, FALSE);
			break;

		case TASK_APPTYPE_NONE:
			break;
	}

	if (portwatch_ports != NULL && apptype == TASK_APPTYPE_DAEMON_ADAPTIVE) {
		int portwatch_boosts = 0;

		for (int i = 0; i < portwatch_count; i++) {
			ipc_port_t port = NULL;

			if ((port = portwatch_ports[i]) != NULL) {
				int boost = 0;
				task_add_importance_watchport(task, port, &boost);
				portwatch_boosts += boost;
			}
		}

		if (portwatch_boosts > 0) {
			task_importance_hold_internal_assertion(task, portwatch_boosts);
		}
	}

	task_lock(task);

	if (apptype == TASK_APPTYPE_APP_TAL) {
		/* TAL starts off enabled by default */
		task->requested_policy.trp_tal_enabled = 1;
	}

	if (apptype != TASK_APPTYPE_NONE) {
		task->requested_policy.trp_apptype = apptype;
	}

#if CONFIG_EMBEDDED
	/* Remove this after launchd starts setting it properly */
	if (apptype == TASK_APPTYPE_APP_DEFAULT && role == TASK_UNSPECIFIED) {
		task->requested_policy.trp_role = TASK_FOREGROUND_APPLICATION;
	} else
#endif
	if (role != TASK_UNSPECIFIED) {
		task->requested_policy.trp_role = role;
	}

	if (qos_clamp != THREAD_QOS_UNSPECIFIED) {
		task->requested_policy.trp_qos_clamp = qos_clamp;
	}

	task_policy_update_locked(task, &pend_token);

	task_unlock(task);

	/* Ensure the donor bit is updated to be in sync with the new live donor status */
	pend_token.tpt_update_live_donor = 1;

	task_policy_update_complete_unlocked(task, &pend_token);

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
				  (IMPORTANCE_CODE(IMP_TASK_APPTYPE, apptype)) | DBG_FUNC_END,
				  task_pid(task), trequested_0(task), trequested_1(task),
				  task_is_importance_receiver(task), 0);
}