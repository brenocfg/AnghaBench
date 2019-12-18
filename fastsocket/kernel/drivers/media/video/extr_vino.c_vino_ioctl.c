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
struct vino_channel_settings {int /*<<< orphan*/  mutex; } ;
struct file {int dummy; } ;

/* Variables and functions */
 long EINTR ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vino_channel_settings* video_drvdata (struct file*) ; 
 long video_ioctl2 (struct file*,unsigned int,unsigned long) ; 

__attribute__((used)) static long vino_ioctl(struct file *file,
		      unsigned int cmd, unsigned long arg)
{
	struct vino_channel_settings *vcs = video_drvdata(file);
	long ret;

	if (mutex_lock_interruptible(&vcs->mutex))
		return -EINTR;

	ret = video_ioctl2(file, cmd, arg);

	mutex_unlock(&vcs->mutex);

	return ret;
}