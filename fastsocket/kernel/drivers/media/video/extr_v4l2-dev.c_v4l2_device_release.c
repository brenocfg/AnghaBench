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
struct video_device {size_t minor; int /*<<< orphan*/  (* release ) (struct video_device*) ;int /*<<< orphan*/ * cdev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devnode_clear (struct video_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct video_device*) ; 
 struct video_device* to_video_device (struct device*) ; 
 struct video_device** video_device ; 
 int /*<<< orphan*/  videodev_lock ; 

__attribute__((used)) static void v4l2_device_release(struct device *cd)
{
	struct video_device *vdev = to_video_device(cd);

	mutex_lock(&videodev_lock);
	if (video_device[vdev->minor] != vdev) {
		mutex_unlock(&videodev_lock);
		/* should not happen */
		WARN_ON(1);
		return;
	}

	/* Free up this device for reuse */
	video_device[vdev->minor] = NULL;

	/* Delete the cdev on this minor as well */
	cdev_del(vdev->cdev);
	/* Just in case some driver tries to access this from
	   the release() callback. */
	vdev->cdev = NULL;

	/* Mark device node number as free */
	devnode_clear(vdev);

	mutex_unlock(&videodev_lock);

	/* Release video_device and perform other
	   cleanups as needed. */
	vdev->release(vdev);
}