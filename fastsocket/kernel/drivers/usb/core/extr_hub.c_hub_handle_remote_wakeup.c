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
typedef  int u16 ;
struct usb_hub {int /*<<< orphan*/  intfdev; struct usb_device* hdev; } ;
struct usb_device {scalar_t__ state; struct usb_device** children; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  USB_PORT_FEAT_C_SUSPEND ; 
 int USB_PORT_STAT_C_SUSPEND ; 
 int USB_PORT_STAT_LINK_STATE ; 
 int USB_SS_PORT_LS_U0 ; 
 scalar_t__ USB_STATE_SUSPENDED ; 
 int /*<<< orphan*/  clear_port_feature (struct usb_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int /*<<< orphan*/  hub_is_superspeed (struct usb_device*) ; 
 int /*<<< orphan*/  hub_port_disable (struct usb_hub*,unsigned int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int remote_wakeup (struct usb_device*) ; 
 int /*<<< orphan*/  usb_lock_device (struct usb_device*) ; 
 int /*<<< orphan*/  usb_unlock_device (struct usb_device*) ; 

__attribute__((used)) static int hub_handle_remote_wakeup(struct usb_hub *hub, unsigned int port,
		u16 portstatus, u16 portchange)
{
	struct usb_device *hdev;
	struct usb_device *udev;
	int connect_change = 0;
	int ret;

	hdev = hub->hdev;
	udev = hdev->children[port-1];
	if (!hub_is_superspeed(hdev)) {
		if (!(portchange & USB_PORT_STAT_C_SUSPEND))
			return 0;
		clear_port_feature(hdev, port, USB_PORT_FEAT_C_SUSPEND);
	} else {
		if (!udev || udev->state != USB_STATE_SUSPENDED ||
				 (portstatus & USB_PORT_STAT_LINK_STATE) !=
				 USB_SS_PORT_LS_U0)
			return 0;
	}

	if (udev) {
		/* TRSMRCY = 10 msec */
		msleep(10);

		usb_lock_device(udev);
		ret = remote_wakeup(udev);
		usb_unlock_device(udev);
		if (ret < 0)
			connect_change = 1;
	} else {
		ret = -ENODEV;
		hub_port_disable(hub, port, 1);
	}
	dev_dbg(hub->intfdev, "resume on port %d, status %d\n",
			port, ret);
	return connect_change;
}