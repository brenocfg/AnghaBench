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
struct perf_event_context {int /*<<< orphan*/  refcount; int /*<<< orphan*/  event_list; int /*<<< orphan*/  flexible_groups; int /*<<< orphan*/  pinned_groups; int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __perf_event_init_context(struct perf_event_context *ctx)
{
	spin_lock_init(&ctx->lock);
	mutex_init(&ctx->mutex);
	INIT_LIST_HEAD(&ctx->pinned_groups);
	INIT_LIST_HEAD(&ctx->flexible_groups);
	INIT_LIST_HEAD(&ctx->event_list);
	atomic_set(&ctx->refcount, 1);
}