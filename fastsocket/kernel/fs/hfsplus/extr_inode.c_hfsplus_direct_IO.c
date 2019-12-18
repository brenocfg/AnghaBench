#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct kiocb {struct file* ki_filp; } ;
struct iovec {int dummy; } ;
struct inode {TYPE_5__* i_sb; } ;
struct TYPE_9__ {TYPE_3__* dentry; } ;
struct file {TYPE_4__ f_path; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_10__ {int /*<<< orphan*/  s_bdev; } ;
struct TYPE_8__ {TYPE_2__* d_inode; } ;
struct TYPE_7__ {TYPE_1__* i_mapping; } ;
struct TYPE_6__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  blockdev_direct_IO (int,struct kiocb*,struct inode*,int /*<<< orphan*/ ,struct iovec const*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfsplus_get_block ; 

__attribute__((used)) static ssize_t hfsplus_direct_IO(int rw, struct kiocb *iocb,
		const struct iovec *iov, loff_t offset, unsigned long nr_segs)
{
	struct file *file = iocb->ki_filp;
	struct inode *inode = file->f_path.dentry->d_inode->i_mapping->host;

	return blockdev_direct_IO(rw, iocb, inode, inode->i_sb->s_bdev, iov,
				  offset, nr_segs, hfsplus_get_block, NULL);
}