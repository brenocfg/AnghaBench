#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  TYPE_2__* thread_t ;
typedef  TYPE_3__* task_pend_token_t ;
struct thread_requested_policy {int thrp_qos; int thrp_qos_override; int thrp_qos_promote; int thrp_qos_ipc_override; int thrp_qos_workq_override; int thrp_qos_sync_ipc_override; scalar_t__ thrp_qos_relprio; int thrp_int_iotier; int thrp_ext_iotier; int thrp_latency_qos; int thrp_through_qos; scalar_t__ thrp_terminated; scalar_t__ thrp_int_iopassive; scalar_t__ thrp_ext_iopassive; scalar_t__ thrp_pidbind_bg; scalar_t__ thrp_ext_darwinbg; scalar_t__ thrp_int_darwinbg; } ;
struct thread_effective_policy {scalar_t__ thep_qos_ui_is_urgent; int thep_qos; int thep_qos_promote; scalar_t__ thep_qos_relprio; int thep_darwinbg; int thep_new_sockets_bg; int thep_all_sockets_bg; int thep_io_tier; int thep_io_passive; int thep_latency_qos; int thep_through_qos; int thep_terminated; } ;
struct task_effective_policy {scalar_t__ tep_qos_ui_is_urgent; int tep_qos_clamp; int tep_qos_ceiling; int tep_bg_iotier; int tep_io_tier; int tep_latency_qos; int tep_through_qos; scalar_t__ tep_terminated; scalar_t__ tep_io_passive; scalar_t__ tep_new_sockets_bg; scalar_t__ tep_darwinbg; } ;
typedef  scalar_t__ boolean_t ;
struct TYPE_12__ {int* qos_iotier; int* qos_latency_qos; int* qos_through_qos; } ;
struct TYPE_11__ {int tpt_update_sockets; int tpt_update_throttle; int tpt_update_thread_sfi; int tpt_force_recompute_pri; } ;
struct TYPE_10__ {struct thread_effective_policy effective_policy; TYPE_1__* task; struct thread_requested_policy requested_policy; } ;
struct TYPE_9__ {struct task_effective_policy effective_policy; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int LATENCY_QOS_TIER_UNSPECIFIED ; 
 int MAX (int,int) ; 
 void* MIN (int,int) ; 
 int THREAD_QOS_BACKGROUND ; 
 int THREAD_QOS_MAINTENANCE ; 
 int THREAD_QOS_UNSPECIFIED ; 
 void* THROTTLE_LEVEL_TIER0 ; 
 int THROUGHPUT_QOS_TIER_UNSPECIFIED ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_6__ thread_qos_policy_params ; 
 int /*<<< orphan*/  thread_recompute_priority (TYPE_2__*) ; 
 int /*<<< orphan*/  thread_update_qos_cpu_time_locked (TYPE_2__*) ; 

__attribute__((used)) static void
thread_policy_update_internal_spinlocked(thread_t thread, boolean_t recompute_priority,
                                         task_pend_token_t pend_token)
{
	/*
	 * Step 1:
	 *  Gather requested policy and effective task state
	 */

	struct thread_requested_policy requested = thread->requested_policy;
	struct task_effective_policy task_effective = thread->task->effective_policy;

	/*
	 * Step 2:
	 *  Calculate new effective policies from requested policy, task and thread state
	 *  Rules:
	 *      Don't change requested, it won't take effect
	 */

	struct thread_effective_policy next = {};

	next.thep_qos_ui_is_urgent = task_effective.tep_qos_ui_is_urgent;

	uint32_t next_qos = requested.thrp_qos;

	if (requested.thrp_qos != THREAD_QOS_UNSPECIFIED) {
		next_qos = MAX(requested.thrp_qos_override, next_qos);
		next_qos = MAX(requested.thrp_qos_promote, next_qos);
		next_qos = MAX(requested.thrp_qos_ipc_override, next_qos);
		next_qos = MAX(requested.thrp_qos_workq_override, next_qos);
	}

	next.thep_qos = next_qos;

	/* A task clamp will result in an effective QoS even when requested is UNSPECIFIED */
	if (task_effective.tep_qos_clamp != THREAD_QOS_UNSPECIFIED) {
		if (next.thep_qos != THREAD_QOS_UNSPECIFIED)
			next.thep_qos = MIN(task_effective.tep_qos_clamp, next.thep_qos);
		else
			next.thep_qos = task_effective.tep_qos_clamp;
	}

	/*
	 * Extract outbound-promotion QoS before applying task ceiling or BG clamp
	 * This allows QoS promotions to work properly even after the process is unclamped.
	 */
	next.thep_qos_promote = next.thep_qos;

	/* The ceiling only applies to threads that are in the QoS world */
	if (task_effective.tep_qos_ceiling != THREAD_QOS_UNSPECIFIED &&
	    next.thep_qos                  != THREAD_QOS_UNSPECIFIED) {
		next.thep_qos = MIN(task_effective.tep_qos_ceiling, next.thep_qos);
	}

	/* Apply the sync ipc qos override */
	assert(requested.thrp_qos_sync_ipc_override == THREAD_QOS_UNSPECIFIED);

	/*
	 * The QoS relative priority is only applicable when the original programmer's
	 * intended (requested) QoS is in effect. When the QoS is clamped (e.g.
	 * USER_INITIATED-13REL clamped to UTILITY), the relative priority is not honored,
	 * since otherwise it would be lower than unclamped threads. Similarly, in the
	 * presence of boosting, the programmer doesn't know what other actors
	 * are boosting the thread.
	 */
	if ((requested.thrp_qos != THREAD_QOS_UNSPECIFIED) &&
	    (requested.thrp_qos == next.thep_qos) &&
	    (requested.thrp_qos_override == THREAD_QOS_UNSPECIFIED)) {
		next.thep_qos_relprio = requested.thrp_qos_relprio;
	} else {
		next.thep_qos_relprio = 0;
	}

	/* Calculate DARWIN_BG */
	boolean_t wants_darwinbg        = FALSE;
	boolean_t wants_all_sockets_bg  = FALSE; /* Do I want my existing sockets to be bg */

	/*
	 * If DARWIN_BG has been requested at either level, it's engaged.
	 * darwinbg threads always create bg sockets,
	 * but only some types of darwinbg change the sockets
	 * after they're created
	 */
	if (requested.thrp_int_darwinbg || requested.thrp_ext_darwinbg)
		wants_all_sockets_bg = wants_darwinbg = TRUE;

	if (requested.thrp_pidbind_bg)
		wants_all_sockets_bg = wants_darwinbg = TRUE;

	if (task_effective.tep_darwinbg)
		wants_darwinbg = TRUE;

	if (next.thep_qos == THREAD_QOS_BACKGROUND ||
	    next.thep_qos == THREAD_QOS_MAINTENANCE)
		wants_darwinbg = TRUE;

	/* Calculate side effects of DARWIN_BG */

	if (wants_darwinbg)
		next.thep_darwinbg = 1;

	if (next.thep_darwinbg || task_effective.tep_new_sockets_bg)
		next.thep_new_sockets_bg = 1;

	/* Don't use task_effective.tep_all_sockets_bg here */
	if (wants_all_sockets_bg)
		next.thep_all_sockets_bg = 1;

	/* darwinbg implies background QOS (or lower) */
	if (next.thep_darwinbg &&
	    (next.thep_qos > THREAD_QOS_BACKGROUND || next.thep_qos == THREAD_QOS_UNSPECIFIED)) {
		next.thep_qos = THREAD_QOS_BACKGROUND;
		next.thep_qos_relprio = 0;
	}

	/* Calculate IO policy */

	int iopol = THROTTLE_LEVEL_TIER0;

	/* Factor in the task's IO policy */
	if (next.thep_darwinbg)
		iopol = MAX(iopol, task_effective.tep_bg_iotier);

	iopol = MAX(iopol, task_effective.tep_io_tier);

	/* Look up the associated IO tier value for the QoS class */
	iopol = MAX(iopol, thread_qos_policy_params.qos_iotier[next.thep_qos]);

	iopol = MAX(iopol, requested.thrp_int_iotier);
	iopol = MAX(iopol, requested.thrp_ext_iotier);

	next.thep_io_tier = iopol;

	/*
	 * If a QoS override is causing IO to go into a lower tier, we also set
	 * the passive bit so that a thread doesn't end up stuck in its own throttle
	 * window when the override goes away.
	 */
	boolean_t qos_io_override_active = FALSE;
	if (thread_qos_policy_params.qos_iotier[next.thep_qos] <
	    thread_qos_policy_params.qos_iotier[requested.thrp_qos])
		qos_io_override_active = TRUE;

	/* Calculate Passive IO policy */
	if (requested.thrp_ext_iopassive    ||
	    requested.thrp_int_iopassive    ||
	    qos_io_override_active          ||
	    task_effective.tep_io_passive   )
		next.thep_io_passive = 1;

	/* Calculate timer QOS */
	uint32_t latency_qos = requested.thrp_latency_qos;

	latency_qos = MAX(latency_qos, task_effective.tep_latency_qos);
	latency_qos = MAX(latency_qos, thread_qos_policy_params.qos_latency_qos[next.thep_qos]);

	next.thep_latency_qos = latency_qos;

	/* Calculate throughput QOS */
	uint32_t through_qos = requested.thrp_through_qos;

	through_qos = MAX(through_qos, task_effective.tep_through_qos);
	through_qos = MAX(through_qos, thread_qos_policy_params.qos_through_qos[next.thep_qos]);

	next.thep_through_qos = through_qos;

	if (task_effective.tep_terminated || requested.thrp_terminated) {
		/* Shoot down the throttles that slow down exit or response to SIGTERM */
		next.thep_terminated    = 1;
		next.thep_darwinbg      = 0;
		next.thep_io_tier       = THROTTLE_LEVEL_TIER0;
		next.thep_qos           = THREAD_QOS_UNSPECIFIED;
		next.thep_latency_qos   = LATENCY_QOS_TIER_UNSPECIFIED;
		next.thep_through_qos   = THROUGHPUT_QOS_TIER_UNSPECIFIED;
	}

	/*
	 * Step 3:
	 *  Swap out old policy for new policy
	 */

	struct thread_effective_policy prev = thread->effective_policy;

	thread_update_qos_cpu_time_locked(thread);

	/* This is the point where the new values become visible to other threads */
	thread->effective_policy = next;

	/*
	 * Step 4:
	 *  Pend updates that can't be done while holding the thread lock
	 */

	if (prev.thep_all_sockets_bg != next.thep_all_sockets_bg)
		pend_token->tpt_update_sockets = 1;

	/* TODO: Doesn't this only need to be done if the throttle went up? */
	if (prev.thep_io_tier != next.thep_io_tier)
		pend_token->tpt_update_throttle = 1;

	/*
	 * Check for the attributes that sfi_thread_classify() consults,
	 *  and trigger SFI re-evaluation.
	 */
	if (prev.thep_qos      != next.thep_qos         ||
	    prev.thep_darwinbg != next.thep_darwinbg    )
		pend_token->tpt_update_thread_sfi = 1;

	/*
	 * Step 5:
	 *  Update other subsystems as necessary if something has changed
	 */

	/* Check for the attributes that thread_recompute_priority() consults */
	if (prev.thep_qos               != next.thep_qos                ||
	    prev.thep_qos_relprio       != next.thep_qos_relprio        ||
	    prev.thep_qos_ui_is_urgent  != next.thep_qos_ui_is_urgent   ||
	    prev.thep_terminated        != next.thep_terminated         ||
	    pend_token->tpt_force_recompute_pri == 1                    ||
	    recompute_priority) {
		thread_recompute_priority(thread);
	}
}