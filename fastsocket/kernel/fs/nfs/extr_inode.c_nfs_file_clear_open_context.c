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
struct nfs_open_context {int /*<<< orphan*/  list; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;
struct TYPE_5__ {TYPE_1__* dentry; } ;
struct file {int /*<<< orphan*/ * private_data; TYPE_2__ f_path; } ;
struct TYPE_6__ {int /*<<< orphan*/  open_files; } ;
struct TYPE_4__ {struct inode* d_inode; } ;

/* Variables and functions */
 TYPE_3__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nfs_open_context* nfs_file_open_context (struct file*) ; 
 int /*<<< orphan*/  put_nfs_open_context_sync (struct nfs_open_context*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_file_clear_open_context(struct file *filp)
{
	struct inode *inode = filp->f_path.dentry->d_inode;
	struct nfs_open_context *ctx = nfs_file_open_context(filp);

	if (ctx) {
		filp->private_data = NULL;
		spin_lock(&inode->i_lock);
		list_move_tail(&ctx->list, &NFS_I(inode)->open_files);
		spin_unlock(&inode->i_lock);
		put_nfs_open_context_sync(ctx);
	}
}