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
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __blkdev_issue_flush (struct block_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int blkdev_issue_flush(struct block_device *bdev, sector_t *error_sector)
{
	return __blkdev_issue_flush(bdev, GFP_KERNEL, error_sector);
}