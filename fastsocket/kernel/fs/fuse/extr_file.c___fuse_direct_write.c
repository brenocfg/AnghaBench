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
struct iovec {int dummy; } ;
struct inode {int dummy; } ;
struct fuse_io_priv {struct file* file; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 scalar_t__ fuse_direct_io (struct fuse_io_priv*,struct iovec const*,unsigned long,size_t,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fuse_invalidate_attr (struct inode*) ; 
 scalar_t__ generic_write_checks (struct file*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 
 size_t iov_length (struct iovec const*,unsigned long) ; 

__attribute__((used)) static ssize_t __fuse_direct_write(struct fuse_io_priv *io,
				   const struct iovec *iov,
				   unsigned long nr_segs, loff_t *ppos)
{
	struct file *file = io->file;
	struct inode *inode = file->f_path.dentry->d_inode;
	size_t count = iov_length(iov, nr_segs);
	ssize_t res;

	res = generic_write_checks(file, ppos, &count, 0);
	if (!res)
		res = fuse_direct_io(io, iov, nr_segs, count, ppos, 1);

	fuse_invalidate_attr(inode);

	return res;
}