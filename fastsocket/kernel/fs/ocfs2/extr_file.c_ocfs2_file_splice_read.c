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
struct pipe_inode_info {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_6__ {TYPE_2__* dentry; } ;
struct file {int /*<<< orphan*/  f_vfsmnt; TYPE_3__ f_path; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct TYPE_5__ {TYPE_1__ d_name; struct inode* d_inode; } ;

/* Variables and functions */
 int generic_file_splice_read (struct file*,int /*<<< orphan*/ *,struct pipe_inode_info*,size_t,unsigned int) ; 
 int /*<<< orphan*/  mlog_entry (char*,struct file*,struct pipe_inode_info*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_inode_lock_atime (struct inode*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 

__attribute__((used)) static ssize_t ocfs2_file_splice_read(struct file *in,
				      loff_t *ppos,
				      struct pipe_inode_info *pipe,
				      size_t len,
				      unsigned int flags)
{
	int ret = 0, lock_level = 0;
	struct inode *inode = in->f_path.dentry->d_inode;

	mlog_entry("(0x%p, 0x%p, %u, '%.*s')\n", in, pipe,
		   (unsigned int)len,
		   in->f_path.dentry->d_name.len,
		   in->f_path.dentry->d_name.name);

	/*
	 * See the comment in ocfs2_file_aio_read()
	 */
	ret = ocfs2_inode_lock_atime(inode, in->f_vfsmnt, &lock_level);
	if (ret < 0) {
		mlog_errno(ret);
		goto bail;
	}
	ocfs2_inode_unlock(inode, lock_level);

	ret = generic_file_splice_read(in, ppos, pipe, len, flags);

bail:
	mlog_exit(ret);
	return ret;
}