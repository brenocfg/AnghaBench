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
struct perf_event_context {scalar_t__ nr_events; scalar_t__ nr_active; int /*<<< orphan*/  pmu; } ;
struct perf_cpu_context {int /*<<< orphan*/  rotation_list; struct perf_event_context* task_ctx; struct perf_event_context ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_FLEXIBLE ; 
 int /*<<< orphan*/  cpu_ctx_sched_out (struct perf_cpu_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx_sched_out (struct perf_event_context*,struct perf_cpu_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_ctx_lock (struct perf_cpu_context*,struct perf_event_context*) ; 
 int /*<<< orphan*/  perf_ctx_unlock (struct perf_cpu_context*,struct perf_event_context*) ; 
 int /*<<< orphan*/  perf_event_sched_in (struct perf_cpu_context*,struct perf_event_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_pmu_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_pmu_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rotate_ctx (struct perf_event_context*) ; 

__attribute__((used)) static void perf_rotate_context(struct perf_cpu_context *cpuctx)
{
	struct perf_event_context *ctx = NULL;
	int rotate = 0, remove = 1;

	if (cpuctx->ctx.nr_events) {
		remove = 0;
		if (cpuctx->ctx.nr_events != cpuctx->ctx.nr_active)
			rotate = 1;
	}

	ctx = cpuctx->task_ctx;
	if (ctx && ctx->nr_events) {
		remove = 0;
		if (ctx->nr_events != ctx->nr_active)
			rotate = 1;
	}

	if (!rotate)
		goto done;

	perf_ctx_lock(cpuctx, cpuctx->task_ctx);
	perf_pmu_disable(cpuctx->ctx.pmu);

	cpu_ctx_sched_out(cpuctx, EVENT_FLEXIBLE);
	if (ctx)
		ctx_sched_out(ctx, cpuctx, EVENT_FLEXIBLE);

	rotate_ctx(&cpuctx->ctx);
	if (ctx)
		rotate_ctx(ctx);

	perf_event_sched_in(cpuctx, ctx, current);

	perf_pmu_enable(cpuctx->ctx.pmu);
	perf_ctx_unlock(cpuctx, cpuctx->task_ctx);
done:
	if (remove)
		list_del_init(&cpuctx->rotation_list);
}