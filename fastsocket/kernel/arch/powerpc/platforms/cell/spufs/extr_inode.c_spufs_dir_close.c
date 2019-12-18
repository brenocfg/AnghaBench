#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct spu_context {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mutex; } ;
struct TYPE_4__ {struct dentry* dentry; } ;
struct file {TYPE_1__ f_path; } ;
struct dentry {int /*<<< orphan*/  d_inode; TYPE_2__* d_parent; } ;
struct TYPE_6__ {struct spu_context* i_ctx; } ;
struct TYPE_5__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 TYPE_3__* SPUFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int dcache_dir_close (struct inode*,struct file*) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spu_forget (struct spu_context*) ; 
 int spufs_rmdir (struct inode*,struct dentry*) ; 

__attribute__((used)) static int spufs_dir_close(struct inode *inode, struct file *file)
{
	struct spu_context *ctx;
	struct inode *parent;
	struct dentry *dir;
	int ret;

	dir = file->f_path.dentry;
	parent = dir->d_parent->d_inode;
	ctx = SPUFS_I(dir->d_inode)->i_ctx;

	mutex_lock_nested(&parent->i_mutex, I_MUTEX_PARENT);
	ret = spufs_rmdir(parent, dir);
	mutex_unlock(&parent->i_mutex);
	WARN_ON(ret);

	/* We have to give up the mm_struct */
	spu_forget(ctx);

	return dcache_dir_close(inode, file);
}