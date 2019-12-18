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
struct perf_event_context {int /*<<< orphan*/  lock; struct task_struct* task; scalar_t__ is_active; } ;
struct perf_event {scalar_t__ state; int /*<<< orphan*/  cpu; struct perf_event_context* ctx; } ;

/* Variables and functions */
 scalar_t__ PERF_EVENT_STATE_ERROR ; 
 scalar_t__ PERF_EVENT_STATE_INACTIVE ; 
 scalar_t__ PERF_EVENT_STATE_OFF ; 
 int /*<<< orphan*/  __perf_event_enable ; 
 int /*<<< orphan*/  __perf_event_mark_enabled (struct perf_event*) ; 
 int /*<<< orphan*/  cpu_function_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct perf_event*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_function_call (struct task_struct*,int /*<<< orphan*/ ,struct perf_event*) ; 

void perf_event_enable(struct perf_event *event)
{
	struct perf_event_context *ctx = event->ctx;
	struct task_struct *task = ctx->task;

	if (!task) {
		/*
		 * Enable the event on the cpu that it's on
		 */
		cpu_function_call(event->cpu, __perf_event_enable, event);
		return;
	}

	spin_lock_irq(&ctx->lock);
	if (event->state >= PERF_EVENT_STATE_INACTIVE)
		goto out;

	/*
	 * If the event is in error state, clear that first.
	 * That way, if we see the event in error state below, we
	 * know that it has gone back into error state, as distinct
	 * from the task having been scheduled away before the
	 * cross-call arrived.
	 */
	if (event->state == PERF_EVENT_STATE_ERROR)
		event->state = PERF_EVENT_STATE_OFF;

retry:
	if (!ctx->is_active) {
		__perf_event_mark_enabled(event);
		goto out;
	}

	spin_unlock_irq(&ctx->lock);

	if (!task_function_call(task, __perf_event_enable, event))
		return;

	spin_lock_irq(&ctx->lock);

	/*
	 * If the context is active and the event is still off,
	 * we need to retry the cross-call.
	 */
	if (ctx->is_active && event->state == PERF_EVENT_STATE_OFF) {
		/*
		 * task could have been flipped by a concurrent
		 * perf_event_context_sched_out()
		 */
		task = ctx->task;
		goto retry;
	}

out:
	spin_unlock_irq(&ctx->lock);
}