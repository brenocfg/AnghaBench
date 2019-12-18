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
struct task_struct {struct perf_event_context** perf_event_ctxp; } ;
struct perf_event_context {int /*<<< orphan*/  lock; struct task_struct* task; int /*<<< orphan*/  parent_ctx; } ;
struct perf_cpu_context {int /*<<< orphan*/ * task_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_ALL ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 struct perf_cpu_context* __get_cpu_context (struct perf_event_context*) ; 
 scalar_t__ context_equiv (struct perf_event_context*,struct perf_event_context*) ; 
 int /*<<< orphan*/  ctx_sched_out (struct perf_event_context*,struct perf_cpu_context*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  perf_event_sync_stat (struct perf_event_context*,struct perf_event_context*) ; 
 struct perf_event_context* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void perf_event_context_sched_out(struct task_struct *task, int ctxn,
					 struct task_struct *next)
{
	struct perf_event_context *ctx = task->perf_event_ctxp[ctxn];
	struct perf_event_context *next_ctx;
	struct perf_event_context *parent;
	struct perf_cpu_context *cpuctx;
	int do_switch = 1;

	if (likely(!ctx))
		return;

	cpuctx = __get_cpu_context(ctx);
	if (!cpuctx->task_ctx)
		return;

	rcu_read_lock();
	parent = rcu_dereference(ctx->parent_ctx);
	next_ctx = next->perf_event_ctxp[ctxn];
	if (parent && next_ctx &&
	    rcu_dereference(next_ctx->parent_ctx) == parent) {
		/*
		 * Looks like the two contexts are clones, so we might be
		 * able to optimize the context switch.  We lock both
		 * contexts and check that they are clones under the
		 * lock (including re-checking that neither has been
		 * uncloned in the meantime).  It doesn't matter which
		 * order we take the locks because no other cpu could
		 * be trying to lock both of these tasks.
		 */
		spin_lock(&ctx->lock);
		spin_lock_nested(&next_ctx->lock, SINGLE_DEPTH_NESTING);
		if (context_equiv(ctx, next_ctx)) {
			/*
			 * XXX do we need a memory barrier of sorts
			 * wrt to rcu_dereference() of perf_event_ctxp
			 */
			task->perf_event_ctxp[ctxn] = next_ctx;
			next->perf_event_ctxp[ctxn] = ctx;
			ctx->task = next;
			next_ctx->task = task;
			do_switch = 0;

			perf_event_sync_stat(ctx, next_ctx);
		}
		spin_unlock(&next_ctx->lock);
		spin_unlock(&ctx->lock);
	}
	rcu_read_unlock();

	if (do_switch) {
		spin_lock(&ctx->lock);
		ctx_sched_out(ctx, cpuctx, EVENT_ALL);
		cpuctx->task_ctx = NULL;
		spin_unlock(&ctx->lock);
	}
}