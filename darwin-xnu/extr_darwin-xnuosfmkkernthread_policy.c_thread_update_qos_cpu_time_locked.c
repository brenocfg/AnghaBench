#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  TYPE_5__* thread_t ;
typedef  TYPE_6__* task_t ;
struct TYPE_10__ {scalar_t__ cpu_time_qos_user_interactive; scalar_t__ cpu_time_qos_user_initiated; scalar_t__ cpu_time_qos_legacy; scalar_t__ cpu_time_qos_utility; scalar_t__ cpu_time_qos_background; scalar_t__ cpu_time_qos_maintenance; scalar_t__ cpu_time_qos_default; } ;
struct TYPE_8__ {scalar_t__ cpu_time_qos_user_interactive; scalar_t__ cpu_time_qos_user_initiated; scalar_t__ cpu_time_qos_legacy; scalar_t__ cpu_time_qos_utility; scalar_t__ cpu_time_qos_background; scalar_t__ cpu_time_qos_maintenance; scalar_t__ cpu_time_qos_default; } ;
struct TYPE_13__ {TYPE_3__ cpu_time_rqos_stats; TYPE_1__ cpu_time_eqos_stats; } ;
struct TYPE_11__ {int thrp_qos; } ;
struct TYPE_9__ {int thep_qos; } ;
struct TYPE_12__ {TYPE_4__ requested_policy; TYPE_2__ effective_policy; scalar_t__ vtimer_qos_save; int /*<<< orphan*/  system_timer; int /*<<< orphan*/  user_timer; TYPE_6__* task; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAddAtomic64 (scalar_t__,scalar_t__*) ; 
#define  THREAD_QOS_BACKGROUND 134 
#define  THREAD_QOS_LEGACY 133 
#define  THREAD_QOS_MAINTENANCE 132 
#define  THREAD_QOS_UNSPECIFIED 131 
#define  THREAD_QOS_USER_INITIATED 130 
#define  THREAD_QOS_USER_INTERACTIVE 129 
#define  THREAD_QOS_UTILITY 128 
 int /*<<< orphan*/  panic (char*,int) ; 
 scalar_t__ timer_grab (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
thread_update_qos_cpu_time_locked(thread_t thread)
{
	task_t task = thread->task;
	uint64_t timer_sum, timer_delta;

	/*
	 * This is only as accurate as the distance between
	 * last context switch (embedded) or last user/kernel boundary transition (desktop)
	 * because user_timer and system_timer are only updated then.
	 *
	 * TODO: Consider running a timer_update operation here to update it first.
	 *       Maybe doable with interrupts disabled from current thread.
	 *       If the thread is on a different core, may not be easy to get right.
	 *
	 * TODO: There should be a function for this in timer.c
	 */

	timer_sum = timer_grab(&thread->user_timer);
	timer_sum += timer_grab(&thread->system_timer);
	timer_delta = timer_sum - thread->vtimer_qos_save;

	thread->vtimer_qos_save = timer_sum;

	uint64_t* task_counter = NULL;

	/* Update the task-level effective and requested qos stats atomically, because we don't have the task lock. */
	switch (thread->effective_policy.thep_qos) {
		case THREAD_QOS_UNSPECIFIED:        task_counter = &task->cpu_time_eqos_stats.cpu_time_qos_default;          break;
		case THREAD_QOS_MAINTENANCE:        task_counter = &task->cpu_time_eqos_stats.cpu_time_qos_maintenance;      break;
		case THREAD_QOS_BACKGROUND:         task_counter = &task->cpu_time_eqos_stats.cpu_time_qos_background;       break;
		case THREAD_QOS_UTILITY:            task_counter = &task->cpu_time_eqos_stats.cpu_time_qos_utility;          break;
		case THREAD_QOS_LEGACY:             task_counter = &task->cpu_time_eqos_stats.cpu_time_qos_legacy;           break;
		case THREAD_QOS_USER_INITIATED:     task_counter = &task->cpu_time_eqos_stats.cpu_time_qos_user_initiated;   break;
		case THREAD_QOS_USER_INTERACTIVE:   task_counter = &task->cpu_time_eqos_stats.cpu_time_qos_user_interactive; break;
		default:
			panic("unknown effective QoS: %d", thread->effective_policy.thep_qos);
	}

	OSAddAtomic64(timer_delta, task_counter);

	/* Update the task-level qos stats atomically, because we don't have the task lock. */
	switch (thread->requested_policy.thrp_qos) {
		case THREAD_QOS_UNSPECIFIED:        task_counter = &task->cpu_time_rqos_stats.cpu_time_qos_default;          break;
		case THREAD_QOS_MAINTENANCE:        task_counter = &task->cpu_time_rqos_stats.cpu_time_qos_maintenance;      break;
		case THREAD_QOS_BACKGROUND:         task_counter = &task->cpu_time_rqos_stats.cpu_time_qos_background;       break;
		case THREAD_QOS_UTILITY:            task_counter = &task->cpu_time_rqos_stats.cpu_time_qos_utility;          break;
		case THREAD_QOS_LEGACY:             task_counter = &task->cpu_time_rqos_stats.cpu_time_qos_legacy;           break;
		case THREAD_QOS_USER_INITIATED:     task_counter = &task->cpu_time_rqos_stats.cpu_time_qos_user_initiated;   break;
		case THREAD_QOS_USER_INTERACTIVE:   task_counter = &task->cpu_time_rqos_stats.cpu_time_qos_user_interactive; break;
		default:
			panic("unknown requested QoS: %d", thread->requested_policy.thrp_qos);
	}

	OSAddAtomic64(timer_delta, task_counter);
}