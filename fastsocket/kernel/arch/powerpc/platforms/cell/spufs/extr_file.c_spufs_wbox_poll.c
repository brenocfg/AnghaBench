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
struct spu_context {TYPE_1__* ops; int /*<<< orphan*/  state_mutex; int /*<<< orphan*/  wbox_wq; } ;
struct file {struct spu_context* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
struct TYPE_2__ {unsigned int (* mbox_stat_poll ) (struct spu_context*,int) ;} ;

/* Variables and functions */
 int POLLOUT ; 
 int POLLWRNORM ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spu_release (struct spu_context*) ; 
 unsigned int stub1 (struct spu_context*,int) ; 

__attribute__((used)) static unsigned int spufs_wbox_poll(struct file *file, poll_table *wait)
{
	struct spu_context *ctx = file->private_data;
	unsigned int mask;

	poll_wait(file, &ctx->wbox_wq, wait);

	/*
	 * For now keep this uninterruptible and also ignore the rule
	 * that poll should not sleep.  Will be fixed later.
	 */
	mutex_lock(&ctx->state_mutex);
	mask = ctx->ops->mbox_stat_poll(ctx, POLLOUT | POLLWRNORM);
	spu_release(ctx);

	return mask;
}