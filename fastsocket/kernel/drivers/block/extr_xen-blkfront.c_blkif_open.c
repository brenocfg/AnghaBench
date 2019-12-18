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
struct gendisk {struct blkfront_info* private_data; } ;
struct block_device {struct gendisk* bd_disk; } ;
struct blkfront_info {int /*<<< orphan*/  mutex; int /*<<< orphan*/  gd; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int blkif_open(struct block_device *bdev, fmode_t mode)
{
	struct gendisk *disk = bdev->bd_disk;
	struct blkfront_info *info;
	int err = 0;

	info = disk->private_data;
	if (!info) {
		/* xbdev gone */
		err = -ERESTARTSYS;
		goto out;
	}

	mutex_lock(&info->mutex);

	if (!info->gd)
		/* xbdev is closed */
		err = -ERESTARTSYS;

	mutex_unlock(&info->mutex);

out:
	return err;
}