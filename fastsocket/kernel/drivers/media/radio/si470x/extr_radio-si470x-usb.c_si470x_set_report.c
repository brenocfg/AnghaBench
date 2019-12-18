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
struct si470x_device {TYPE_1__* intf; int /*<<< orphan*/  usbdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char,int,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_timeout ; 

__attribute__((used)) static int si470x_set_report(struct si470x_device *radio, void *buf, int size)
{
	unsigned char *report = (unsigned char *) buf;
	int retval;

	retval = usb_control_msg(radio->usbdev,
		usb_sndctrlpipe(radio->usbdev, 0),
		HID_REQ_SET_REPORT,
		USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_DIR_OUT,
		report[0], 2,
		buf, size, usb_timeout);

	if (retval < 0)
		dev_warn(&radio->intf->dev,
			"si470x_set_report: usb_control_msg returned %d\n",
			retval);
	return retval;
}