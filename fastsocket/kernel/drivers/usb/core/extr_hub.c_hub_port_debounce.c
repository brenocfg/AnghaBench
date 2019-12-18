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
typedef  unsigned int u16 ;
struct usb_hub {int /*<<< orphan*/  intfdev; int /*<<< orphan*/  hdev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HUB_DEBOUNCE_STABLE ; 
 scalar_t__ HUB_DEBOUNCE_STEP ; 
 int HUB_DEBOUNCE_TIMEOUT ; 
 int /*<<< orphan*/  USB_PORT_FEAT_C_CONNECTION ; 
 unsigned int USB_PORT_STAT_CONNECTION ; 
 unsigned int USB_PORT_STAT_C_CONNECTION ; 
 int /*<<< orphan*/  clear_port_feature (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int,unsigned int) ; 
 int hub_port_status (struct usb_hub*,int,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 

__attribute__((used)) static int hub_port_debounce(struct usb_hub *hub, int port1)
{
	int ret;
	int total_time, stable_time = 0;
	u16 portchange, portstatus;
	unsigned connection = 0xffff;

	for (total_time = 0; ; total_time += HUB_DEBOUNCE_STEP) {
		ret = hub_port_status(hub, port1, &portstatus, &portchange);
		if (ret < 0)
			return ret;

		if (!(portchange & USB_PORT_STAT_C_CONNECTION) &&
		     (portstatus & USB_PORT_STAT_CONNECTION) == connection) {
			stable_time += HUB_DEBOUNCE_STEP;
			if (stable_time >= HUB_DEBOUNCE_STABLE)
				break;
		} else {
			stable_time = 0;
			connection = portstatus & USB_PORT_STAT_CONNECTION;
		}

		if (portchange & USB_PORT_STAT_C_CONNECTION) {
			clear_port_feature(hub->hdev, port1,
					USB_PORT_FEAT_C_CONNECTION);
		}

		if (total_time >= HUB_DEBOUNCE_TIMEOUT)
			break;
		msleep(HUB_DEBOUNCE_STEP);
	}

	dev_dbg (hub->intfdev,
		"debounce: port %d: total %dms stable %dms status 0x%x\n",
		port1, total_time, stable_time, portstatus);

	if (stable_time < HUB_DEBOUNCE_STABLE)
		return -ETIMEDOUT;
	return portstatus;
}