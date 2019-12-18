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
struct kiocb {int /*<<< orphan*/  ki_pos; struct file* ki_filp; } ;
struct iovec {int dummy; } ;
struct inode {int /*<<< orphan*/  i_alloc_sem; } ;
struct TYPE_6__ {TYPE_2__* dentry; } ;
struct file {int f_flags; int /*<<< orphan*/  f_vfsmnt; TYPE_3__ f_path; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct TYPE_5__ {TYPE_1__ d_name; struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int EIOCBQUEUED ; 
 int O_DIRECT ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int generic_file_aio_read (struct kiocb*,struct iovec const*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlog_entry (char*,struct file*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_inode_lock_atime (struct inode*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int /*<<< orphan*/  ocfs2_iocb_is_rw_locked (struct kiocb*) ; 
 int /*<<< orphan*/  ocfs2_iocb_set_rw_locked (struct kiocb*,int) ; 
 int ocfs2_rw_lock (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_rw_unlock (struct inode*,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t ocfs2_file_aio_read(struct kiocb *iocb,
				   const struct iovec *iov,
				   unsigned long nr_segs,
				   loff_t pos)
{
	int ret = 0, rw_level = -1, have_alloc_sem = 0, lock_level = 0;
	struct file *filp = iocb->ki_filp;
	struct inode *inode = filp->f_path.dentry->d_inode;

	mlog_entry("(0x%p, %u, '%.*s')\n", filp,
		   (unsigned int)nr_segs,
		   filp->f_path.dentry->d_name.len,
		   filp->f_path.dentry->d_name.name);

	if (!inode) {
		ret = -EINVAL;
		mlog_errno(ret);
		goto bail;
	}

	/* 
	 * buffered reads protect themselves in ->readpage().  O_DIRECT reads
	 * need locks to protect pending reads from racing with truncate.
	 */
	if (filp->f_flags & O_DIRECT) {
		down_read(&inode->i_alloc_sem);
		have_alloc_sem = 1;

		ret = ocfs2_rw_lock(inode, 0);
		if (ret < 0) {
			mlog_errno(ret);
			goto bail;
		}
		rw_level = 0;
		/* communicate with ocfs2_dio_end_io */
		ocfs2_iocb_set_rw_locked(iocb, rw_level);
	}

	/*
	 * We're fine letting folks race truncates and extending
	 * writes with read across the cluster, just like they can
	 * locally. Hence no rw_lock during read.
	 * 
	 * Take and drop the meta data lock to update inode fields
	 * like i_size. This allows the checks down below
	 * generic_file_aio_read() a chance of actually working. 
	 */
	ret = ocfs2_inode_lock_atime(inode, filp->f_vfsmnt, &lock_level);
	if (ret < 0) {
		mlog_errno(ret);
		goto bail;
	}
	ocfs2_inode_unlock(inode, lock_level);

	ret = generic_file_aio_read(iocb, iov, nr_segs, iocb->ki_pos);
	if (ret == -EINVAL)
		mlog(0, "generic_file_aio_read returned -EINVAL\n");

	/* buffered aio wouldn't have proper lock coverage today */
	BUG_ON(ret == -EIOCBQUEUED && !(filp->f_flags & O_DIRECT));

	/* see ocfs2_file_aio_write */
	if (ret == -EIOCBQUEUED || !ocfs2_iocb_is_rw_locked(iocb)) {
		rw_level = -1;
		have_alloc_sem = 0;
	}

bail:
	if (have_alloc_sem)
		up_read(&inode->i_alloc_sem);
	if (rw_level != -1) 
		ocfs2_rw_unlock(inode, rw_level);
	mlog_exit(ret);

	return ret;
}