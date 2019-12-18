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
typedef  int /*<<< orphan*/  u64 ;
struct task_struct {int dummy; } ;
struct TYPE_4__ {scalar_t__ inherit_stat; } ;
struct perf_event {int /*<<< orphan*/  child_mutex; int /*<<< orphan*/  child_list; TYPE_1__* ctx; int /*<<< orphan*/  child_total_time_running; int /*<<< orphan*/  total_time_running; int /*<<< orphan*/  child_total_time_enabled; int /*<<< orphan*/  total_time_enabled; int /*<<< orphan*/  child_count; TYPE_2__ attr; struct perf_event* parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic64_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_event_count (struct perf_event*) ; 
 int /*<<< orphan*/  perf_event_read_event (struct perf_event*,struct task_struct*) ; 
 int /*<<< orphan*/  put_event (struct perf_event*) ; 

__attribute__((used)) static void sync_child_event(struct perf_event *child_event,
			       struct task_struct *child)
{
	struct perf_event *parent_event = child_event->parent;
	u64 child_val;

	if (child_event->attr.inherit_stat)
		perf_event_read_event(child_event, child);

	child_val = perf_event_count(child_event);

	/*
	 * Add back the child's count to the parent's count:
	 */
	atomic64_add(child_val, &parent_event->child_count);
	atomic64_add(child_event->total_time_enabled,
		     &parent_event->child_total_time_enabled);
	atomic64_add(child_event->total_time_running,
		     &parent_event->child_total_time_running);

	/*
	 * Remove this event from the parent's list
	 */
	WARN_ON_ONCE(parent_event->ctx->parent_ctx);
	mutex_lock(&parent_event->child_mutex);
	list_del_init(&child_event->child_list);
	mutex_unlock(&parent_event->child_mutex);

	/*
	 * Release the parent event, if this was the last
	 * reference to it.
	 */
	put_event(parent_event);
}