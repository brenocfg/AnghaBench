#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* task_t ;
struct TYPE_4__ {int tep_darwinbg; int tep_all_sockets_bg; int tep_latency_qos; int tep_through_qos; int tep_role; int tep_watchers_bg; int tep_sfi_managed; } ;
struct TYPE_5__ {TYPE_1__ effective_policy; } ;

/* Variables and functions */
#define  TASK_POLICY_ALL_SOCKETS_BG 134 
#define  TASK_POLICY_DARWIN_BG 133 
#define  TASK_POLICY_LATENCY_QOS 132 
#define  TASK_POLICY_ROLE 131 
#define  TASK_POLICY_SFI_MANAGED 130 
#define  TASK_POLICY_THROUGH_QOS 129 
#define  TASK_POLICY_WATCHERS_BG 128 
 int /*<<< orphan*/  panic (char*,int) ; 

int
proc_get_effective_task_policy(task_t   task,
                               int      flavor)
{
	int value = 0;

	switch (flavor) {
		case TASK_POLICY_DARWIN_BG:
			/*
			 * This backs the KPI call proc_pidbackgrounded to find
			 * out if a pid is backgrounded.
			 * It is used to communicate state to the VM system, as well as
			 * prioritizing requests to the graphics system.
			 * Returns 1 for background mode, 0 for normal mode
			 */
			value = task->effective_policy.tep_darwinbg;
			break;
		case TASK_POLICY_ALL_SOCKETS_BG:
			/*
			 * do_background_socket() calls this to determine what it should do to the proc's sockets
			 * Returns 1 for background mode, 0 for normal mode
			 *
			 * This consults both thread and task so un-DBGing a thread while the task is BG
			 * doesn't get you out of the network throttle.
			 */
			value = task->effective_policy.tep_all_sockets_bg;
			break;
		case TASK_POLICY_LATENCY_QOS:
			/*
			 * timer arming calls into here to find out the timer coalescing level
			 * Returns a QoS tier (0-6)
			 */
			value = task->effective_policy.tep_latency_qos;
			break;
		case TASK_POLICY_THROUGH_QOS:
			/*
			 * This value is passed into the urgency callout from the scheduler
			 * to the performance management subsystem.
			 * Returns a QoS tier (0-6)
			 */
			value = task->effective_policy.tep_through_qos;
			break;
		case TASK_POLICY_ROLE:
			/*
			 * This controls various things that ask whether a process is foreground,
			 * like SFI, VM, access to GPU, etc
			 */
			value = task->effective_policy.tep_role;
			break;
		case TASK_POLICY_WATCHERS_BG:
			/*
			 * This controls whether or not a thread watching this process should be BG.
			 */
			value = task->effective_policy.tep_watchers_bg;
			break;
		case TASK_POLICY_SFI_MANAGED:
			/*
			 * This controls whether or not a process is targeted for specific control by thermald.
			 */
			value = task->effective_policy.tep_sfi_managed;
			break;
		default:
			panic("unknown policy_flavor %d", flavor);
			break;
	}

	return value;
}