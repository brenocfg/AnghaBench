#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct usb_hub {int /*<<< orphan*/  hdev; TYPE_1__* descriptor; int /*<<< orphan*/  intfdev; } ;
struct TYPE_2__ {int bPwrOn2PwrGood; int bNbrPorts; int /*<<< orphan*/  wHubCharacteristics; } ;

/* Variables and functions */
 int HUB_CHAR_LPSM ; 
 int /*<<< orphan*/  USB_PORT_FEAT_POWER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int max (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  msleep (unsigned int) ; 
 int /*<<< orphan*/  set_port_feature (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned hub_power_on(struct usb_hub *hub, bool do_delay)
{
	int port1;
	unsigned pgood_delay = hub->descriptor->bPwrOn2PwrGood * 2;
	unsigned delay;
	u16 wHubCharacteristics =
			le16_to_cpu(hub->descriptor->wHubCharacteristics);

	/* Enable power on each port.  Some hubs have reserved values
	 * of LPSM (> 2) in their descriptors, even though they are
	 * USB 2.0 hubs.  Some hubs do not implement port-power switching
	 * but only emulate it.  In all cases, the ports won't work
	 * unless we send these messages to the hub.
	 */
	if ((wHubCharacteristics & HUB_CHAR_LPSM) < 2)
		dev_dbg(hub->intfdev, "enabling power on all ports\n");
	else
		dev_dbg(hub->intfdev, "trying to enable port power on "
				"non-switchable hub\n");
	for (port1 = 1; port1 <= hub->descriptor->bNbrPorts; port1++)
		set_port_feature(hub->hdev, port1, USB_PORT_FEAT_POWER);

	/* Wait at least 100 msec for power to become stable */
	delay = max(pgood_delay, (unsigned) 100);
	if (do_delay)
		msleep(delay);
	return delay;
}