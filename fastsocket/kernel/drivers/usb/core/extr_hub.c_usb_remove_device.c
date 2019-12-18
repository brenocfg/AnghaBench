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
struct usb_interface {int dummy; } ;
struct usb_hub {int /*<<< orphan*/  removed_bits; int /*<<< orphan*/  intfdev; } ;
struct usb_device {int /*<<< orphan*/  portnum; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int EINVAL ; 
 struct usb_hub* hdev_to_hub (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hub_port_logical_disconnect (struct usb_hub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_interface* to_usb_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_get_interface (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (struct usb_interface*) ; 

int usb_remove_device(struct usb_device *udev)
{
	struct usb_hub *hub;
	struct usb_interface *intf;

	if (!udev->parent)	/* Can't remove a root hub */
		return -EINVAL;
	hub = hdev_to_hub(udev->parent);
	intf = to_usb_interface(hub->intfdev);

	usb_autopm_get_interface(intf);
	set_bit(udev->portnum, hub->removed_bits);
	hub_port_logical_disconnect(hub, udev->portnum);
	usb_autopm_put_interface(intf);
	return 0;
}