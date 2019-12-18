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
struct spufs_inode_info {int /*<<< orphan*/  i_openers; struct spu_context* i_ctx; } ;
struct spu_context {int /*<<< orphan*/  mapping_lock; int /*<<< orphan*/ * local_store; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct spufs_inode_info* SPUFS_I (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
spufs_mem_release(struct inode *inode, struct file *file)
{
	struct spufs_inode_info *i = SPUFS_I(inode);
	struct spu_context *ctx = i->i_ctx;

	mutex_lock(&ctx->mapping_lock);
	if (!--i->i_openers)
		ctx->local_store = NULL;
	mutex_unlock(&ctx->mapping_lock);
	return 0;
}