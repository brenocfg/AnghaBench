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
struct usbtest_dev {int* buf; struct usb_interface* intf; } ;
struct usb_interface {TYPE_2__* altsetting; } ;
struct usb_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  USB_CTRL_GET_TIMEOUT ; 
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int /*<<< orphan*/  USB_REQ_GET_INTERFACE ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_altsetting (struct usbtest_dev *dev)
{
	struct usb_interface	*iface = dev->intf;
	struct usb_device	*udev = interface_to_usbdev (iface);
	int			retval;

	retval = usb_control_msg (udev, usb_rcvctrlpipe (udev, 0),
			USB_REQ_GET_INTERFACE, USB_DIR_IN|USB_RECIP_INTERFACE,
			0, iface->altsetting [0].desc.bInterfaceNumber,
			dev->buf, 1, USB_CTRL_GET_TIMEOUT);
	switch (retval) {
	case 1:
		return dev->buf [0];
	case 0:
		retval = -ERANGE;
		// FALLTHROUGH
	default:
		return retval;
	}
}