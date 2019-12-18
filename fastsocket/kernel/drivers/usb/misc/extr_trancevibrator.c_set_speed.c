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
struct usb_interface {int dummy; } ;
struct trancevibrator {int speed; TYPE_1__* udev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_CTRL_GET_TIMEOUT ; 
 int USB_DIR_IN ; 
 int USB_RECIP_OTHER ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 int usb_control_msg (TYPE_1__*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct trancevibrator* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t set_speed(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	struct usb_interface *intf = to_usb_interface(dev);
	struct trancevibrator *tv = usb_get_intfdata(intf);
	int temp, retval, old;

	temp = simple_strtoul(buf, NULL, 10);
	if (temp > 255)
		temp = 255;
	else if (temp < 0)
		temp = 0;
	old = tv->speed;
	tv->speed = temp;

	dev_dbg(&tv->udev->dev, "speed = %d\n", tv->speed);

	/* Set speed */
	retval = usb_control_msg(tv->udev, usb_sndctrlpipe(tv->udev, 0),
				 0x01, /* vendor request: set speed */
				 USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_OTHER,
				 tv->speed, /* speed value */
				 0, NULL, 0, USB_CTRL_GET_TIMEOUT);
	if (retval) {
		tv->speed = old;
		dev_dbg(&tv->udev->dev, "retval = %d\n", retval);
		return retval;
	}
	return count;
}