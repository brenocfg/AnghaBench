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
struct nfs_open_context {int /*<<< orphan*/  error; int /*<<< orphan*/  flags; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_3__ d_name; TYPE_2__* d_parent; struct inode* d_inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_1__ d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLUSH_SYNC ; 
 int /*<<< orphan*/  NFSIOS_VFSFSYNC ; 
 int /*<<< orphan*/  NFS_CONTEXT_ERROR_WRITE ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nfs_commit_inode (struct inode*,int /*<<< orphan*/ ) ; 
 struct nfs_open_context* nfs_file_open_context (struct file*) ; 
 int /*<<< orphan*/  nfs_inc_stats (struct inode*,int /*<<< orphan*/ ) ; 
 int pnfs_layoutcommit_inode (struct inode*,int) ; 
 int test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_file_fsync(struct file *file, struct dentry *dentry, int datasync)
{
	struct nfs_open_context *ctx = nfs_file_open_context(file);
	struct inode *inode = dentry->d_inode;
	int have_error, status;
	int ret = 0;


	dprintk("NFS: fsync file(%s/%s) datasync %d\n",
			dentry->d_parent->d_name.name, dentry->d_name.name,
			datasync);

	nfs_inc_stats(inode, NFSIOS_VFSFSYNC);
	have_error = test_and_clear_bit(NFS_CONTEXT_ERROR_WRITE, &ctx->flags);
	status = nfs_commit_inode(inode, FLUSH_SYNC);
	have_error |= test_bit(NFS_CONTEXT_ERROR_WRITE, &ctx->flags);
	if (have_error)
		ret = xchg(&ctx->error, 0);
	if (!ret && status < 0)
		ret = status;
	if (!ret && !datasync)
		/* application has asked for meta-data sync */
		ret = pnfs_layoutcommit_inode(inode, true);
	return ret;
}