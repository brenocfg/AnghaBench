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
struct perf_event_context {int /*<<< orphan*/  lock; scalar_t__ is_active; scalar_t__ task; } ;
struct perf_event {scalar_t__ state; TYPE_1__* pmu; struct perf_event_context* ctx; } ;
struct perf_cpu_context {struct perf_event_context* task_ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* read ) (struct perf_event*) ;} ;

/* Variables and functions */
 scalar_t__ PERF_EVENT_STATE_ACTIVE ; 
 struct perf_cpu_context* __get_cpu_context (struct perf_event_context*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct perf_event*) ; 
 int /*<<< orphan*/  update_cgrp_time_from_event (struct perf_event*) ; 
 int /*<<< orphan*/  update_context_time (struct perf_event_context*) ; 
 int /*<<< orphan*/  update_event_times (struct perf_event*) ; 

__attribute__((used)) static void __perf_event_read(void *info)
{
	struct perf_event *event = info;
	struct perf_event_context *ctx = event->ctx;
	struct perf_cpu_context *cpuctx = __get_cpu_context(ctx);

	/*
	 * If this is a task context, we need to check whether it is
	 * the current task context of this cpu.  If not it has been
	 * scheduled out before the smp call arrived.  In that case
	 * event->count would have been updated to a recent sample
	 * when the event was scheduled out.
	 */
	if (ctx->task && cpuctx->task_ctx != ctx)
		return;

	spin_lock(&ctx->lock);
	if (ctx->is_active) {
		update_context_time(ctx);
		update_cgrp_time_from_event(event);
	}
	update_event_times(event);
	if (event->state == PERF_EVENT_STATE_ACTIVE)
		event->pmu->read(event);
	spin_unlock(&ctx->lock);
}