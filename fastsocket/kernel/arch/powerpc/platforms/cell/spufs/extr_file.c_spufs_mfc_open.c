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
struct spufs_inode_info {int /*<<< orphan*/  i_openers; struct spu_context* i_ctx; } ;
struct spu_context {scalar_t__ owner; int /*<<< orphan*/  mapping_lock; int /*<<< orphan*/  mfc; } ;
struct inode {int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_count; } ;
struct file {struct spu_context* private_data; } ;
struct TYPE_2__ {scalar_t__ mm; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 struct spufs_inode_info* SPUFS_I (struct inode*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nonseekable_open (struct inode*,struct file*) ; 

__attribute__((used)) static int spufs_mfc_open(struct inode *inode, struct file *file)
{
	struct spufs_inode_info *i = SPUFS_I(inode);
	struct spu_context *ctx = i->i_ctx;

	/* we don't want to deal with DMA into other processes */
	if (ctx->owner != current->mm)
		return -EINVAL;

	if (atomic_read(&inode->i_count) != 1)
		return -EBUSY;

	mutex_lock(&ctx->mapping_lock);
	file->private_data = ctx;
	if (!i->i_openers++)
		ctx->mfc = inode->i_mapping;
	mutex_unlock(&ctx->mapping_lock);
	return nonseekable_open(inode, file);
}