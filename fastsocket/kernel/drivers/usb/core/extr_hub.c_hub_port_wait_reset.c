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
struct usb_hub {int /*<<< orphan*/  intfdev; int /*<<< orphan*/  hdev; } ;
struct usb_device {int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  HUB_BH_RESET_TIME ; 
 unsigned int HUB_LONG_RESET_TIME ; 
 int HUB_RESET_TIMEOUT ; 
 int HUB_SHORT_RESET_TIME ; 
 int /*<<< orphan*/  USB_PORT_FEAT_C_CONNECTION ; 
 int /*<<< orphan*/  USB_PORT_FEAT_C_PORT_LINK_STATE ; 
 int /*<<< orphan*/  USB_PORT_FEAT_C_RESET ; 
 int USB_PORT_STAT_CONNECTION ; 
 int USB_PORT_STAT_C_CONNECTION ; 
 int USB_PORT_STAT_C_LINK_STATE ; 
 int USB_PORT_STAT_C_RESET ; 
 int USB_PORT_STAT_ENABLE ; 
 int USB_PORT_STAT_HIGH_SPEED ; 
 int USB_PORT_STAT_LOW_SPEED ; 
 int USB_PORT_STAT_RESET ; 
 int /*<<< orphan*/  USB_SPEED_FULL ; 
 int /*<<< orphan*/  USB_SPEED_HIGH ; 
 int /*<<< orphan*/  USB_SPEED_LOW ; 
 int /*<<< orphan*/  USB_SPEED_SUPER ; 
 int /*<<< orphan*/  USB_SPEED_WIRELESS ; 
 int /*<<< orphan*/  clear_port_feature (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ hub_is_superspeed (int /*<<< orphan*/ ) ; 
 scalar_t__ hub_is_wusb (struct usb_hub*) ; 
 int hub_port_reset (struct usb_hub*,int,struct usb_device*,int /*<<< orphan*/ ,int) ; 
 int hub_port_status (struct usb_hub*,int,int*,int*) ; 
 scalar_t__ hub_port_warm_reset_required (struct usb_hub*,int) ; 
 int /*<<< orphan*/  msleep (unsigned int) ; 

__attribute__((used)) static int hub_port_wait_reset(struct usb_hub *hub, int port1,
			struct usb_device *udev, unsigned int delay, bool warm)
{
	int delay_time, ret;
	u16 portstatus;
	u16 portchange;

	for (delay_time = 0;
			delay_time < HUB_RESET_TIMEOUT;
			delay_time += delay) {
		/* wait to give the device a chance to reset */
		msleep(delay);

		/* read and decode port status */
		ret = hub_port_status(hub, port1, &portstatus, &portchange);
		if (ret < 0)
			return ret;

		/* The port state is unknown until the reset completes. */
		if ((portstatus & USB_PORT_STAT_RESET))
			goto delay;

		/*
		 * Some buggy devices require a warm reset to be issued even
		 * when the port appears not to be connected.
		 */
		if (!warm) {
			/*
			 * Some buggy devices can cause an NEC host controller
			 * to transition to the "Error" state after a hot port
			 * reset.  This will show up as the port state in
			 * "Inactive", and the port may also report a
			 * disconnect.  Forcing a warm port reset seems to make
			 * the device work.
			 *
			 * See https://bugzilla.kernel.org/show_bug.cgi?id=41752
			 */
			if (hub_port_warm_reset_required(hub, portstatus)) {
				int ret;

				if ((portchange & USB_PORT_STAT_C_CONNECTION))
					clear_port_feature(hub->hdev, port1,
							USB_PORT_FEAT_C_CONNECTION);
				if (portchange & USB_PORT_STAT_C_LINK_STATE)
					clear_port_feature(hub->hdev, port1,
							USB_PORT_FEAT_C_PORT_LINK_STATE);
				if (portchange & USB_PORT_STAT_C_RESET)
					clear_port_feature(hub->hdev, port1,
							USB_PORT_FEAT_C_RESET);
				dev_dbg(hub->intfdev, "hot reset failed, warm reset port %d\n",
						port1);
				ret = hub_port_reset(hub, port1,
						udev, HUB_BH_RESET_TIME,
						true);
				if ((portchange & USB_PORT_STAT_C_CONNECTION))
					clear_port_feature(hub->hdev, port1,
							USB_PORT_FEAT_C_CONNECTION);
				return ret;
			}
			/* Device went away? */
			if (!(portstatus & USB_PORT_STAT_CONNECTION))
				return -ENOTCONN;

			/* bomb out completely if the connection bounced */
			if ((portchange & USB_PORT_STAT_C_CONNECTION))
				return -ENOTCONN;

			if ((portstatus & USB_PORT_STAT_ENABLE)) {
				if (hub_is_wusb(hub))
					udev->speed = USB_SPEED_WIRELESS;
				else if (hub_is_superspeed(hub->hdev))
					udev->speed = USB_SPEED_SUPER;
				else if (portstatus & USB_PORT_STAT_HIGH_SPEED)
					udev->speed = USB_SPEED_HIGH;
				else if (portstatus & USB_PORT_STAT_LOW_SPEED)
					udev->speed = USB_SPEED_LOW;
				else
					udev->speed = USB_SPEED_FULL;
				return 0;
			}
		} else {
			if (!(portstatus & USB_PORT_STAT_CONNECTION) ||
					hub_port_warm_reset_required(hub,
						portstatus))
				return -ENOTCONN;

			return 0;
		}

delay:
		/* switch to the long delay after two short delay failures */
		if (delay_time >= 2 * HUB_SHORT_RESET_TIME)
			delay = HUB_LONG_RESET_TIME;

		dev_dbg (hub->intfdev,
			"port %d not %sreset yet, waiting %dms\n",
			port1, warm ? "warm " : "", delay);
	}

	return -EBUSY;
}