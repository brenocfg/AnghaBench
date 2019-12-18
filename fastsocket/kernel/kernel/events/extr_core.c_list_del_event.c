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
struct perf_event_context {int /*<<< orphan*/  nr_stat; int /*<<< orphan*/  nr_events; int /*<<< orphan*/  nr_cgroups; } ;
struct TYPE_2__ {scalar_t__ inherit_stat; } ;
struct perf_event {int attach_state; scalar_t__ state; int /*<<< orphan*/  group_entry; struct perf_event* group_leader; int /*<<< orphan*/  event_entry; TYPE_1__ attr; } ;
struct perf_cpu_context {int /*<<< orphan*/ * cgrp; } ;

/* Variables and functions */
 int PERF_ATTACH_CONTEXT ; 
 scalar_t__ PERF_EVENT_STATE_OFF ; 
 struct perf_cpu_context* __get_cpu_context (struct perf_event_context*) ; 
 scalar_t__ is_cgroup_event (struct perf_event*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_group_times (struct perf_event*) ; 

__attribute__((used)) static void
list_del_event(struct perf_event *event, struct perf_event_context *ctx)
{
	struct perf_cpu_context *cpuctx;
	/*
	 * We can have double detach due to exit/hot-unplug + close.
	 */
	if (!(event->attach_state & PERF_ATTACH_CONTEXT))
		return;

	event->attach_state &= ~PERF_ATTACH_CONTEXT;

	if (is_cgroup_event(event)) {
		ctx->nr_cgroups--;
		cpuctx = __get_cpu_context(ctx);
		/*
		 * if there are no more cgroup events
		 * then cler cgrp to avoid stale pointer
		 * in update_cgrp_time_from_cpuctx()
		 */
		if (!ctx->nr_cgroups)
			cpuctx->cgrp = NULL;
	}

	ctx->nr_events--;
	if (event->attr.inherit_stat)
		ctx->nr_stat--;

	list_del_rcu(&event->event_entry);

	if (event->group_leader == event)
		list_del_init(&event->group_entry);

	update_group_times(event);

	/*
	 * If event was in error state, then keep it
	 * that way, otherwise bogus counts will be
	 * returned on read(). The only way to get out
	 * of error state is by explicit re-enabling
	 * of the event
	 */
	if (event->state > PERF_EVENT_STATE_OFF)
		event->state = PERF_EVENT_STATE_OFF;
}