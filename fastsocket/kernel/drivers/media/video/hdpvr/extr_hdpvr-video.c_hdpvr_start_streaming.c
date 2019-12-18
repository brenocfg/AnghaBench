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
struct hdpvr_video_info {int /*<<< orphan*/  fps; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_2__ {int video_input; } ;
struct hdpvr_device {scalar_t__ status; TYPE_1__ options; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  worker; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_START_STREAMING_VALUE ; 
 int EAGAIN ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_BUFFER ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ STATUS_IDLE ; 
 scalar_t__ STATUS_STREAMING ; 
 struct hdpvr_video_info* get_video_info (struct hdpvr_device*) ; 
 int /*<<< orphan*/  hdpvr_config_call (struct hdpvr_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hdpvr_debug ; 
 int /*<<< orphan*/  hdpvr_transmit_buffers ; 
 int /*<<< orphan*/  kfree (struct hdpvr_video_info*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int hdpvr_start_streaming(struct hdpvr_device *dev)
{
	int ret;
	struct hdpvr_video_info *vidinf;

	if (dev->status == STATUS_STREAMING)
		return 0;
	else if (dev->status != STATUS_IDLE)
		return -EAGAIN;

	vidinf = get_video_info(dev);

	if (vidinf) {
		v4l2_dbg(MSG_BUFFER, hdpvr_debug, &dev->v4l2_dev,
			 "video signal: %dx%d@%dhz\n", vidinf->width,
			 vidinf->height, vidinf->fps);
		kfree(vidinf);

		/* start streaming 2 request */
		ret = usb_control_msg(dev->udev,
				      usb_sndctrlpipe(dev->udev, 0),
				      0xb8, 0x38, 0x1, 0, NULL, 0, 8000);
		v4l2_dbg(MSG_BUFFER, hdpvr_debug, &dev->v4l2_dev,
			 "encoder start control request returned %d\n", ret);

		hdpvr_config_call(dev, CTRL_START_STREAMING_VALUE, 0x00);

		INIT_WORK(&dev->worker, hdpvr_transmit_buffers);
		queue_work(dev->workqueue, &dev->worker);

		v4l2_dbg(MSG_BUFFER, hdpvr_debug, &dev->v4l2_dev,
			 "streaming started\n");
		dev->status = STATUS_STREAMING;

		return 0;
	}
	msleep(250);
	v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
		 "no video signal at input %d\n", dev->options.video_input);
	return -EAGAIN;
}