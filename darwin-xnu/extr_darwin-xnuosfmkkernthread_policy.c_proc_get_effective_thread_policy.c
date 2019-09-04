#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* thread_t ;
struct TYPE_8__ {int thep_io_tier; int thep_latency_qos; int thep_through_qos; int thep_qos; int /*<<< orphan*/  thep_new_sockets_bg; int /*<<< orphan*/  thep_all_sockets_bg; int /*<<< orphan*/  thep_io_passive; int /*<<< orphan*/  thep_darwinbg; } ;
struct TYPE_9__ {int iotier_override; TYPE_3__ effective_policy; TYPE_2__* task; } ;
struct TYPE_6__ {int /*<<< orphan*/  tep_all_sockets_bg; } ;
struct TYPE_7__ {TYPE_1__ effective_policy; } ;

/* Variables and functions */
 int MIN (int,int) ; 
#define  TASK_POLICY_ALL_SOCKETS_BG 135 
#define  TASK_POLICY_DARWIN_BG 134 
#define  TASK_POLICY_IO 133 
#define  TASK_POLICY_LATENCY_QOS 132 
#define  TASK_POLICY_NEW_SOCKETS_BG 131 
#define  TASK_POLICY_PASSIVE_IO 130 
#define  TASK_POLICY_QOS 129 
#define  TASK_POLICY_THROUGH_QOS 128 
 int THROTTLE_LEVEL_NONE ; 
 int /*<<< orphan*/  panic (char*,int) ; 

int
proc_get_effective_thread_policy(thread_t thread,
                                 int      flavor)
{
	int value = 0;

	switch (flavor) {
		case TASK_POLICY_DARWIN_BG:
			/*
			 * This call is used within the timer layer, as well as
			 * prioritizing requests to the graphics system.
			 * It also informs SFI and originator-bg-state.
			 * Returns 1 for background mode, 0 for normal mode
			 */

			value = thread->effective_policy.thep_darwinbg ? 1 : 0;
			break;
		case TASK_POLICY_IO:
			/*
			 * The I/O system calls here to find out what throttling tier to apply to an operation.
			 * Returns THROTTLE_LEVEL_* values
			 */
			value = thread->effective_policy.thep_io_tier;
			if (thread->iotier_override != THROTTLE_LEVEL_NONE)
				value = MIN(value, thread->iotier_override);
			break;
		case TASK_POLICY_PASSIVE_IO:
			/*
			 * The I/O system calls here to find out whether an operation should be passive.
			 * (i.e. not cause operations with lower throttle tiers to be throttled)
			 * Returns 1 for passive mode, 0 for normal mode
			 *
			 * If an override is causing IO to go into a lower tier, we also set
			 * the passive bit so that a thread doesn't end up stuck in its own throttle
			 * window when the override goes away.
			 */
			value = thread->effective_policy.thep_io_passive ? 1 : 0;
			if (thread->iotier_override != THROTTLE_LEVEL_NONE &&
			    thread->iotier_override < thread->effective_policy.thep_io_tier)
				value = 1;
			break;
		case TASK_POLICY_ALL_SOCKETS_BG:
			/*
			 * do_background_socket() calls this to determine whether
			 * it should change the thread's sockets
			 * Returns 1 for background mode, 0 for normal mode
			 * This consults both thread and task so un-DBGing a thread while the task is BG
			 * doesn't get you out of the network throttle.
			 */
			value = (thread->effective_policy.thep_all_sockets_bg ||
			         thread->task->effective_policy.tep_all_sockets_bg) ? 1 : 0;
			break;
		case TASK_POLICY_NEW_SOCKETS_BG:
			/*
			 * socreate() calls this to determine if it should mark a new socket as background
			 * Returns 1 for background mode, 0 for normal mode
			 */
			value = thread->effective_policy.thep_new_sockets_bg ? 1 : 0;
			break;
		case TASK_POLICY_LATENCY_QOS:
			/*
			 * timer arming calls into here to find out the timer coalescing level
			 * Returns a latency QoS tier (0-6)
			 */
			value = thread->effective_policy.thep_latency_qos;
			break;
		case TASK_POLICY_THROUGH_QOS:
			/*
			 * This value is passed into the urgency callout from the scheduler
			 * to the performance management subsystem.
			 *
			 * Returns a throughput QoS tier (0-6)
			 */
			value = thread->effective_policy.thep_through_qos;
			break;
		case TASK_POLICY_QOS:
			/*
			 * This is communicated to the performance management layer and SFI.
			 *
			 * Returns a QoS policy tier
			 */
			value = thread->effective_policy.thep_qos;
			break;
		default:
			panic("unknown thread policy flavor %d", flavor);
			break;
	}

	return value;
}