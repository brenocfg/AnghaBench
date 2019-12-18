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
struct kiocb {TYPE_3__* ki_filp; } ;
struct iovec {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_sb_info {scalar_t__ s_bitmap_maxbytes; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_aio_mutex; } ;
struct TYPE_6__ {TYPE_1__* dentry; } ;
struct TYPE_7__ {int f_flags; TYPE_2__ f_path; } ;
struct TYPE_5__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFBIG ; 
 TYPE_4__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 struct ext4_sb_info* EXT4_SB (int /*<<< orphan*/ ) ; 
 int O_DIRECT ; 
 int /*<<< orphan*/  ext4_aiodio_wait (struct inode*) ; 
 int /*<<< orphan*/  ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_unaligned_aio (struct inode*,struct iovec const*,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  generic_file_aio_write (struct kiocb*,struct iovec const*,unsigned long,scalar_t__) ; 
 size_t iov_length (struct iovec const*,unsigned long) ; 
 unsigned long iov_shorten (struct iovec*,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  is_sync_kiocb (struct kiocb*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static ssize_t
ext4_file_write(struct kiocb *iocb, const struct iovec *iov,
		unsigned long nr_segs, loff_t pos)
{
	struct inode *inode = iocb->ki_filp->f_path.dentry->d_inode;
	int unaligned_aio = 0;
	ssize_t ret;

	/*
	 * If we have encountered a bitmap-format file, the size limit
	 * is smaller than s_maxbytes, which is for extent-mapped files.
	 */

	if (!(ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))) {
		struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
		size_t length = iov_length(iov, nr_segs);

		if ((pos > sbi->s_bitmap_maxbytes ||
		    (pos == sbi->s_bitmap_maxbytes && length > 0)))
			return -EFBIG;

		if (pos + length > sbi->s_bitmap_maxbytes) {
			nr_segs = iov_shorten((struct iovec *)iov, nr_segs,
					      sbi->s_bitmap_maxbytes - pos);
		}
	} else if (unlikely((iocb->ki_filp->f_flags & O_DIRECT) &&
		            !is_sync_kiocb(iocb)))
		unaligned_aio = ext4_unaligned_aio(inode, iov, nr_segs, pos);

	/* Unaligned direct AIO must be serialized; see comment above */
	if (unaligned_aio) {
		mutex_lock(&EXT4_I(inode)->i_aio_mutex);
		ext4_aiodio_wait(inode);
 	}

	ret = generic_file_aio_write(iocb, iov, nr_segs, pos);

	if (unaligned_aio)
		mutex_unlock(&EXT4_I(inode)->i_aio_mutex);

	return ret;
}