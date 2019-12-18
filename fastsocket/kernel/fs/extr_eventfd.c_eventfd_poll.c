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
struct file {struct eventfd_ctx* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct eventfd_ctx {scalar_t__ count; TYPE_1__ wqh; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int POLLERR ; 
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 int ULLONG_MAX ; 
 int /*<<< orphan*/  poll_wait (struct file*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int eventfd_poll(struct file *file, poll_table *wait)
{
	struct eventfd_ctx *ctx = file->private_data;
	unsigned int events = 0;
	unsigned long flags;

	poll_wait(file, &ctx->wqh, wait);

	spin_lock_irqsave(&ctx->wqh.lock, flags);
	if (ctx->count > 0)
		events |= POLLIN;
	if (ctx->count == ULLONG_MAX)
		events |= POLLERR;
	if (ULLONG_MAX - 1 > ctx->count)
		events |= POLLOUT;
	spin_unlock_irqrestore(&ctx->wqh.lock, flags);

	return events;
}