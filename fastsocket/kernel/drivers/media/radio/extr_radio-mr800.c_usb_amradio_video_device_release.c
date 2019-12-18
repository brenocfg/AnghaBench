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
struct amradio_device {struct amradio_device* buffer; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct amradio_device*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_device_release (struct video_device*) ; 
 struct amradio_device* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static void usb_amradio_video_device_release(struct video_device *videodev)
{
	struct amradio_device *radio = video_get_drvdata(videodev);

	/* we call v4l to free radio->videodev */
	video_device_release(videodev);

	v4l2_device_unregister(&radio->v4l2_dev);

	/* free rest memory */
	kfree(radio->buffer);
	kfree(radio);
}