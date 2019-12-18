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
struct file {int /*<<< orphan*/  f_mode; TYPE_1__* f_mapping; } ;
struct block_device {struct file* bd_holder; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 struct block_device* I_BDEV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bd_release (struct block_device*) ; 
 int blkdev_put (struct block_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int blkdev_close(struct inode * inode, struct file * filp)
{
	struct block_device *bdev = I_BDEV(filp->f_mapping->host);
	if (bdev->bd_holder == filp)
		bd_release(bdev);
	return blkdev_put(bdev, filp->f_mode);
}