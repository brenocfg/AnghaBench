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
struct usb_interface {int ep_devs_created; int /*<<< orphan*/  dev; scalar_t__ unregistering; struct usb_host_interface* cur_altsetting; } ;
struct TYPE_2__ {int bNumEndpoints; } ;
struct usb_host_interface {int /*<<< orphan*/ * endpoint; TYPE_1__ desc; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_create_ep_devs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct usb_device*) ; 

__attribute__((used)) static int create_intf_ep_devs(struct usb_interface *intf)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	struct usb_host_interface *alt = intf->cur_altsetting;
	int i;

	if (intf->ep_devs_created || intf->unregistering)
		return 0;

	for (i = 0; i < alt->desc.bNumEndpoints; ++i)
		(void) usb_create_ep_devs(&intf->dev, &alt->endpoint[i], udev);
	intf->ep_devs_created = 1;
	return 0;
}