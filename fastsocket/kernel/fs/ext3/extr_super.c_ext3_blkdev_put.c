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

/* Variables and functions */
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  bd_release (struct block_device*) ; 
 int blkdev_put (struct block_device*,int) ; 

__attribute__((used)) static int ext3_blkdev_put(struct block_device *bdev)
{
	bd_release(bdev);
	return blkdev_put(bdev, FMODE_READ|FMODE_WRITE);
}