#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kiocb {struct file* ki_filp; } ;
struct iovec {int dummy; } ;
struct inode {int dummy; } ;
struct file {TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 int /*<<< orphan*/  ext4_ext_direct_IO (int,struct kiocb*,struct iovec const*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ext4_ind_direct_IO (int,struct kiocb*,struct iovec const*,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t ext4_direct_IO(int rw, struct kiocb *iocb,
			      const struct iovec *iov, loff_t offset,
			      unsigned long nr_segs)
{
	struct file *file = iocb->ki_filp;
	struct inode *inode = file->f_mapping->host;

	if (ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))
		return ext4_ext_direct_IO(rw, iocb, iov, offset, nr_segs);

	return ext4_ind_direct_IO(rw, iocb, iov, offset, nr_segs);
}