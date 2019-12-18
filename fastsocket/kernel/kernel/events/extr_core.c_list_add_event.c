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
struct perf_event_context {int /*<<< orphan*/  nr_stat; int /*<<< orphan*/  nr_events; int /*<<< orphan*/  pmu; int /*<<< orphan*/  event_list; int /*<<< orphan*/  nr_cgroups; } ;
struct TYPE_2__ {scalar_t__ inherit_stat; } ;
struct perf_event {int attach_state; TYPE_1__ attr; int /*<<< orphan*/  event_entry; int /*<<< orphan*/  group_entry; int /*<<< orphan*/  group_flags; struct perf_event* group_leader; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int PERF_ATTACH_CONTEXT ; 
 int /*<<< orphan*/  PERF_GROUP_SOFTWARE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct list_head* ctx_group_list (struct perf_event*,struct perf_event_context*) ; 
 scalar_t__ is_cgroup_event (struct perf_event*) ; 
 scalar_t__ is_software_event (struct perf_event*) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  perf_pmu_rotate_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
list_add_event(struct perf_event *event, struct perf_event_context *ctx)
{
	WARN_ON_ONCE(event->attach_state & PERF_ATTACH_CONTEXT);
	event->attach_state |= PERF_ATTACH_CONTEXT;

	/*
	 * If we're a stand alone event or group leader, we go to the context
	 * list, group events are kept attached to the group so that
	 * perf_group_detach can, at all times, locate all siblings.
	 */
	if (event->group_leader == event) {
		struct list_head *list;

		if (is_software_event(event))
			event->group_flags |= PERF_GROUP_SOFTWARE;

		list = ctx_group_list(event, ctx);
		list_add_tail(&event->group_entry, list);
	}

	if (is_cgroup_event(event))
		ctx->nr_cgroups++;

	list_add_rcu(&event->event_entry, &ctx->event_list);
	if (!ctx->nr_events)
		perf_pmu_rotate_start(ctx->pmu);
	ctx->nr_events++;
	if (event->attr.inherit_stat)
		ctx->nr_stat++;
}