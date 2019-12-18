#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct spu_context {TYPE_3__* switch_log; } ;
struct inode {int dummy; } ;
struct TYPE_6__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
typedef  int /*<<< orphan*/  poll_table ;
struct TYPE_8__ {struct spu_context* i_ctx; } ;
struct TYPE_7__ {int /*<<< orphan*/  wait; } ;
struct TYPE_5__ {struct inode* d_inode; } ;

/* Variables and functions */
 unsigned int POLLIN ; 
 TYPE_4__* SPUFS_I (struct inode*) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int spu_acquire (struct spu_context*) ; 
 int /*<<< orphan*/  spu_release (struct spu_context*) ; 
 scalar_t__ spufs_switch_log_used (struct spu_context*) ; 

__attribute__((used)) static unsigned int spufs_switch_log_poll(struct file *file, poll_table *wait)
{
	struct inode *inode = file->f_path.dentry->d_inode;
	struct spu_context *ctx = SPUFS_I(inode)->i_ctx;
	unsigned int mask = 0;
	int rc;

	poll_wait(file, &ctx->switch_log->wait, wait);

	rc = spu_acquire(ctx);
	if (rc)
		return rc;

	if (spufs_switch_log_used(ctx) > 0)
		mask |= POLLIN;

	spu_release(ctx);

	return mask;
}