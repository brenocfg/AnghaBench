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
struct perf_event_context {int /*<<< orphan*/  lock; int /*<<< orphan*/  is_active; } ;
struct TYPE_2__ {scalar_t__ pinned; } ;
struct perf_event {scalar_t__ state; TYPE_1__ attr; struct perf_event* group_leader; struct perf_event_context* ctx; } ;
struct perf_cpu_context {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 scalar_t__ PERF_EVENT_STATE_ACTIVE ; 
 scalar_t__ PERF_EVENT_STATE_ERROR ; 
 scalar_t__ PERF_EVENT_STATE_INACTIVE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct perf_cpu_context* __get_cpu_context (struct perf_event_context*) ; 
 int /*<<< orphan*/  __perf_event_mark_enabled (struct perf_event*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  event_filter_match (struct perf_event*) ; 
 int event_sched_in (struct perf_event*,struct perf_cpu_context*,struct perf_event_context*) ; 
 int /*<<< orphan*/  group_can_go_on (struct perf_event*,struct perf_cpu_context*,int) ; 
 int group_sched_in (struct perf_event*,struct perf_cpu_context*,struct perf_event_context*) ; 
 int /*<<< orphan*/  group_sched_out (struct perf_event*,struct perf_cpu_context*,struct perf_event_context*) ; 
 scalar_t__ is_cgroup_event (struct perf_event*) ; 
 int /*<<< orphan*/  perf_cgroup_defer_enabled (struct perf_event*) ; 
 int /*<<< orphan*/  perf_cgroup_set_timestamp (int /*<<< orphan*/ ,struct perf_event_context*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_context_time (struct perf_event_context*) ; 
 int /*<<< orphan*/  update_group_times (struct perf_event*) ; 

__attribute__((used)) static int __perf_event_enable(void *info)
{
	struct perf_event *event = info;
	struct perf_event_context *ctx = event->ctx;
	struct perf_event *leader = event->group_leader;
	struct perf_cpu_context *cpuctx = __get_cpu_context(ctx);
	int err;

	if (WARN_ON_ONCE(!ctx->is_active))
		return -EINVAL;

	spin_lock(&ctx->lock);
	update_context_time(ctx);

	if (event->state >= PERF_EVENT_STATE_INACTIVE)
		goto unlock;

	/*
	 * set current task's cgroup time reference point
	 */
	perf_cgroup_set_timestamp(current, ctx);

	__perf_event_mark_enabled(event);

	if (!event_filter_match(event)) {
		if (is_cgroup_event(event))
			perf_cgroup_defer_enabled(event);
		goto unlock;
	}

	/*
	 * If the event is in a group and isn't the group leader,
	 * then don't put it on unless the group is on.
	 */
	if (leader != event && leader->state != PERF_EVENT_STATE_ACTIVE)
		goto unlock;

	if (!group_can_go_on(event, cpuctx, 1)) {
		err = -EEXIST;
	} else {
		if (event == leader)
			err = group_sched_in(event, cpuctx, ctx);
		else
			err = event_sched_in(event, cpuctx, ctx);
	}

	if (err) {
		/*
		 * If this event can't go on and it's part of a
		 * group, then the whole group has to come off.
		 */
		if (leader != event)
			group_sched_out(leader, cpuctx, ctx);
		if (leader->attr.pinned) {
			update_group_times(leader);
			leader->state = PERF_EVENT_STATE_ERROR;
		}
	}

unlock:
	spin_unlock(&ctx->lock);

	return 0;
}