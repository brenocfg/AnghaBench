#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usbnet {int /*<<< orphan*/  interrupt; TYPE_4__* driver_info; int /*<<< orphan*/  deferred; int /*<<< orphan*/  kevent; struct net_device* net; } ;
struct TYPE_6__ {TYPE_1__* driver; } ;
struct usb_interface {TYPE_2__ dev; } ;
struct usb_device {int /*<<< orphan*/  devpath; TYPE_3__* bus; } ;
struct net_device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* unbind ) (struct usbnet*,struct usb_interface*) ;int /*<<< orphan*/  description; } ;
struct TYPE_7__ {int /*<<< orphan*/  bus_name; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  netif_info (struct usbnet*,int /*<<< orphan*/ ,struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  stub1 (struct usbnet*,struct usb_interface*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct usbnet* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_scuttle_anchored_urbs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

void usbnet_disconnect (struct usb_interface *intf)
{
	struct usbnet		*dev;
	struct usb_device	*xdev;
	struct net_device	*net;

	dev = usb_get_intfdata(intf);
	usb_set_intfdata(intf, NULL);
	if (!dev)
		return;

	xdev = interface_to_usbdev (intf);

	netif_info(dev, probe, dev->net, "unregister '%s' usb-%s-%s, %s\n",
		   intf->dev.driver->name,
		   xdev->bus->bus_name, xdev->devpath,
		   dev->driver_info->description);

	net = dev->net;
	unregister_netdev (net);

	cancel_work_sync(&dev->kevent);

	usb_scuttle_anchored_urbs(&dev->deferred);

	if (dev->driver_info->unbind)
		dev->driver_info->unbind (dev, intf);

	usb_kill_urb(dev->interrupt);
	usb_free_urb(dev->interrupt);

	free_netdev(net);
}