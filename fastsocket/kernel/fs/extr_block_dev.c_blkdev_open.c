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
struct inode {int dummy; } ;
struct file {int f_flags; int f_mode; int /*<<< orphan*/  f_mapping; } ;
struct block_device {TYPE_1__* bd_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FMODE_EXCL ; 
 int FMODE_NDELAY ; 
 int FMODE_WRITE_IOCTL ; 
 int O_ACCMODE ; 
 int O_EXCL ; 
 int O_LARGEFILE ; 
 int O_NDELAY ; 
 struct block_device* bd_acquire (struct inode*) ; 
 int bd_claim (struct block_device*,struct file*) ; 
 int blkdev_get (struct block_device*,int) ; 
 int /*<<< orphan*/  blkdev_put (struct block_device*,int) ; 

__attribute__((used)) static int blkdev_open(struct inode * inode, struct file * filp)
{
	struct block_device *bdev;
	int res;

	/*
	 * Preserve backwards compatibility and allow large file access
	 * even if userspace doesn't ask for it explicitly. Some mkfs
	 * binary needs it. We might want to drop this workaround
	 * during an unstable branch.
	 */
	filp->f_flags |= O_LARGEFILE;

	if (filp->f_flags & O_NDELAY)
		filp->f_mode |= FMODE_NDELAY;
	if (filp->f_flags & O_EXCL)
		filp->f_mode |= FMODE_EXCL;
	if ((filp->f_flags & O_ACCMODE) == 3)
		filp->f_mode |= FMODE_WRITE_IOCTL;

	bdev = bd_acquire(inode);
	if (bdev == NULL)
		return -ENOMEM;

	filp->f_mapping = bdev->bd_inode->i_mapping;

	res = blkdev_get(bdev, filp->f_mode);
	if (res)
		return res;

	if (filp->f_mode & FMODE_EXCL) {
		res = bd_claim(bdev, filp);
		if (res)
			goto out_blkdev_put;
	}

	return 0;

 out_blkdev_put:
	blkdev_put(bdev, filp->f_mode);
	return res;
}