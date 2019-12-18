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
struct usb_interface {int minor; int /*<<< orphan*/  dev; } ;
struct ld_usb {int /*<<< orphan*/  mutex; int /*<<< orphan*/  write_wait; int /*<<< orphan*/  read_wait; int /*<<< orphan*/ * intf; int /*<<< orphan*/  open_count; } ;

/* Variables and functions */
 scalar_t__ USB_LD_MINOR_BASE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  ld_usb_class ; 
 int /*<<< orphan*/  ld_usb_delete (struct ld_usb*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_deregister_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 struct ld_usb* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ld_usb_disconnect(struct usb_interface *intf)
{
	struct ld_usb *dev;
	int minor;

	dev = usb_get_intfdata(intf);
	usb_set_intfdata(intf, NULL);

	minor = intf->minor;

	/* give back our minor */
	usb_deregister_dev(intf, &ld_usb_class);

	mutex_lock(&dev->mutex);

	/* if the device is not opened, then we clean up right now */
	if (!dev->open_count) {
		mutex_unlock(&dev->mutex);
		ld_usb_delete(dev);
	} else {
		dev->intf = NULL;
		/* wake up pollers */
		wake_up_interruptible_all(&dev->read_wait);
		wake_up_interruptible_all(&dev->write_wait);
		mutex_unlock(&dev->mutex);
	}

	dev_info(&intf->dev, "LD USB Device #%d now disconnected\n",
		 (minor - USB_LD_MINOR_BASE));
}