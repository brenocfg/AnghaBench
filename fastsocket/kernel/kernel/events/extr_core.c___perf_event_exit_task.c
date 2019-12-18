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
struct task_struct {int dummy; } ;
struct perf_event_context {int /*<<< orphan*/  lock; } ;
struct perf_event {scalar_t__ parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_event (struct perf_event*) ; 
 int /*<<< orphan*/  perf_group_detach (struct perf_event*) ; 
 int /*<<< orphan*/  perf_remove_from_context (struct perf_event*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_child_event (struct perf_event*,struct task_struct*) ; 

__attribute__((used)) static void
__perf_event_exit_task(struct perf_event *child_event,
			 struct perf_event_context *child_ctx,
			 struct task_struct *child)
{
	if (child_event->parent) {
		spin_lock_irq(&child_ctx->lock);
		perf_group_detach(child_event);
		spin_unlock_irq(&child_ctx->lock);
	}

	perf_remove_from_context(child_event);

	/*
	 * It can happen that the parent exits first, and has events
	 * that are still around due to the child reference. These
	 * events need to be zapped.
	 */
	if (child_event->parent) {
		sync_child_event(child_event, child);
		free_event(child_event);
	}
}