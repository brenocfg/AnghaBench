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
struct ems_usb {int /*<<< orphan*/  intr_in_buffer; int /*<<< orphan*/  intr_urb; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_candev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink_all_urbs (struct ems_usb*) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct ems_usb* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ems_usb_disconnect(struct usb_interface *intf)
{
	struct ems_usb *dev = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NULL);

	if (dev) {
		unregister_netdev(dev->netdev);
		free_candev(dev->netdev);

		unlink_all_urbs(dev);

		usb_free_urb(dev->intr_urb);

		kfree(dev->intr_in_buffer);
	}
}