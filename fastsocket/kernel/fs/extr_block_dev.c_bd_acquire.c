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
struct inode {int /*<<< orphan*/  i_devices; int /*<<< orphan*/  i_mapping; struct block_device* i_bdev; int /*<<< orphan*/  i_rdev; } ;
struct block_device {int /*<<< orphan*/  bd_inodes; TYPE_1__* bd_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bdev_lock ; 
 struct block_device* bdget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct block_device *bd_acquire(struct inode *inode)
{
	struct block_device *bdev;

	spin_lock(&bdev_lock);
	bdev = inode->i_bdev;
	if (bdev) {
		atomic_inc(&bdev->bd_inode->i_count);
		spin_unlock(&bdev_lock);
		return bdev;
	}
	spin_unlock(&bdev_lock);

	bdev = bdget(inode->i_rdev);
	if (bdev) {
		spin_lock(&bdev_lock);
		if (!inode->i_bdev) {
			/*
			 * We take an additional bd_inode->i_count for inode,
			 * and it's released in clear_inode() of inode.
			 * So, we can access it via ->i_mapping always
			 * without igrab().
			 */
			atomic_inc(&bdev->bd_inode->i_count);
			inode->i_bdev = bdev;
			inode->i_mapping = bdev->bd_inode->i_mapping;
			list_add(&inode->i_devices, &bdev->bd_inodes);
		}
		spin_unlock(&bdev_lock);
	}
	return bdev;
}