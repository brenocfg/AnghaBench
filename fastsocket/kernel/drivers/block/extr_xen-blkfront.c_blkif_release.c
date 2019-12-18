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
struct xenbus_device {scalar_t__ state; } ;
struct gendisk {struct blkfront_info* private_data; } ;
struct block_device {scalar_t__ bd_openers; } ;
struct blkfront_info {int /*<<< orphan*/  mutex; struct xenbus_device* xbdev; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 scalar_t__ XenbusStateClosing ; 
 struct block_device* bdget_disk (struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdput (struct block_device*) ; 
 int /*<<< orphan*/  kfree (struct blkfront_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenbus_frontend_closed (struct xenbus_device*) ; 
 int /*<<< orphan*/  xlvbd_release_gendisk (struct blkfront_info*) ; 

__attribute__((used)) static int blkif_release(struct gendisk *disk, fmode_t mode)
{
	struct blkfront_info *info = disk->private_data;
	struct block_device *bdev;
	struct xenbus_device *xbdev;

	bdev = bdget_disk(disk, 0);

	if (bdev->bd_openers)
		goto out;

	/*
	 * Check if we have been instructed to close. We will have
	 * deferred this request, because the bdev was still open.
	 */

	mutex_lock(&info->mutex);
	xbdev = info->xbdev;

	if (xbdev && xbdev->state == XenbusStateClosing) {
		/* pending switch to state closed */
		xlvbd_release_gendisk(info);
		xenbus_frontend_closed(info->xbdev);
 	}

	mutex_unlock(&info->mutex);

	if (!xbdev) {
		/* sudden device removal */
		xlvbd_release_gendisk(info);
		disk->private_data = NULL;
		kfree(info);
	}

out:
	bdput(bdev);
	return 0;
}