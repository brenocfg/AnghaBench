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
typedef  enum usb_device_speed { ____Placeholder_usb_device_speed } usb_device_speed ;
struct TYPE_3__ {int* port_status; int pending_port; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int USB_PORT_FEAT_C_CONNECTION ; 
 int USB_PORT_STAT_CONNECTION ; 
 int USB_PORT_STAT_HIGH_SPEED ; 
 int USB_PORT_STAT_LOW_SPEED ; 
#define  USB_SPEED_HIGH 129 
#define  USB_SPEED_LOW 128 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* the_controller ; 
 int /*<<< orphan*/  usb_hcd_poll_rh_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_dbg_vhci_rh (char*,int) ; 
 int /*<<< orphan*/  vhci_to_hcd (TYPE_1__*) ; 

void rh_port_connect(int rhport, enum usb_device_speed speed)
{
	unsigned long	flags;

	usbip_dbg_vhci_rh("rh_port_connect %d\n", rhport);

	spin_lock_irqsave(&the_controller->lock, flags);

	the_controller->port_status[rhport] |= USB_PORT_STAT_CONNECTION
		| (1 << USB_PORT_FEAT_C_CONNECTION);

	switch (speed) {
	case USB_SPEED_HIGH:
		the_controller->port_status[rhport] |= USB_PORT_STAT_HIGH_SPEED;
		break;
	case USB_SPEED_LOW:
		the_controller->port_status[rhport] |= USB_PORT_STAT_LOW_SPEED;
		break;
	default:
		break;
	}

	/* spin_lock(&the_controller->vdev[rhport].ud.lock);
	 * the_controller->vdev[rhport].ud.status = VDEV_CONNECT;
	 * spin_unlock(&the_controller->vdev[rhport].ud.lock); */

	the_controller->pending_port = rhport;

	spin_unlock_irqrestore(&the_controller->lock, flags);

	usb_hcd_poll_rh_status(vhci_to_hcd(the_controller));
}