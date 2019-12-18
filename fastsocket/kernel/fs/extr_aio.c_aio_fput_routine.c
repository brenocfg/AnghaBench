#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct work_struct {int dummy; } ;
struct kioctx {int /*<<< orphan*/  ctx_lock; } ;
struct kiocb {int /*<<< orphan*/ * ki_filp; int /*<<< orphan*/  ki_list; struct kioctx* ki_ctx; } ;
struct TYPE_3__ {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  __fput (int /*<<< orphan*/ *) ; 
 TYPE_1__ fput_head ; 
 int /*<<< orphan*/  fput_lock ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (TYPE_1__*) ; 
 struct kiocb* list_kiocb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  really_put_req (struct kioctx*,struct kiocb*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aio_fput_routine(struct work_struct *data)
{
	spin_lock_irq(&fput_lock);
	while (likely(!list_empty(&fput_head))) {
		struct kiocb *req = list_kiocb(fput_head.next);
		struct kioctx *ctx = req->ki_ctx;

		list_del(&req->ki_list);
		spin_unlock_irq(&fput_lock);

		/* Complete the fput(s) */
		if (req->ki_filp != NULL)
			__fput(req->ki_filp);

		/* Link the iocb into the context's free list */
		rcu_read_lock();
		spin_lock_irq(&ctx->ctx_lock);
		really_put_req(ctx, req);
		/*
		 * at that point ctx might've been killed, but actual
		 * freeing is RCU'd
		 */
		spin_unlock_irq(&ctx->ctx_lock);
		rcu_read_unlock();

		spin_lock_irq(&fput_lock);
	}
	spin_unlock_irq(&fput_lock);
}