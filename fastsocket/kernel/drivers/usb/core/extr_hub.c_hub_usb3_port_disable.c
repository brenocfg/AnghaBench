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

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HUB_DEBOUNCE_STEP ; 
 int HUB_DEBOUNCE_TIMEOUT ; 
 int USB_PORT_STAT_LINK_STATE ; 
 int USB_SS_PORT_LS_RX_DETECT ; 
 int USB_SS_PORT_LS_SS_DISABLED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  hub_is_superspeed (int /*<<< orphan*/ ) ; 
 int hub_port_status (struct usb_hub*,int,int*,int*) ; 
 int hub_set_port_link_state (struct usb_hub*,int,int) ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 

__attribute__((used)) static int hub_usb3_port_disable(struct usb_hub *hub, int port1)
{
	int ret;
	int total_time;
	u16 portchange, portstatus;

	if (!hub_is_superspeed(hub->hdev))
		return -EINVAL;

	ret = hub_set_port_link_state(hub, port1, USB_SS_PORT_LS_SS_DISABLED);
	if (ret) {
		dev_err(hub->intfdev, "cannot disable port %d (err = %d)\n",
				port1, ret);
		return ret;
	}

	/* Wait for the link to enter the disabled state. */
	for (total_time = 0; ; total_time += HUB_DEBOUNCE_STEP) {
		ret = hub_port_status(hub, port1, &portstatus, &portchange);
		if (ret < 0)
			return ret;

		if ((portstatus & USB_PORT_STAT_LINK_STATE) ==
				USB_SS_PORT_LS_SS_DISABLED)
			break;
		if (total_time >= HUB_DEBOUNCE_TIMEOUT)
			break;
		msleep(HUB_DEBOUNCE_STEP);
	}
	if (total_time >= HUB_DEBOUNCE_TIMEOUT)
		dev_warn(hub->intfdev, "Could not disable port %d after %d ms\n",
				port1, total_time);

	return hub_set_port_link_state(hub, port1, USB_SS_PORT_LS_RX_DETECT);
}