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
typedef  int u32 ;
struct xhci_hcd {int* port_array; int /*<<< orphan*/  hcs_params1; } ;
struct usb_device {unsigned int portnum; scalar_t__ speed; struct usb_device* parent; } ;

/* Variables and functions */
 int DUPLICATE_ENTRY ; 
 int HCS_MAX_PORTS (int /*<<< orphan*/ ) ; 
 scalar_t__ USB_SPEED_SUPER ; 

__attribute__((used)) static u32 xhci_find_real_port_number(struct xhci_hcd *xhci,
		struct usb_device *udev)
{
	struct usb_device *top_dev;
	unsigned int num_similar_speed_ports;
	unsigned int faked_port_num;
	int i;

	for (top_dev = udev; top_dev->parent && top_dev->parent->parent;
			top_dev = top_dev->parent)
		/* Found device below root hub */;
	faked_port_num = top_dev->portnum;
	for (i = 0, num_similar_speed_ports = 0;
			i < HCS_MAX_PORTS(xhci->hcs_params1); i++) {
		u8 port_speed = xhci->port_array[i];

		/*
		 * Skip ports that don't have known speeds, or have duplicate
		 * Extended Capabilities port speed entries.
		 */
		if (port_speed == 0 || port_speed == DUPLICATE_ENTRY)
			continue;

		/*
		 * USB 3.0 ports are always under a USB 3.0 hub.  USB 2.0 and
		 * 1.1 ports are under the USB 2.0 hub.  If the port speed
		 * matches the device speed, it's a similar speed port.
		 */
		if ((port_speed == 0x03) == (udev->speed == USB_SPEED_SUPER))
			num_similar_speed_ports++;
		if (num_similar_speed_ports == faked_port_num)
			/* Roothub ports are numbered from 1 to N */
			return i+1;
	}
	return 0;
}