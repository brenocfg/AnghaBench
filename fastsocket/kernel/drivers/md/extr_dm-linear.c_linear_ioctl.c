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
struct linear_c {scalar_t__ start; struct dm_dev* dev; } ;
struct dm_target {scalar_t__ len; scalar_t__ private; } ;
struct dm_dev {int /*<<< orphan*/  mode; TYPE_1__* bdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  bd_inode; } ;

/* Variables and functions */
 int SECTOR_SHIFT ; 
 int __blkdev_driver_ioctl (TYPE_1__*,int /*<<< orphan*/ ,unsigned int,unsigned long) ; 
 scalar_t__ i_size_read (int /*<<< orphan*/ ) ; 
 int scsi_verify_blk_ioctl (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int linear_ioctl(struct dm_target *ti, unsigned int cmd,
			unsigned long arg)
{
	struct linear_c *lc = (struct linear_c *) ti->private;
	struct dm_dev *dev = lc->dev;
	int r = 0;

	/*
	 * Only pass ioctls through if the device sizes match exactly.
	 */
	if (lc->start ||
	    ti->len != i_size_read(dev->bdev->bd_inode) >> SECTOR_SHIFT)
		r = scsi_verify_blk_ioctl(NULL, cmd);

	return r ? : __blkdev_driver_ioctl(dev->bdev, dev->mode, cmd, arg);
}