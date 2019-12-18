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
struct perf_event_context {int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; int /*<<< orphan*/  parent_ctx; } ;
struct perf_event {struct perf_event_context* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_event (struct perf_event*) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_group_detach (struct perf_event*) ; 
 int /*<<< orphan*/  perf_remove_from_context (struct perf_event*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int perf_event_release_kernel(struct perf_event *event)
{
	struct perf_event_context *ctx = event->ctx;

	WARN_ON_ONCE(ctx->parent_ctx);
	/*
	 * There are two ways this annotation is useful:
	 *
	 *  1) there is a lock recursion from perf_event_exit_task
	 *     see the comment there.
	 *
	 *  2) there is a lock-inversion with mmap_sem through
	 *     perf_event_read_group(), which takes faults while
	 *     holding ctx->mutex, however this is called after
	 *     the last filedesc died, so there is no possibility
	 *     to trigger the AB-BA case.
	 */
	mutex_lock_nested(&ctx->mutex, SINGLE_DEPTH_NESTING);
	spin_lock_irq(&ctx->lock);
	perf_group_detach(event);
	spin_unlock_irq(&ctx->lock);
	perf_remove_from_context(event);
	mutex_unlock(&ctx->mutex);

	free_event(event);

	return 0;
}