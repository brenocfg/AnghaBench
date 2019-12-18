#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct perf_event_context {struct task_struct* task; int /*<<< orphan*/  lock; } ;
struct perf_event {struct perf_event_context* ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  pmu; } ;
struct perf_cpu_context {TYPE_1__ ctx; struct perf_event_context* task_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_ALL ; 
 struct perf_cpu_context* __get_cpu_context (struct perf_event_context*) ; 
 int /*<<< orphan*/  add_event_to_ctx (struct perf_event*,struct perf_event_context*) ; 
 int /*<<< orphan*/  cpu_ctx_sched_out (struct perf_cpu_context*,int /*<<< orphan*/ ) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  perf_ctx_lock (struct perf_cpu_context*,struct perf_event_context*) ; 
 int /*<<< orphan*/  perf_ctx_unlock (struct perf_cpu_context*,struct perf_event_context*) ; 
 int /*<<< orphan*/  perf_event_sched_in (struct perf_cpu_context*,struct perf_event_context*,struct task_struct*) ; 
 int /*<<< orphan*/  perf_pmu_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_pmu_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_ctx_sched_out (struct perf_event_context*) ; 
 int /*<<< orphan*/  update_cgrp_time_from_event (struct perf_event*) ; 
 int /*<<< orphan*/  update_context_time (struct perf_event_context*) ; 

__attribute__((used)) static int  __perf_install_in_context(void *info)
{
	struct perf_event *event = info;
	struct perf_event_context *ctx = event->ctx;
	struct perf_cpu_context *cpuctx = __get_cpu_context(ctx);
	struct perf_event_context *task_ctx = cpuctx->task_ctx;
	struct task_struct *task = current;

	perf_ctx_lock(cpuctx, task_ctx);
	perf_pmu_disable(cpuctx->ctx.pmu);

	/*
	 * If there was an active task_ctx schedule it out.
	 */
	if (task_ctx)
		task_ctx_sched_out(task_ctx);

	/*
	 * If the context we're installing events in is not the
	 * active task_ctx, flip them.
	 */
	if (ctx->task && task_ctx != ctx) {
		if (task_ctx)
			spin_unlock(&task_ctx->lock);
		spin_lock(&ctx->lock);
		task_ctx = ctx;
	}

	if (task_ctx) {
		cpuctx->task_ctx = task_ctx;
		task = task_ctx->task;
	}

	cpu_ctx_sched_out(cpuctx, EVENT_ALL);

	update_context_time(ctx);
	/*
	 * update cgrp time only if current cgrp
	 * matches event->cgrp. Must be done before
	 * calling add_event_to_ctx()
	 */
	update_cgrp_time_from_event(event);

	add_event_to_ctx(event, ctx);

	/*
	 * Schedule everything back in
	 */
	perf_event_sched_in(cpuctx, task_ctx, task);

	perf_pmu_enable(cpuctx->ctx.pmu);
	perf_ctx_unlock(cpuctx, task_ctx);

	return 0;
}