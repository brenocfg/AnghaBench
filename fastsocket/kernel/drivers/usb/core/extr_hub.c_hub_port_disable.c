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
struct usb_hub {int /*<<< orphan*/  intfdev; struct usb_device* hdev; int /*<<< orphan*/  error; } ;
struct usb_device {scalar_t__* children; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_PORT_FEAT_ENABLE ; 
 int /*<<< orphan*/  USB_STATE_NOTATTACHED ; 
 int clear_port_feature (struct usb_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ hub_is_superspeed (struct usb_device*) ; 
 int hub_usb3_port_disable (struct usb_hub*,int) ; 
 int /*<<< orphan*/  usb_set_device_state (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hub_port_disable(struct usb_hub *hub, int port1, int set_state)
{
	struct usb_device *hdev = hub->hdev;
	int ret = 0;

	if (hdev->children[port1-1] && set_state)
		usb_set_device_state(hdev->children[port1-1],
				USB_STATE_NOTATTACHED);
	if (!hub->error) {
		if (hub_is_superspeed(hub->hdev))
			ret = hub_usb3_port_disable(hub, port1);
		else
			ret = clear_port_feature(hdev, port1,
					USB_PORT_FEAT_ENABLE);
	}
	if (ret)
		dev_err(hub->intfdev, "cannot disable port %d (err = %d)\n",
				port1, ret);
	return ret;
}