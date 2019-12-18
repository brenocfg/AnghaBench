#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct task_struct {int dummy; } ;
struct perf_event_context {int /*<<< orphan*/  lock; struct task_struct* task; } ;
struct perf_event {scalar_t__ state; int /*<<< orphan*/  cpu; struct perf_event_context* ctx; } ;

/* Variables and functions */
 scalar_t__ PERF_EVENT_STATE_ACTIVE ; 
 scalar_t__ PERF_EVENT_STATE_INACTIVE ; 
 scalar_t__ PERF_EVENT_STATE_OFF ; 
 int /*<<< orphan*/  __perf_event_disable ; 
 int /*<<< orphan*/  cpu_function_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct perf_event*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_function_call (struct task_struct*,int /*<<< orphan*/ ,struct perf_event*) ; 
 int /*<<< orphan*/  update_group_times (struct perf_event*) ; 

void perf_event_disable(struct perf_event *event)
{
	struct perf_event_context *ctx = event->ctx;
	struct task_struct *task = ctx->task;

	if (!task) {
		/*
		 * Disable the event on the cpu that it's on
		 */
		cpu_function_call(event->cpu, __perf_event_disable, event);
		return;
	}

retry:
	if (!task_function_call(task, __perf_event_disable, event))
		return;

	spin_lock_irq(&ctx->lock);
	/*
	 * If the event is still active, we need to retry the cross-call.
	 */
	if (event->state == PERF_EVENT_STATE_ACTIVE) {
		spin_unlock_irq(&ctx->lock);
		/*
		 * Reload the task pointer, it might have been changed by
		 * a concurrent perf_event_context_sched_out().
		 */
		task = ctx->task;
		goto retry;
	}

	/*
	 * Since we have the lock this context can't be scheduled
	 * in, so we can change the state safely.
	 */
	if (event->state == PERF_EVENT_STATE_INACTIVE) {
		update_group_times(event);
		event->state = PERF_EVENT_STATE_OFF;
	}
	spin_unlock_irq(&ctx->lock);
}