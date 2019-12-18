#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ext3_sb_info {struct block_device* journal_bdev; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ext3_blkdev_put (struct block_device*) ; 

__attribute__((used)) static int ext3_blkdev_remove(struct ext3_sb_info *sbi)
{
	struct block_device *bdev;
	int ret = -ENODEV;

	bdev = sbi->journal_bdev;
	if (bdev) {
		ret = ext3_blkdev_put(bdev);
		sbi->journal_bdev = NULL;
	}
	return ret;
}