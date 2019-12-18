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
struct kiocb {struct file* ki_filp; } ;
struct iovec {int dummy; } ;
struct inode {scalar_t__ i_size; scalar_t__ i_nlink; TYPE_2__* i_sb; } ;
struct file {TYPE_1__* f_mapping; } ;
struct ext4_inode_info {scalar_t__ i_disksize; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_4__ {int /*<<< orphan*/  s_bdev; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int ENOSPC ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int WRITE ; 
 int blockdev_direct_IO (int,struct kiocb*,struct inode*,int /*<<< orphan*/ ,struct iovec const*,scalar_t__,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_get_block ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int) ; 
 int ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 int ext4_orphan_add (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_orphan_del (int /*<<< orphan*/ *,struct inode*) ; 
 scalar_t__ ext4_should_retry_alloc (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 size_t iov_length (struct iovec const*,unsigned long) ; 

__attribute__((used)) static ssize_t ext4_ind_direct_IO(int rw, struct kiocb *iocb,
			      const struct iovec *iov, loff_t offset,
			      unsigned long nr_segs)
{
	struct file *file = iocb->ki_filp;
	struct inode *inode = file->f_mapping->host;
	struct ext4_inode_info *ei = EXT4_I(inode);
	handle_t *handle;
	ssize_t ret;
	int orphan = 0;
	size_t count = iov_length(iov, nr_segs);
	int retries = 0;

	if (rw == WRITE) {
		loff_t final_size = offset + count;

		if (final_size > inode->i_size) {
			/* Credits for sb + inode write */
			handle = ext4_journal_start(inode, 2);
			if (IS_ERR(handle)) {
				ret = PTR_ERR(handle);
				goto out;
			}
			ret = ext4_orphan_add(handle, inode);
			if (ret) {
				ext4_journal_stop(handle);
				goto out;
			}
			orphan = 1;
			ei->i_disksize = inode->i_size;
			ext4_journal_stop(handle);
		}
	}

retry:
	ret = blockdev_direct_IO(rw, iocb, inode, inode->i_sb->s_bdev, iov,
				 offset, nr_segs,
				 ext4_get_block, NULL);
	if (ret == -ENOSPC && ext4_should_retry_alloc(inode->i_sb, &retries))
		goto retry;

	if (orphan) {
		int err;

		/* Credits for sb + inode write */
		handle = ext4_journal_start(inode, 2);
		if (IS_ERR(handle)) {
			/* This is really bad luck. We've written the data
			 * but cannot extend i_size. Bail out and pretend
			 * the write failed... */
			ret = PTR_ERR(handle);
			if (inode->i_nlink)
				ext4_orphan_del(NULL, inode);

			goto out;
		}
		if (inode->i_nlink)
			ext4_orphan_del(handle, inode);
		if (ret > 0) {
			loff_t end = offset + ret;
			if (end > inode->i_size) {
				ei->i_disksize = end;
				i_size_write(inode, end);
				/*
				 * We're going to return a positive `ret'
				 * here due to non-zero-length I/O, so there's
				 * no way of reporting error returns from
				 * ext4_mark_inode_dirty() to userspace.  So
				 * ignore it.
				 */
				ext4_mark_inode_dirty(handle, inode);
			}
		}
		err = ext4_journal_stop(handle);
		if (ret == 0)
			ret = err;
	}
out:
	return ret;
}