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
struct perf_event_context {int dummy; } ;
struct perf_event {int /*<<< orphan*/  child_mutex; int /*<<< orphan*/  child_list; struct perf_event* parent; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  free_event (struct perf_event*) ; 
 int /*<<< orphan*/  list_del_event (struct perf_event*,struct perf_event_context*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_group_detach (struct perf_event*) ; 
 int /*<<< orphan*/  put_event (struct perf_event*) ; 

__attribute__((used)) static void perf_free_event(struct perf_event *event,
			    struct perf_event_context *ctx)
{
	struct perf_event *parent = event->parent;

	if (WARN_ON_ONCE(!parent))
		return;

	mutex_lock(&parent->child_mutex);
	list_del_init(&event->child_list);
	mutex_unlock(&parent->child_mutex);

	put_event(parent);

	perf_group_detach(event);
	list_del_event(event, ctx);
	free_event(event);
}