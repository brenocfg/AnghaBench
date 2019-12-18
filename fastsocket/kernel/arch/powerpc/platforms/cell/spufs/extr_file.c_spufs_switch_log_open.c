#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct switch_log_entry {int dummy; } ;
struct switch_log {int dummy; } ;
struct spu_context {TYPE_1__* switch_log; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_4__ {struct spu_context* i_ctx; } ;
struct TYPE_3__ {int /*<<< orphan*/  wait; scalar_t__ tail; scalar_t__ head; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_2__* SPUFS_I (struct inode*) ; 
 int SWITCH_LOG_BUFSIZE ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 TYPE_1__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int spu_acquire (struct spu_context*) ; 
 int /*<<< orphan*/  spu_release (struct spu_context*) ; 

__attribute__((used)) static int spufs_switch_log_open(struct inode *inode, struct file *file)
{
	struct spu_context *ctx = SPUFS_I(inode)->i_ctx;
	int rc;

	rc = spu_acquire(ctx);
	if (rc)
		return rc;

	if (ctx->switch_log) {
		rc = -EBUSY;
		goto out;
	}

	ctx->switch_log = kmalloc(sizeof(struct switch_log) +
		SWITCH_LOG_BUFSIZE * sizeof(struct switch_log_entry),
		GFP_KERNEL);

	if (!ctx->switch_log) {
		rc = -ENOMEM;
		goto out;
	}

	ctx->switch_log->head = ctx->switch_log->tail = 0;
	init_waitqueue_head(&ctx->switch_log->wait);
	rc = 0;

out:
	spu_release(ctx);
	return rc;
}