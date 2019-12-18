#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  bLength; } ;
struct TYPE_3__ {TYPE_2__ descr; } ;
struct wusbhc {int gtk_index; TYPE_1__ gtk; } ;
struct wusb_dev {struct usb_device* usb_dev; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int USB_DIR_OUT ; 
 int USB_DT_KEY ; 
 int USB_RECIP_DEVICE ; 
 int /*<<< orphan*/  USB_REQ_SET_DESCRIPTOR ; 
 int USB_TYPE_STANDARD ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wusb_dev_set_gtk(struct wusbhc *wusbhc, struct wusb_dev *wusb_dev)
{
	struct usb_device *usb_dev = wusb_dev->usb_dev;

	return usb_control_msg(
		usb_dev, usb_sndctrlpipe(usb_dev, 0),
		USB_REQ_SET_DESCRIPTOR,
		USB_DIR_OUT | USB_TYPE_STANDARD | USB_RECIP_DEVICE,
		USB_DT_KEY << 8 | wusbhc->gtk_index, 0,
		&wusbhc->gtk.descr, wusbhc->gtk.descr.bLength,
		1000);
}