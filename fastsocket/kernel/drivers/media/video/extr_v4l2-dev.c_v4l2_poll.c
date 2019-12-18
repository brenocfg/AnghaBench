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
struct poll_table_struct {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int (* poll ) (struct file*,struct poll_table_struct*) ;} ;

/* Variables and functions */
 unsigned int DEFAULT_POLLMASK ; 
 int POLLERR ; 
 int POLLHUP ; 
 int /*<<< orphan*/  mutex_lock (scalar_t__) ; 
 int /*<<< orphan*/  mutex_unlock (scalar_t__) ; 
 int stub1 (struct file*,struct poll_table_struct*) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct video_device_shadow* video_device_shadow_get (struct video_device*) ; 
 scalar_t__ video_is_registered (struct video_device*) ; 

__attribute__((used)) static unsigned int v4l2_poll(struct file *filp, struct poll_table_struct *poll)
{
	struct video_device *vdev = video_devdata(filp);
	struct video_device_shadow *shvdev = video_device_shadow_get(vdev);
	int ret = POLLERR | POLLHUP;

	if (!vdev->fops->poll)
		return DEFAULT_POLLMASK;
	if (shvdev && shvdev->lock)
		mutex_lock(shvdev->lock);
	if (video_is_registered(vdev))
		ret = vdev->fops->poll(filp, poll);
	if (shvdev && shvdev->lock)
		mutex_unlock(shvdev->lock);
	return ret;
}