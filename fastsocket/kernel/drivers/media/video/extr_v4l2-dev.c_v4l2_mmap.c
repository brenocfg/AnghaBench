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
struct vm_area_struct {int dummy; } ;
struct video_device_shadow {scalar_t__ lock; } ;
struct video_device {TYPE_1__* fops; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int (* mmap ) (struct file*,struct vm_area_struct*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int ERESTARTSYS ; 
 scalar_t__ mutex_lock_interruptible (scalar_t__) ; 
 int /*<<< orphan*/  mutex_unlock (scalar_t__) ; 
 int stub1 (struct file*,struct vm_area_struct*) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct video_device_shadow* video_device_shadow_get (struct video_device*) ; 
 scalar_t__ video_is_registered (struct video_device*) ; 

__attribute__((used)) static int v4l2_mmap(struct file *filp, struct vm_area_struct *vm)
{
	struct video_device *vdev = video_devdata(filp);
	struct video_device_shadow *shvdev = video_device_shadow_get(vdev);
	int ret = -ENODEV;

	if (!vdev->fops->mmap)
		return ret;
	if (shvdev && shvdev->lock && mutex_lock_interruptible(shvdev->lock))
		return -ERESTARTSYS;
	if (video_is_registered(vdev))
		ret = vdev->fops->mmap(filp, vm);
	if (shvdev && shvdev->lock)
		mutex_unlock(shvdev->lock);
	return ret;
}