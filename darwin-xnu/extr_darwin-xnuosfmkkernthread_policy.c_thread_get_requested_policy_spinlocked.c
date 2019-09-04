#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
struct thread_requested_policy {int thrp_ext_darwinbg; int thrp_int_darwinbg; int thrp_ext_iotier; int thrp_ext_iopassive; int thrp_int_iotier; int thrp_int_iopassive; int thrp_qos; int thrp_qos_override; int thrp_latency_qos; int thrp_through_qos; int thrp_qos_workq_override; int thrp_qos_relprio; int thrp_qos_promote; int thrp_qos_ipc_override; int thrp_terminated; } ;
struct TYPE_3__ {struct thread_requested_policy requested_policy; } ;

/* Variables and functions */
 int TASK_POLICY_ATTRIBUTE ; 
#define  TASK_POLICY_DARWIN_BG 140 
 int TASK_POLICY_EXTERNAL ; 
#define  TASK_POLICY_IO 139 
#define  TASK_POLICY_IOPOL 138 
#define  TASK_POLICY_LATENCY_QOS 137 
#define  TASK_POLICY_PASSIVE_IO 136 
#define  TASK_POLICY_QOS 135 
#define  TASK_POLICY_QOS_AND_RELPRIO 134 
#define  TASK_POLICY_QOS_IPC_OVERRIDE 133 
#define  TASK_POLICY_QOS_OVERRIDE 132 
#define  TASK_POLICY_QOS_PROMOTE 131 
#define  TASK_POLICY_QOS_WORKQ_OVERRIDE 130 
#define  TASK_POLICY_TERMINATED 129 
#define  TASK_POLICY_THROUGH_QOS 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int proc_tier_to_iopol (int,int) ; 

__attribute__((used)) static int
thread_get_requested_policy_spinlocked(thread_t thread,
                                       int      category,
                                       int      flavor,
                                       int*     value2)
{
	int value = 0;

	struct thread_requested_policy requested = thread->requested_policy;

	switch (flavor) {
		case TASK_POLICY_DARWIN_BG:
			if (category == TASK_POLICY_EXTERNAL)
				value = requested.thrp_ext_darwinbg;
			else
				value = requested.thrp_int_darwinbg;
			break;
		case TASK_POLICY_IOPOL:
			if (category == TASK_POLICY_EXTERNAL)
				value = proc_tier_to_iopol(requested.thrp_ext_iotier,
				                           requested.thrp_ext_iopassive);
			else
				value = proc_tier_to_iopol(requested.thrp_int_iotier,
				                           requested.thrp_int_iopassive);
			break;
		case TASK_POLICY_IO:
			if (category == TASK_POLICY_EXTERNAL)
				value = requested.thrp_ext_iotier;
			else
				value = requested.thrp_int_iotier;
			break;
		case TASK_POLICY_PASSIVE_IO:
			if (category == TASK_POLICY_EXTERNAL)
				value = requested.thrp_ext_iopassive;
			else
				value = requested.thrp_int_iopassive;
			break;
		case TASK_POLICY_QOS:
			assert(category == TASK_POLICY_ATTRIBUTE);
			value = requested.thrp_qos;
			break;
		case TASK_POLICY_QOS_OVERRIDE:
			assert(category == TASK_POLICY_ATTRIBUTE);
			value = requested.thrp_qos_override;
			break;
		case TASK_POLICY_LATENCY_QOS:
			assert(category == TASK_POLICY_ATTRIBUTE);
			value = requested.thrp_latency_qos;
			break;
		case TASK_POLICY_THROUGH_QOS:
			assert(category == TASK_POLICY_ATTRIBUTE);
			value = requested.thrp_through_qos;
			break;
		case TASK_POLICY_QOS_WORKQ_OVERRIDE:
			assert(category == TASK_POLICY_ATTRIBUTE);
			value = requested.thrp_qos_workq_override;
			break;
		case TASK_POLICY_QOS_AND_RELPRIO:
			assert(category == TASK_POLICY_ATTRIBUTE);
			assert(value2 != NULL);
			value = requested.thrp_qos;
			*value2 = requested.thrp_qos_relprio;
			break;
		case TASK_POLICY_QOS_PROMOTE:
			assert(category == TASK_POLICY_ATTRIBUTE);
			value = requested.thrp_qos_promote;
			break;
		case TASK_POLICY_QOS_IPC_OVERRIDE:
			assert(category == TASK_POLICY_ATTRIBUTE);
			value = requested.thrp_qos_ipc_override;
			break;
		case TASK_POLICY_TERMINATED:
			assert(category == TASK_POLICY_ATTRIBUTE);
			value = requested.thrp_terminated;
			break;

		default:
			panic("unknown policy_flavor %d", flavor);
			break;
	}

	return value;
}