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
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct kioctx {int /*<<< orphan*/  rcu_head; int /*<<< orphan*/ * mm; TYPE_1__ wq; int /*<<< orphan*/  reqs_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aio_free_ring (struct kioctx*) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work (TYPE_1__*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctx_rcu_free ; 
 int /*<<< orphan*/  mmdrop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,struct kioctx*) ; 

__attribute__((used)) static void __put_ioctx(struct kioctx *ctx)
{
	BUG_ON(ctx->reqs_active);

	cancel_delayed_work(&ctx->wq);
	cancel_work_sync(&ctx->wq.work);
	aio_free_ring(ctx);
	mmdrop(ctx->mm);
	ctx->mm = NULL;
	pr_debug("__put_ioctx: freeing %p\n", ctx);
	call_rcu(&ctx->rcu_head, ctx_rcu_free);
}