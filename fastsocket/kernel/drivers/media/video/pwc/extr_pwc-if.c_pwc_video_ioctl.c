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
struct pwc_device {int /*<<< orphan*/  modlock; int /*<<< orphan*/  unplugged; } ;
struct file {struct video_device* private_data; } ;

/* Variables and functions */
 long ENODEV ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwc_video_do_ioctl ; 
 struct pwc_device* video_get_drvdata (struct video_device*) ; 
 long video_usercopy (struct file*,unsigned int,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long pwc_video_ioctl(struct file *file,
			   unsigned int cmd, unsigned long arg)
{
	struct video_device *vdev = file->private_data;
	struct pwc_device *pdev;
	long r = -ENODEV;

	if (!vdev)
		goto out;
	pdev = video_get_drvdata(vdev);

	mutex_lock(&pdev->modlock);
	if (!pdev->unplugged)
		r = video_usercopy(file, cmd, arg, pwc_video_do_ioctl);
	mutex_unlock(&pdev->modlock);
out:
	return r;
}