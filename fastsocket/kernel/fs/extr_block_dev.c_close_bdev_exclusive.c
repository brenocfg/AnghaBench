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
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int /*<<< orphan*/  bd_release (struct block_device*) ; 
 int /*<<< orphan*/  blkdev_put (struct block_device*,int /*<<< orphan*/ ) ; 

void close_bdev_exclusive(struct block_device *bdev, fmode_t mode)
{
	bd_release(bdev);
	blkdev_put(bdev, mode);
}