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
struct task_struct {int /*<<< orphan*/ * perf_event_ctxp; } ;
struct perf_event_context {int /*<<< orphan*/  lock; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 struct perf_event_context* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct perf_event_context *
perf_lock_task_context(struct task_struct *task, int ctxn, unsigned long *flags)
{
	struct perf_event_context *ctx;

	rcu_read_lock();
retry:
	ctx = rcu_dereference(task->perf_event_ctxp[ctxn]);
	if (ctx) {
		/*
		 * If this context is a clone of another, it might
		 * get swapped for another underneath us by
		 * perf_event_task_sched_out, though the
		 * rcu_read_lock() protects us from any context
		 * getting freed.  Lock the context and check if it
		 * got swapped before we could get the lock, and retry
		 * if so.  If we locked the right context, then it
		 * can't get swapped on us any more.
		 */
		spin_lock_irqsave(&ctx->lock, *flags);
		if (ctx != rcu_dereference(task->perf_event_ctxp[ctxn])) {
			spin_unlock_irqrestore(&ctx->lock, *flags);
			goto retry;
		}

		if (!atomic_inc_not_zero(&ctx->refcount)) {
			spin_unlock_irqrestore(&ctx->lock, *flags);
			ctx = NULL;
		}
	}
	rcu_read_unlock();
	return ctx;
}