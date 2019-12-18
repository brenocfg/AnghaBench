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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct kaweth_device {int /*<<< orphan*/  intbufferhandle; scalar_t__ intbuffer; int /*<<< orphan*/  dev; int /*<<< orphan*/  rxbufferhandle; scalar_t__ rx_buf; int /*<<< orphan*/  irq_urb; int /*<<< orphan*/  tx_urb; int /*<<< orphan*/  rx_urb; struct net_device* net; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTBUFFERSIZE ; 
 int /*<<< orphan*/  KAWETH_BUF_SIZE ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  usb_buffer_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct kaweth_device* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kaweth_disconnect(struct usb_interface *intf)
{
	struct kaweth_device *kaweth = usb_get_intfdata(intf);
	struct net_device *netdev;

	dev_info(&intf->dev, "Unregistering\n");

	usb_set_intfdata(intf, NULL);
	if (!kaweth) {
		dev_warn(&intf->dev, "unregistering non-existant device\n");
		return;
	}
	netdev = kaweth->net;

	dbg("Unregistering net device");
	unregister_netdev(netdev);

	usb_free_urb(kaweth->rx_urb);
	usb_free_urb(kaweth->tx_urb);
	usb_free_urb(kaweth->irq_urb);

	usb_buffer_free(kaweth->dev, KAWETH_BUF_SIZE, (void *)kaweth->rx_buf, kaweth->rxbufferhandle);
	usb_buffer_free(kaweth->dev, INTBUFFERSIZE, (void *)kaweth->intbuffer, kaweth->intbufferhandle);

	free_netdev(netdev);
}