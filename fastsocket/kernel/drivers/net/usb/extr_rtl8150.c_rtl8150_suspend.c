#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  intr_urb; int /*<<< orphan*/  rx_urb; int /*<<< orphan*/  netdev; } ;
typedef  TYPE_1__ rtl8150_t ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 TYPE_1__* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8150_suspend(struct usb_interface *intf, pm_message_t message)
{
	rtl8150_t *dev = usb_get_intfdata(intf);

	netif_device_detach(dev->netdev);

	if (netif_running(dev->netdev)) {
		usb_kill_urb(dev->rx_urb);
		usb_kill_urb(dev->intr_urb);
	}
	return 0;
}