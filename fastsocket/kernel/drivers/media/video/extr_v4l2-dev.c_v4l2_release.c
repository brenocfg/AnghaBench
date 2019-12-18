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
struct video_device_shadow {scalar_t__ lock; } ;
struct video_device {TYPE_1__* fops; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* release ) (struct file*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (scalar_t__) ; 
 int /*<<< orphan*/  mutex_unlock (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct file*) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct video_device_shadow* video_device_shadow_get (struct video_device*) ; 
 int /*<<< orphan*/  video_put (struct video_device*) ; 

__attribute__((used)) static int v4l2_release(struct inode *inode, struct file *filp)
{
	struct video_device *vdev = video_devdata(filp);
	struct video_device_shadow *shvdev = video_device_shadow_get(vdev);
	int ret = 0;

	if (vdev->fops->release) {
		if (shvdev && shvdev->lock)
			mutex_lock(shvdev->lock);
		vdev->fops->release(filp);
		if (shvdev && shvdev->lock)
			mutex_unlock(shvdev->lock);
	}

	/* decrease the refcount unconditionally since the release()
	   return value is ignored. */
	video_put(vdev);
	return ret;
}