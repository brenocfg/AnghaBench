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
struct perf_event_context {int /*<<< orphan*/  lock; scalar_t__ task; } ;
struct perf_event {scalar_t__ state; struct perf_event* group_leader; struct perf_event_context* ctx; } ;
struct perf_cpu_context {struct perf_event_context* task_ctx; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PERF_EVENT_STATE_INACTIVE ; 
 scalar_t__ PERF_EVENT_STATE_OFF ; 
 struct perf_cpu_context* __get_cpu_context (struct perf_event_context*) ; 
 int /*<<< orphan*/  event_sched_out (struct perf_event*,struct perf_cpu_context*,struct perf_event_context*) ; 
 int /*<<< orphan*/  group_sched_out (struct perf_event*,struct perf_cpu_context*,struct perf_event_context*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_cgrp_time_from_event (struct perf_event*) ; 
 int /*<<< orphan*/  update_context_time (struct perf_event_context*) ; 
 int /*<<< orphan*/  update_group_times (struct perf_event*) ; 

__attribute__((used)) static int __perf_event_disable(void *info)
{
	struct perf_event *event = info;
	struct perf_event_context *ctx = event->ctx;
	struct perf_cpu_context *cpuctx = __get_cpu_context(ctx);

	/*
	 * If this is a per-task event, need to check whether this
	 * event's task is the current task on this cpu.
	 *
	 * Can trigger due to concurrent perf_event_context_sched_out()
	 * flipping contexts around.
	 */
	if (ctx->task && cpuctx->task_ctx != ctx)
		return -EINVAL;

	spin_lock(&ctx->lock);

	/*
	 * If the event is on, turn it off.
	 * If it is in error state, leave it in error state.
	 */
	if (event->state >= PERF_EVENT_STATE_INACTIVE) {
		update_context_time(ctx);
		update_cgrp_time_from_event(event);
		update_group_times(event);
		if (event == event->group_leader)
			group_sched_out(event, cpuctx, ctx);
		else
			event_sched_out(event, cpuctx, ctx);
		event->state = PERF_EVENT_STATE_OFF;
	}

	spin_unlock(&ctx->lock);

	return 0;
}