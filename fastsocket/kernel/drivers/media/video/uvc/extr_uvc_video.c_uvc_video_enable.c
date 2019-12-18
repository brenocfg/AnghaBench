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
struct uvc_streaming {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  queue; int /*<<< orphan*/  intfnum; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uvc_commit_video (struct uvc_streaming*,int /*<<< orphan*/ *) ; 
 int uvc_init_video (struct uvc_streaming*,int /*<<< orphan*/ ) ; 
 int uvc_queue_enable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uvc_uninit_video (struct uvc_streaming*,int) ; 

int uvc_video_enable(struct uvc_streaming *stream, int enable)
{
	int ret;

	if (!enable) {
		uvc_uninit_video(stream, 1);
		usb_set_interface(stream->dev->udev, stream->intfnum, 0);
		uvc_queue_enable(&stream->queue, 0);
		return 0;
	}

	ret = uvc_queue_enable(&stream->queue, 1);
	if (ret < 0)
		return ret;

	/* Commit the streaming parameters. */
	ret = uvc_commit_video(stream, &stream->ctrl);
	if (ret < 0)
		return ret;

	return uvc_init_video(stream, GFP_KERNEL);
}