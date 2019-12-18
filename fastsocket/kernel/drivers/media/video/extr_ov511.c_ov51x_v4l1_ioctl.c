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
struct video_device {int dummy; } ;
struct usb_ov511 {int /*<<< orphan*/  lock; } ;
struct file {struct video_device* private_data; } ;

/* Variables and functions */
 long EINTR ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ov51x_v4l1_ioctl_internal ; 
 struct usb_ov511* video_get_drvdata (struct video_device*) ; 
 int video_usercopy (struct file*,unsigned int,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long
ov51x_v4l1_ioctl(struct file *file,
		 unsigned int cmd, unsigned long arg)
{
	struct video_device *vdev = file->private_data;
	struct usb_ov511 *ov = video_get_drvdata(vdev);
	int rc;

	if (mutex_lock_interruptible(&ov->lock))
		return -EINTR;

	rc = video_usercopy(file, cmd, arg, ov51x_v4l1_ioctl_internal);

	mutex_unlock(&ov->lock);
	return rc;
}