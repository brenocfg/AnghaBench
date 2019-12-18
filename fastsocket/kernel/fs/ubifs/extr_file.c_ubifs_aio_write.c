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
struct ubifs_info {int dummy; } ;
struct kiocb {TYPE_2__* ki_filp; } ;
struct iovec {int dummy; } ;
struct inode {TYPE_3__* i_sb; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_6__ {struct ubifs_info* s_fs_info; } ;
struct TYPE_5__ {int f_flags; TYPE_1__* f_mapping; } ;
struct TYPE_4__ {struct inode* host; } ;

/* Variables and functions */
 scalar_t__ IS_SYNC (struct inode*) ; 
 int O_SYNC ; 
 int generic_file_aio_write (struct kiocb*,struct iovec const*,unsigned long,int /*<<< orphan*/ ) ; 
 int ubifs_sync_wbufs_by_inode (struct ubifs_info*,struct inode*) ; 
 int update_mctime (struct ubifs_info*,struct inode*) ; 

__attribute__((used)) static ssize_t ubifs_aio_write(struct kiocb *iocb, const struct iovec *iov,
			       unsigned long nr_segs, loff_t pos)
{
	int err;
	ssize_t ret;
	struct inode *inode = iocb->ki_filp->f_mapping->host;
	struct ubifs_info *c = inode->i_sb->s_fs_info;

	err = update_mctime(c, inode);
	if (err)
		return err;

	ret = generic_file_aio_write(iocb, iov, nr_segs, pos);
	if (ret < 0)
		return ret;

	if (ret > 0 && (IS_SYNC(inode) || iocb->ki_filp->f_flags & O_SYNC)) {
		err = ubifs_sync_wbufs_by_inode(c, inode);
		if (err)
			return err;
	}

	return ret;
}