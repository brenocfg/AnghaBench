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
typedef  int u8 ;
struct hdpvr_video_info {int dummy; } ;
struct hdpvr_device {int* usbc_buf; int /*<<< orphan*/  status; int /*<<< orphan*/  usbc_mutex; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_DEFAULT_INDEX ; 
 int /*<<< orphan*/  CTRL_LOW_PASS_FILTER_VALUE ; 
 int EACCES ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  STATUS_IDLE ; 
 int boost_audio ; 
 scalar_t__ device_authorization (struct hdpvr_device*) ; 
 struct hdpvr_video_info* get_video_info (struct hdpvr_device*) ; 
 int /*<<< orphan*/  hdpvr_debug ; 
 int /*<<< orphan*/  hdpvr_set_options (struct hdpvr_device*) ; 
 int /*<<< orphan*/  kfree (struct hdpvr_video_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int hdpvr_device_init(struct hdpvr_device *dev)
{
	int ret;
	u8 *buf;
	struct hdpvr_video_info *vidinf;

	if (device_authorization(dev))
		return -EACCES;

	/* default options for init */
	hdpvr_set_options(dev);

	/* set filter options */
	mutex_lock(&dev->usbc_mutex);
	buf = dev->usbc_buf;
	buf[0] = 0x03; buf[1] = 0x03; buf[2] = 0x00; buf[3] = 0x00;
	ret = usb_control_msg(dev->udev,
			      usb_sndctrlpipe(dev->udev, 0),
			      0x01, 0x38,
			      CTRL_LOW_PASS_FILTER_VALUE, CTRL_DEFAULT_INDEX,
			      buf, 4,
			      1000);
	v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
		 "control request returned %d\n", ret);
	mutex_unlock(&dev->usbc_mutex);

	vidinf = get_video_info(dev);
	if (!vidinf)
		v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
			"no valid video signal or device init failed\n");
	else
		kfree(vidinf);

	/* enable fan and bling leds */
	mutex_lock(&dev->usbc_mutex);
	buf[0] = 0x1;
	ret = usb_control_msg(dev->udev,
			      usb_sndctrlpipe(dev->udev, 0),
			      0xd4, 0x38, 0, 0, buf, 1,
			      1000);
	v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
		 "control request returned %d\n", ret);

	/* boost analog audio */
	buf[0] = boost_audio;
	ret = usb_control_msg(dev->udev,
			      usb_sndctrlpipe(dev->udev, 0),
			      0xd5, 0x38, 0, 0, buf, 1,
			      1000);
	v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
		 "control request returned %d\n", ret);
	mutex_unlock(&dev->usbc_mutex);

	dev->status = STATUS_IDLE;
	return 0;
}