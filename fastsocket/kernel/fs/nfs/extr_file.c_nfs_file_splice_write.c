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
struct pipe_inode_info {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_8__ {struct dentry* dentry; } ;
struct file {TYPE_4__ f_path; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_3__ d_name; TYPE_2__* d_parent; struct inode* d_inode; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_1__ d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSIOS_NORMALWRITTENBYTES ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned long long) ; 
 scalar_t__ generic_file_splice_write (struct pipe_inode_info*,struct file*,scalar_t__*,size_t,unsigned int) ; 
 int /*<<< orphan*/  nfs_add_stats (struct inode*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ nfs_need_sync_write (struct file*,struct inode*) ; 
 int vfs_fsync (struct file*,struct dentry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t nfs_file_splice_write(struct pipe_inode_info *pipe,
				     struct file *filp, loff_t *ppos,
				     size_t count, unsigned int flags)
{
	struct dentry *dentry = filp->f_path.dentry;
	struct inode *inode = dentry->d_inode;
	ssize_t ret;

	dprintk("NFS splice_write(%s/%s, %lu@%llu)\n",
		dentry->d_parent->d_name.name, dentry->d_name.name,
		(unsigned long) count, (unsigned long long) *ppos);

	/*
	 * The combination of splice and an O_APPEND destination is disallowed.
	 */

	nfs_add_stats(inode, NFSIOS_NORMALWRITTENBYTES, count);

	ret = generic_file_splice_write(pipe, filp, ppos, count, flags);
	if (ret >= 0 && nfs_need_sync_write(filp, inode)) {
		int err = vfs_fsync(filp, dentry, 0);
		if (err < 0)
			ret = err;
	}
	return ret;
}