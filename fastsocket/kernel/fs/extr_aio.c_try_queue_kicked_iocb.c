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
struct kioctx {int /*<<< orphan*/  ctx_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  task_list; } ;
struct kiocb {TYPE_1__ ki_wait; struct kioctx* ki_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int __queue_kicked_iocb (struct kiocb*) ; 
 int /*<<< orphan*/  aio_queue_work (struct kioctx*) ; 
 int /*<<< orphan*/  kiocbTryKick (struct kiocb*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void try_queue_kicked_iocb(struct kiocb *iocb)
{
 	struct kioctx	*ctx = iocb->ki_ctx;
	unsigned long flags;
	int run = 0;

	/* We're supposed to be the only path putting the iocb back on the run
	 * list.  If we find that the iocb is *back* on a wait queue already
	 * than retry has happened before we could queue the iocb.  This also
	 * means that the retry could have completed and freed our iocb, no
	 * good. */
	BUG_ON((!list_empty(&iocb->ki_wait.task_list)));

	spin_lock_irqsave(&ctx->ctx_lock, flags);
	/* set this inside the lock so that we can't race with aio_run_iocb()
	 * testing it and putting the iocb on the run list under the lock */
	if (!kiocbTryKick(iocb))
		run = __queue_kicked_iocb(iocb);
	spin_unlock_irqrestore(&ctx->ctx_lock, flags);
	if (run)
		aio_queue_work(ctx);
}