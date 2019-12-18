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
struct inode {struct block_device* i_bdev; int /*<<< orphan*/  i_sb; } ;
struct block_device {int /*<<< orphan*/  bd_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bd_forget (struct inode*) ; 
 int /*<<< orphan*/  bdev_lock ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_is_blkdev_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void bd_forget(struct inode *inode)
{
	struct block_device *bdev = NULL;

	spin_lock(&bdev_lock);
	if (inode->i_bdev) {
		if (!sb_is_blkdev_sb(inode->i_sb))
			bdev = inode->i_bdev;
		__bd_forget(inode);
	}
	spin_unlock(&bdev_lock);

	if (bdev)
		iput(bdev->bd_inode);
}