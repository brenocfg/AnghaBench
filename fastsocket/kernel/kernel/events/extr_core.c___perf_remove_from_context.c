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
struct perf_event_context {int /*<<< orphan*/  lock; scalar_t__ is_active; int /*<<< orphan*/  nr_events; } ;
struct perf_event {struct perf_event_context* ctx; } ;
struct perf_cpu_context {struct perf_event_context* task_ctx; } ;

/* Variables and functions */
 struct perf_cpu_context* __get_cpu_context (struct perf_event_context*) ; 
 int /*<<< orphan*/  event_sched_out (struct perf_event*,struct perf_cpu_context*,struct perf_event_context*) ; 
 int /*<<< orphan*/  list_del_event (struct perf_event*,struct perf_event_context*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __perf_remove_from_context(void *info)
{
	struct perf_event *event = info;
	struct perf_event_context *ctx = event->ctx;
	struct perf_cpu_context *cpuctx = __get_cpu_context(ctx);

	spin_lock(&ctx->lock);
	event_sched_out(event, cpuctx, ctx);
	list_del_event(event, ctx);
	if (!ctx->nr_events && cpuctx->task_ctx == ctx) {
		ctx->is_active = 0;
		cpuctx->task_ctx = NULL;
	}
	spin_unlock(&ctx->lock);

	return 0;
}