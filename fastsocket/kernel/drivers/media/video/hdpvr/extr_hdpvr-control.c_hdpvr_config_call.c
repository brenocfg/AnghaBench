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
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u8 ;
struct hdpvr_device {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  usbc_mutex; int /*<<< orphan*/ * usbc_buf; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_DEFAULT_INDEX ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  hdpvr_debug ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 

int hdpvr_config_call(struct hdpvr_device *dev, uint value, u8 valbuf)
{
	int ret;
	char request_type = 0x38, snd_request = 0x01;

	mutex_lock(&dev->usbc_mutex);
	dev->usbc_buf[0] = valbuf;
	ret = usb_control_msg(dev->udev,
			      usb_sndctrlpipe(dev->udev, 0),
			      snd_request, 0x00 | request_type,
			      value, CTRL_DEFAULT_INDEX,
			      dev->usbc_buf, 1, 10000);

	mutex_unlock(&dev->usbc_mutex);
	v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
		 "config call request for value 0x%x returned %d\n", value,
		 ret);

	return ret < 0 ? ret : 0;
}