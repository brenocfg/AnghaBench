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
struct usb_interface {int dummy; } ;
struct pegasus {int /*<<< orphan*/  intr_urb; int /*<<< orphan*/  rx_urb; int /*<<< orphan*/  net; int /*<<< orphan*/  carrier_check; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 struct pegasus* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pegasus_suspend (struct usb_interface *intf, pm_message_t message)
{
	struct pegasus *pegasus = usb_get_intfdata(intf);
	
	netif_device_detach (pegasus->net);
	cancel_delayed_work(&pegasus->carrier_check);
	if (netif_running(pegasus->net)) {
		usb_kill_urb(pegasus->rx_urb);
		usb_kill_urb(pegasus->intr_urb);
	}
	return 0;
}