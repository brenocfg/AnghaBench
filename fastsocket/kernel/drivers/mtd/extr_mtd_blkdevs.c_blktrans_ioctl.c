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
struct mtd_blktrans_ops {int (* flush ) (struct mtd_blktrans_dev*) ;} ;
struct mtd_blktrans_dev {struct mtd_blktrans_ops* tr; } ;
struct block_device {TYPE_1__* bd_disk; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_2__ {struct mtd_blktrans_dev* private_data; } ;

/* Variables and functions */
#define  BLKFLSBUF 128 
 int ENOTTY ; 
 int stub1 (struct mtd_blktrans_dev*) ; 

__attribute__((used)) static int blktrans_ioctl(struct block_device *bdev, fmode_t mode,
			      unsigned int cmd, unsigned long arg)
{
	struct mtd_blktrans_dev *dev = bdev->bd_disk->private_data;
	struct mtd_blktrans_ops *tr = dev->tr;

	switch (cmd) {
	case BLKFLSBUF:
		if (tr->flush)
			return tr->flush(dev);
		/* The core code did the work, we had nothing to do. */
		return 0;
	default:
		return -ENOTTY;
	}
}