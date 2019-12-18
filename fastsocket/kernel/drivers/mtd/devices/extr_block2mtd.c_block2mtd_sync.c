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
struct mtd_info {struct block2mtd_dev* priv; } ;
struct block2mtd_dev {int /*<<< orphan*/  blkdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  sync_blockdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void block2mtd_sync(struct mtd_info *mtd)
{
	struct block2mtd_dev *dev = mtd->priv;
	sync_blockdev(dev->blkdev);
	return;
}