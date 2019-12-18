#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct perf_event_context {int /*<<< orphan*/  nr_freq; int /*<<< orphan*/  nr_active; } ;
struct TYPE_4__ {scalar_t__ exclusive; scalar_t__ sample_freq; scalar_t__ freq; } ;
struct perf_event {scalar_t__ state; void* tstamp_stopped; int oncpu; TYPE_2__ attr; TYPE_1__* pmu; scalar_t__ pending_disable; int /*<<< orphan*/  tstamp_running; } ;
struct perf_cpu_context {scalar_t__ exclusive; int /*<<< orphan*/  active_oncpu; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* del ) (struct perf_event*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ PERF_EVENT_STATE_ACTIVE ; 
 scalar_t__ PERF_EVENT_STATE_INACTIVE ; 
 scalar_t__ PERF_EVENT_STATE_OFF ; 
 int /*<<< orphan*/  event_filter_match (struct perf_event*) ; 
 int /*<<< orphan*/  is_software_event (struct perf_event*) ; 
 void* perf_event_time (struct perf_event*) ; 
 int /*<<< orphan*/  stub1 (struct perf_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
event_sched_out(struct perf_event *event,
		  struct perf_cpu_context *cpuctx,
		  struct perf_event_context *ctx)
{
	u64 tstamp = perf_event_time(event);
	u64 delta;
	/*
	 * An event which could not be activated because of
	 * filter mismatch still needs to have its timings
	 * maintained, otherwise bogus information is return
	 * via read() for time_enabled, time_running:
	 */
	if (event->state == PERF_EVENT_STATE_INACTIVE
	    && !event_filter_match(event)) {
		delta = tstamp - event->tstamp_stopped;
		event->tstamp_running += delta;
		event->tstamp_stopped = tstamp;
	}

	if (event->state != PERF_EVENT_STATE_ACTIVE)
		return;

	event->state = PERF_EVENT_STATE_INACTIVE;
	if (event->pending_disable) {
		event->pending_disable = 0;
		event->state = PERF_EVENT_STATE_OFF;
	}
	event->tstamp_stopped = tstamp;
	event->pmu->del(event, 0);
	event->oncpu = -1;

	if (!is_software_event(event))
		cpuctx->active_oncpu--;
	ctx->nr_active--;
	if (event->attr.freq && event->attr.sample_freq)
		ctx->nr_freq--;
	if (event->attr.exclusive || !cpuctx->active_oncpu)
		cpuctx->exclusive = 0;
}