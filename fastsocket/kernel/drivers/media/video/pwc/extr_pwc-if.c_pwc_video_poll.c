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
struct pwc_device {int /*<<< orphan*/ * full_frames; scalar_t__ error_status; int /*<<< orphan*/  frameq; int /*<<< orphan*/  modlock; } ;
struct file {struct video_device* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int EFAULT ; 
 unsigned int POLLERR ; 
 unsigned int POLLIN ; 
 unsigned int POLLRDNORM ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pwc_isoc_init (struct pwc_device*) ; 
 struct pwc_device* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static unsigned int pwc_video_poll(struct file *file, poll_table *wait)
{
	struct video_device *vdev = file->private_data;
	struct pwc_device *pdev;
	int ret;

	if (vdev == NULL)
		return -EFAULT;
	pdev = video_get_drvdata(vdev);
	if (pdev == NULL)
		return -EFAULT;

	/* Start the stream (if not already started) */
	mutex_lock(&pdev->modlock);
	ret = pwc_isoc_init(pdev);
	mutex_unlock(&pdev->modlock);
	if (ret)
		return ret;

	poll_wait(file, &pdev->frameq, wait);
	if (pdev->error_status)
		return POLLERR;
	if (pdev->full_frames != NULL) /* we have frames waiting */
		return (POLLIN | POLLRDNORM);

	return 0;
}