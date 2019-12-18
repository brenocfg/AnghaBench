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
typedef  int /*<<< orphan*/  u64 ;
struct perf_event_context {int /*<<< orphan*/  lock; scalar_t__ is_active; } ;
struct perf_event {scalar_t__ state; struct perf_event_context* ctx; int /*<<< orphan*/  oncpu; } ;

/* Variables and functions */
 scalar_t__ PERF_EVENT_STATE_ACTIVE ; 
 scalar_t__ PERF_EVENT_STATE_INACTIVE ; 
 int /*<<< orphan*/  __perf_event_read ; 
 int /*<<< orphan*/  perf_event_count (struct perf_event*) ; 
 int /*<<< orphan*/  smp_call_function_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct perf_event*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  update_cgrp_time_from_event (struct perf_event*) ; 
 int /*<<< orphan*/  update_context_time (struct perf_event_context*) ; 
 int /*<<< orphan*/  update_event_times (struct perf_event*) ; 

__attribute__((used)) static u64 perf_event_read(struct perf_event *event)
{
	/*
	 * If event is enabled and currently active on a CPU, update the
	 * value in the event structure:
	 */
	if (event->state == PERF_EVENT_STATE_ACTIVE) {
		smp_call_function_single(event->oncpu,
					 __perf_event_read, event, 1);
	} else if (event->state == PERF_EVENT_STATE_INACTIVE) {
		struct perf_event_context *ctx = event->ctx;
		unsigned long flags;

		spin_lock_irqsave(&ctx->lock, flags);
		/*
		 * may read while context is not active
		 * (e.g., thread is blocked), in that case
		 * we cannot update context time
		 */
		if (ctx->is_active) {
			update_context_time(ctx);
			update_cgrp_time_from_event(event);
		}
		update_event_times(event);
		spin_unlock_irqrestore(&ctx->lock, flags);
	}

	return perf_event_count(event);
}