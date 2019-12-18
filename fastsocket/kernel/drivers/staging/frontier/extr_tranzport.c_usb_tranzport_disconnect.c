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
struct usb_tranzport {int /*<<< orphan*/  sem; int /*<<< orphan*/ * intf; int /*<<< orphan*/  open_count; } ;
struct usb_interface {int minor; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ USB_TRANZPORT_MINOR_BASE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  disconnect_mutex ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_deregister_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 struct usb_tranzport* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_tranzport_class ; 
 int /*<<< orphan*/  usb_tranzport_delete (struct usb_tranzport*) ; 

__attribute__((used)) static void usb_tranzport_disconnect(struct usb_interface *intf)
{
	struct usb_tranzport *dev;
	int minor;
	mutex_lock(&disconnect_mutex);
	dev = usb_get_intfdata(intf);
	usb_set_intfdata(intf, NULL);
	down(&dev->sem);
	minor = intf->minor;
	/* give back our minor */
	usb_deregister_dev(intf, &usb_tranzport_class);

	/* if the device is not opened, then we clean up right now */
	if (!dev->open_count) {
		up(&dev->sem);
		usb_tranzport_delete(dev);
	} else {
		dev->intf = NULL;
		up(&dev->sem);
	}

	mutex_unlock(&disconnect_mutex);

	dev_info(&intf->dev, "Tranzport Surface #%d now disconnected\n",
		(minor - USB_TRANZPORT_MINOR_BASE));
}