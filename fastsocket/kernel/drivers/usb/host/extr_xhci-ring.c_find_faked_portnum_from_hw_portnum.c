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
struct xhci_hcd {int* port_array; } ;
struct usb_hcd {scalar_t__ speed; } ;

/* Variables and functions */
 int DUPLICATE_ENTRY ; 
 scalar_t__ HCD_USB3 ; 

__attribute__((used)) static unsigned int find_faked_portnum_from_hw_portnum(struct usb_hcd *hcd,
		struct xhci_hcd *xhci, u32 port_id)
{
	unsigned int i;
	unsigned int num_similar_speed_ports = 0;

	/* port_id from the hardware is 1-based, but port_array[], usb3_ports[],
	 * and usb2_ports are 0-based indexes.  Count the number of similar
	 * speed ports, up to 1 port before this port.
	 */
	for (i = 0; i < (port_id - 1); i++) {
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
		if ((port_speed == 0x03) == (hcd->speed == HCD_USB3))
			num_similar_speed_ports++;
	}
	return num_similar_speed_ports;
}