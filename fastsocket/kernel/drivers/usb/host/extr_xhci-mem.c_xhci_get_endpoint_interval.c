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
struct usb_host_endpoint {int /*<<< orphan*/  desc; } ;
struct usb_device {int speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 unsigned int EP_INTERVAL (unsigned int) ; 
#define  USB_SPEED_FULL 131 
#define  USB_SPEED_HIGH 130 
#define  USB_SPEED_LOW 129 
#define  USB_SPEED_SUPER 128 
 int /*<<< orphan*/  usb_endpoint_xfer_bulk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_endpoint_xfer_control (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_endpoint_xfer_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_endpoint_xfer_isoc (int /*<<< orphan*/ *) ; 
 unsigned int xhci_parse_exponent_interval (struct usb_device*,struct usb_host_endpoint*) ; 
 unsigned int xhci_parse_frame_interval (struct usb_device*,struct usb_host_endpoint*) ; 
 unsigned int xhci_parse_microframe_interval (struct usb_device*,struct usb_host_endpoint*) ; 

__attribute__((used)) static unsigned int xhci_get_endpoint_interval(struct usb_device *udev,
		struct usb_host_endpoint *ep)
{
	unsigned int interval = 0;

	switch (udev->speed) {
	case USB_SPEED_HIGH:
		/* Max NAK rate */
		if (usb_endpoint_xfer_control(&ep->desc) ||
		    usb_endpoint_xfer_bulk(&ep->desc)) {
			interval = xhci_parse_microframe_interval(udev, ep);
			break;
		}
		/* Fall through - SS and HS isoc/int have same decoding */

	case USB_SPEED_SUPER:
		if (usb_endpoint_xfer_int(&ep->desc) ||
		    usb_endpoint_xfer_isoc(&ep->desc)) {
			interval = xhci_parse_exponent_interval(udev, ep);
		}
		break;

	case USB_SPEED_FULL:
		if (usb_endpoint_xfer_isoc(&ep->desc)) {
			interval = xhci_parse_exponent_interval(udev, ep);
			break;
		}
		/*
		 * Fall through for interrupt endpoint interval decoding
		 * since it uses the same rules as low speed interrupt
		 * endpoints.
		 */

	case USB_SPEED_LOW:
		if (usb_endpoint_xfer_int(&ep->desc) ||
		    usb_endpoint_xfer_isoc(&ep->desc)) {

			interval = xhci_parse_frame_interval(udev, ep);
		}
		break;

	default:
		BUG();
	}
	return EP_INTERVAL(interval);
}