#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cx25821_dev {TYPE_1__* ioctl_dev; } ;
struct TYPE_3__ {int minor; } ;

/* Variables and functions */
 int /*<<< orphan*/  video_device_release (TYPE_1__*) ; 
 int /*<<< orphan*/  video_unregister_device (TYPE_1__*) ; 

void cx25821_videoioctl_unregister(struct cx25821_dev *dev)
{
	if (dev->ioctl_dev) {
		if (dev->ioctl_dev->minor != -1)
			video_unregister_device(dev->ioctl_dev);
		else
			video_device_release(dev->ioctl_dev);

		dev->ioctl_dev = NULL;
	}
}