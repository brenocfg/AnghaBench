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
typedef  enum usb_device_speed { ____Placeholder_usb_device_speed } usb_device_speed ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int EINVAL ; 
#define  USB_SPEED_FULL 131 
#define  USB_SPEED_HIGH 130 
#define  USB_SPEED_LOW 129 
#define  USB_SPEED_WIRELESS 128 
 scalar_t__ VHCI_NPORTS ; 
 int /*<<< orphan*/  usbip_uerr (char*,int) ; 

__attribute__((used)) static int valid_args(__u32 rhport, enum usb_device_speed speed)
{
	/* check rhport */
	if ((rhport < 0) || (rhport >= VHCI_NPORTS)) {
		usbip_uerr("port %u\n", rhport);
		return -EINVAL;
	}

	/* check speed */
	switch (speed) {
	case USB_SPEED_LOW:
	case USB_SPEED_FULL:
	case USB_SPEED_HIGH:
	case USB_SPEED_WIRELESS:
		break;
	default:
		usbip_uerr("speed %d\n", speed);
		return -EINVAL;
	}

	return 0;
}