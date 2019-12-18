#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wait_queue_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct eventfd_ctx {TYPE_1__ wqh; } ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  POLLOUT ; 
 int /*<<< orphan*/  __remove_wait_queue (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eventfd_ctx_do_read (struct eventfd_ctx*,scalar_t__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ waitqueue_active (TYPE_1__*) ; 
 int /*<<< orphan*/  wake_up_locked_poll (TYPE_1__*,int /*<<< orphan*/ ) ; 

int eventfd_ctx_remove_wait_queue(struct eventfd_ctx *ctx, wait_queue_t *wait,
				  __u64 *cnt)
{
	unsigned long flags;

	spin_lock_irqsave(&ctx->wqh.lock, flags);
	eventfd_ctx_do_read(ctx, cnt);
	__remove_wait_queue(&ctx->wqh, wait);
	if (*cnt != 0 && waitqueue_active(&ctx->wqh))
		wake_up_locked_poll(&ctx->wqh, POLLOUT);
	spin_unlock_irqrestore(&ctx->wqh.lock, flags);

	return *cnt != 0 ? 0 : -EAGAIN;
}