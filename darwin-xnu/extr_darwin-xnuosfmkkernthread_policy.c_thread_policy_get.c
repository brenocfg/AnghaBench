#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_21__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  TYPE_3__* thread_time_constraint_policy_t ;
typedef  void* thread_throughput_qos_t ;
typedef  TYPE_4__* thread_throughput_qos_policy_t ;
typedef  TYPE_5__* thread_t ;
typedef  TYPE_6__* thread_qos_policy_t ;
typedef  TYPE_7__* thread_precedence_policy_t ;
typedef  scalar_t__ thread_policy_t ;
typedef  TYPE_8__* thread_policy_state_t ;
typedef  int thread_policy_flavor_t ;
typedef  void* thread_latency_qos_t ;
typedef  TYPE_9__* thread_latency_qos_policy_t ;
typedef  TYPE_10__* thread_extended_policy_t ;
typedef  TYPE_11__* thread_affinity_policy_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int boolean_t ;
struct TYPE_34__ {int /*<<< orphan*/  thread_latency_qos_tier; } ;
struct TYPE_33__ {int /*<<< orphan*/  pending; int /*<<< orphan*/  effective; int /*<<< orphan*/  requested; int /*<<< orphan*/  thps_ipc_overrides; int /*<<< orphan*/  thps_user_promotion_basepri; int /*<<< orphan*/  thps_user_promotions; void* thps_effective_policy; void* thps_requested_policy; int /*<<< orphan*/  flags; } ;
struct TYPE_32__ {int /*<<< orphan*/  importance; } ;
struct TYPE_31__ {int tier_importance; void* qos_tier; } ;
struct TYPE_25__ {void* preemptible; int /*<<< orphan*/  constraint; int /*<<< orphan*/  computation; int /*<<< orphan*/  period; } ;
struct TYPE_30__ {int sched_flags; int /*<<< orphan*/  ipc_overrides; int /*<<< orphan*/  user_promotion_basepri; int /*<<< orphan*/  effective_policy; int /*<<< orphan*/  requested_policy; int /*<<< orphan*/  static_param; int /*<<< orphan*/  importance; TYPE_1__ realtime; int /*<<< orphan*/  saved_mode; int /*<<< orphan*/  sched_mode; int /*<<< orphan*/  active; } ;
struct TYPE_29__ {int /*<<< orphan*/  thread_throughput_qos_tier; } ;
struct TYPE_28__ {void* preemptible; int /*<<< orphan*/  constraint; int /*<<< orphan*/  computation; int /*<<< orphan*/  period; } ;
struct TYPE_27__ {int /*<<< orphan*/ * val; } ;
struct TYPE_26__ {TYPE_2__ sec_token; } ;
struct TYPE_24__ {int /*<<< orphan*/  affinity_tag; } ;
struct TYPE_23__ {int timeshare; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_NOT_SUPPORTED ; 
 int /*<<< orphan*/  KERN_PROTECTION_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  KERN_TERMINATED ; 
 int /*<<< orphan*/  TASK_POLICY_ATTRIBUTE ; 
 int /*<<< orphan*/  TASK_POLICY_LATENCY_QOS ; 
 int /*<<< orphan*/  TASK_POLICY_QOS_AND_RELPRIO ; 
 int /*<<< orphan*/  TASK_POLICY_THROUGH_QOS ; 
#define  THREAD_AFFINITY_POLICY 135 
 int /*<<< orphan*/  THREAD_AFFINITY_POLICY_COUNT ; 
 int /*<<< orphan*/  THREAD_AFFINITY_TAG_NULL ; 
#define  THREAD_EXTENDED_POLICY 134 
 int /*<<< orphan*/  THREAD_EXTENDED_POLICY_COUNT ; 
#define  THREAD_LATENCY_QOS_POLICY 133 
 int /*<<< orphan*/  THREAD_LATENCY_QOS_POLICY_COUNT ; 
 TYPE_5__* THREAD_NULL ; 
#define  THREAD_POLICY_STATE 132 
 int /*<<< orphan*/  THREAD_POLICY_STATE_COUNT ; 
 int /*<<< orphan*/  THREAD_POLICY_STATE_FLAG_STATIC_PARAM ; 
#define  THREAD_PRECEDENCE_POLICY 131 
 int /*<<< orphan*/  THREAD_PRECEDENCE_POLICY_COUNT ; 
#define  THREAD_QOS_POLICY 130 
 int /*<<< orphan*/  THREAD_QOS_POLICY_COUNT ; 
 void* THREAD_QOS_UNSPECIFIED ; 
#define  THREAD_THROUGHPUT_QOS_POLICY 129 
 int /*<<< orphan*/  THREAD_THROUGHPUT_QOS_POLICY_COUNT ; 
#define  THREAD_TIME_CONSTRAINT_POLICY 128 
 int /*<<< orphan*/  THREAD_TIME_CONSTRAINT_POLICY_COUNT ; 
 int /*<<< orphan*/  TH_MODE_REALTIME ; 
 int /*<<< orphan*/  TH_MODE_TIMESHARE ; 
 int TH_SFLAG_DEMOTED_MASK ; 
 void* TRUE ; 
 TYPE_21__* current_task () ; 
 int /*<<< orphan*/  default_timeshare_computation ; 
 int /*<<< orphan*/  default_timeshare_constraint ; 
 int /*<<< orphan*/  proc_get_thread_policy_bitfield (TYPE_5__*,TYPE_8__*) ; 
 void* proc_get_thread_policy_locked (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  qos_latency_policy_package (void*) ; 
 int /*<<< orphan*/  qos_throughput_policy_package (void*) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_affinity_get (TYPE_5__*) ; 
 int /*<<< orphan*/  thread_affinity_is_supported () ; 
 int /*<<< orphan*/  thread_lock (TYPE_5__*) ; 
 int /*<<< orphan*/  thread_mtx_lock (TYPE_5__*) ; 
 int /*<<< orphan*/  thread_mtx_unlock (TYPE_5__*) ; 
 int /*<<< orphan*/  thread_unlock (TYPE_5__*) ; 

kern_return_t
thread_policy_get(
	thread_t				thread,
	thread_policy_flavor_t	flavor,
	thread_policy_t			policy_info,
	mach_msg_type_number_t	*count,
	boolean_t				*get_default)
{
	kern_return_t			result = KERN_SUCCESS;

	if (thread == THREAD_NULL)
		return (KERN_INVALID_ARGUMENT);

	thread_mtx_lock(thread);
	if (!thread->active) {
		thread_mtx_unlock(thread);

		return (KERN_TERMINATED);
	}

	switch (flavor) {

	case THREAD_EXTENDED_POLICY:
	{
		boolean_t		timeshare = TRUE;

		if (!(*get_default)) {
			spl_t s = splsched();
			thread_lock(thread);

			if (	 (thread->sched_mode != TH_MODE_REALTIME)	&&
					 (thread->saved_mode != TH_MODE_REALTIME)			) {
				if (!(thread->sched_flags & TH_SFLAG_DEMOTED_MASK))
					timeshare = (thread->sched_mode == TH_MODE_TIMESHARE) != 0;
				else
					timeshare = (thread->saved_mode == TH_MODE_TIMESHARE) != 0;
			}
			else
				*get_default = TRUE;

			thread_unlock(thread);
			splx(s);
		}

		if (*count >= THREAD_EXTENDED_POLICY_COUNT) {
			thread_extended_policy_t	info;

			info = (thread_extended_policy_t)policy_info;
			info->timeshare = timeshare;
		}

		break;
	}

	case THREAD_TIME_CONSTRAINT_POLICY:
	{
		thread_time_constraint_policy_t		info;

		if (*count < THREAD_TIME_CONSTRAINT_POLICY_COUNT) {
			result = KERN_INVALID_ARGUMENT;
			break;
		}

		info = (thread_time_constraint_policy_t)policy_info;

		if (!(*get_default)) {
			spl_t s = splsched();
			thread_lock(thread);

			if (	(thread->sched_mode == TH_MODE_REALTIME)	||
					(thread->saved_mode == TH_MODE_REALTIME)		) {
				info->period = thread->realtime.period;
				info->computation = thread->realtime.computation;
				info->constraint = thread->realtime.constraint;
				info->preemptible = thread->realtime.preemptible;
			}
			else
				*get_default = TRUE;

			thread_unlock(thread);
			splx(s);
		}

		if (*get_default) {
			info->period = 0;
			info->computation = default_timeshare_computation;
			info->constraint = default_timeshare_constraint;
			info->preemptible = TRUE;
		}

		break;
	}

	case THREAD_PRECEDENCE_POLICY:
	{
		thread_precedence_policy_t		info;

		if (*count < THREAD_PRECEDENCE_POLICY_COUNT) {
			result = KERN_INVALID_ARGUMENT;
			break;
		}

		info = (thread_precedence_policy_t)policy_info;

		if (!(*get_default)) {
			spl_t s = splsched();
			thread_lock(thread);

			info->importance = thread->importance;

			thread_unlock(thread);
			splx(s);
		}
		else
			info->importance = 0;

		break;
	}

	case THREAD_AFFINITY_POLICY:
	{
		thread_affinity_policy_t		info;

		if (!thread_affinity_is_supported()) {
			result = KERN_NOT_SUPPORTED;
			break;
		}
		if (*count < THREAD_AFFINITY_POLICY_COUNT) {
			result = KERN_INVALID_ARGUMENT;
			break;
		}

		info = (thread_affinity_policy_t)policy_info;

		if (!(*get_default))
			info->affinity_tag = thread_affinity_get(thread);
		else
			info->affinity_tag = THREAD_AFFINITY_TAG_NULL;

		break;
	}

	case THREAD_POLICY_STATE:
	{
		thread_policy_state_t		info;

		if (*count < THREAD_POLICY_STATE_COUNT) {
			result = KERN_INVALID_ARGUMENT;
			break;
		}

		/* Only root can get this info */
		if (current_task()->sec_token.val[0] != 0) {
			result = KERN_PROTECTION_FAILURE;
			break;
		}

		info = (thread_policy_state_t)(void*)policy_info;

		if (!(*get_default)) {
			info->flags = 0;

			spl_t s = splsched();
			thread_lock(thread);

			info->flags |= (thread->static_param ? THREAD_POLICY_STATE_FLAG_STATIC_PARAM : 0);

			info->thps_requested_policy = *(uint64_t*)(void*)(&thread->requested_policy);
			info->thps_effective_policy = *(uint64_t*)(void*)(&thread->effective_policy);

			info->thps_user_promotions          = 0;
			info->thps_user_promotion_basepri   = thread->user_promotion_basepri;
			info->thps_ipc_overrides            = thread->ipc_overrides;

			proc_get_thread_policy_bitfield(thread, info);

			thread_unlock(thread);
			splx(s);
		} else {
			info->requested = 0;
			info->effective = 0;
			info->pending = 0;
		}

		break;
	}
	
	case THREAD_LATENCY_QOS_POLICY:
	{
		thread_latency_qos_policy_t info = (thread_latency_qos_policy_t) policy_info;
		thread_latency_qos_t plqos;

		if (*count < THREAD_LATENCY_QOS_POLICY_COUNT) {
			result = KERN_INVALID_ARGUMENT;
			break;
		}

		if (*get_default) {
			plqos = 0;
		} else {
			plqos = proc_get_thread_policy_locked(thread, TASK_POLICY_ATTRIBUTE, TASK_POLICY_LATENCY_QOS, NULL);
		}

		info->thread_latency_qos_tier = qos_latency_policy_package(plqos);
	}
	break;

	case THREAD_THROUGHPUT_QOS_POLICY:
	{
		thread_throughput_qos_policy_t info = (thread_throughput_qos_policy_t) policy_info;
		thread_throughput_qos_t ptqos;

		if (*count < THREAD_THROUGHPUT_QOS_POLICY_COUNT) {
			result = KERN_INVALID_ARGUMENT;
			break;
		}

		if (*get_default) {
			ptqos = 0;
		} else {
			ptqos = proc_get_thread_policy_locked(thread, TASK_POLICY_ATTRIBUTE, TASK_POLICY_THROUGH_QOS, NULL);
		}

		info->thread_throughput_qos_tier = qos_throughput_policy_package(ptqos);
	}
	break;

	case THREAD_QOS_POLICY:
	{
		thread_qos_policy_t info = (thread_qos_policy_t)policy_info;

		if (*count < THREAD_QOS_POLICY_COUNT) {
			result = KERN_INVALID_ARGUMENT;
			break;
		}

		if (!(*get_default)) {
			int relprio_value = 0;
			info->qos_tier = proc_get_thread_policy_locked(thread, TASK_POLICY_ATTRIBUTE,
			                                               TASK_POLICY_QOS_AND_RELPRIO, &relprio_value);

			info->tier_importance = -relprio_value;
		} else {
			info->qos_tier = THREAD_QOS_UNSPECIFIED;
			info->tier_importance = 0;
		}

		break;
	}

	default:
		result = KERN_INVALID_ARGUMENT;
		break;
	}

	thread_mtx_unlock(thread);

	return (result);
}