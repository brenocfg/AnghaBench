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
struct block_device {int /*<<< orphan*/  bd_mutex; scalar_t__ bd_openers; } ;
struct blkfront_info {int /*<<< orphan*/  mutex; scalar_t__ gd; struct xenbus_device* xbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 scalar_t__ XenbusStateClosing ; 
 struct block_device* bdget_disk (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdput (struct block_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenbus_dev_error (struct xenbus_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xenbus_frontend_closed (struct xenbus_device*) ; 
 int /*<<< orphan*/  xlvbd_release_gendisk (struct blkfront_info*) ; 

__attribute__((used)) static void
blkfront_closing(struct blkfront_info *info)
{
	struct xenbus_device *xbdev = info->xbdev;
	struct block_device *bdev = NULL;

	mutex_lock(&info->mutex);

	if (xbdev->state == XenbusStateClosing) {
		mutex_unlock(&info->mutex);
		return;
	}

	if (info->gd)
		bdev = bdget_disk(info->gd, 0);

	mutex_unlock(&info->mutex);

	if (!bdev) {
		xenbus_frontend_closed(xbdev);
		return;
	}

	mutex_lock(&bdev->bd_mutex);

	if (bdev->bd_openers) {
		xenbus_dev_error(xbdev, -EBUSY,
				 "Device in use; refusing to close");
	} else {
		xlvbd_release_gendisk(info);
		xenbus_frontend_closed(xbdev);
	}

	mutex_unlock(&bdev->bd_mutex);
	bdput(bdev);
}