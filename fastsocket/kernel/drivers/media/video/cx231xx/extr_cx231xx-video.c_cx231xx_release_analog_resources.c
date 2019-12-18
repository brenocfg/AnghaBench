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
struct cx231xx {scalar_t__ model; int /*<<< orphan*/ * vdev; int /*<<< orphan*/ * vbi_dev; int /*<<< orphan*/ * radio_dev; } ;

/* Variables and functions */
 scalar_t__ CX231XX_BOARD_CNXT_VIDEO_GRABBER ; 
 int /*<<< orphan*/  cx231xx_417_unregister (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_device_node_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_device_release (int /*<<< orphan*/ *) ; 
 scalar_t__ video_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

void cx231xx_release_analog_resources(struct cx231xx *dev)
{

	/*FIXME: I2C IR should be disconnected */

	if (dev->radio_dev) {
		if (video_is_registered(dev->radio_dev))
			video_unregister_device(dev->radio_dev);
		else
			video_device_release(dev->radio_dev);
		dev->radio_dev = NULL;
	}
	if (dev->vbi_dev) {
		cx231xx_info("V4L2 device %s deregistered\n",
			     video_device_node_name(dev->vbi_dev));
		if (video_is_registered(dev->vbi_dev))
			video_unregister_device(dev->vbi_dev);
		else
			video_device_release(dev->vbi_dev);
		dev->vbi_dev = NULL;
	}
	if (dev->vdev) {
		cx231xx_info("V4L2 device %s deregistered\n",
			     video_device_node_name(dev->vdev));

		if (dev->model == CX231XX_BOARD_CNXT_VIDEO_GRABBER)
			cx231xx_417_unregister(dev);

		if (video_is_registered(dev->vdev))
			video_unregister_device(dev->vdev);
		else
			video_device_release(dev->vdev);
		dev->vdev = NULL;
	}
}