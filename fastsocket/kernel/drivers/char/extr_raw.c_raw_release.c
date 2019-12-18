#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * backing_dev_info; } ;
struct inode {TYPE_1__* i_mapping; TYPE_1__ i_data; } ;
struct file {int /*<<< orphan*/  f_mode; } ;
struct block_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ inuse; struct block_device* binding; } ;

/* Variables and functions */
 int /*<<< orphan*/  bd_release (struct block_device*) ; 
 int /*<<< orphan*/  blkdev_put (struct block_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_backing_dev_info ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* raw_devices ; 
 int /*<<< orphan*/  raw_mutex ; 

__attribute__((used)) static int raw_release(struct inode *inode, struct file *filp)
{
	const int minor= iminor(inode);
	struct block_device *bdev;

	mutex_lock(&raw_mutex);
	bdev = raw_devices[minor].binding;
	if (--raw_devices[minor].inuse == 0) {
		/* Here  inode->i_mapping == bdev->bd_inode->i_mapping  */
		inode->i_mapping = &inode->i_data;
		inode->i_mapping->backing_dev_info = &default_backing_dev_info;
	}
	mutex_unlock(&raw_mutex);

	bd_release(bdev);
	blkdev_put(bdev, filp->f_mode);
	return 0;
}