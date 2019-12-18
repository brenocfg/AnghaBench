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
struct mdc800_data {scalar_t__ state; int /*<<< orphan*/ * dev; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  download_urb; int /*<<< orphan*/  write_urb; int /*<<< orphan*/  irq_urb; } ;

/* Variables and functions */
 scalar_t__ NOT_CONNECTED ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mdc800_class ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_deregister_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 struct mdc800_data* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mdc800_usb_disconnect (struct usb_interface *intf)
{
	struct mdc800_data* mdc800 = usb_get_intfdata(intf);

	dbg ("(mdc800_usb_disconnect) called");

	if (mdc800) {
		if (mdc800->state == NOT_CONNECTED)
			return;

		usb_deregister_dev(intf, &mdc800_class);

		/* must be under lock to make sure no URB
		   is submitted after usb_kill_urb() */
		mutex_lock(&mdc800->io_lock);
		mdc800->state=NOT_CONNECTED;

		usb_kill_urb(mdc800->irq_urb);
		usb_kill_urb(mdc800->write_urb);
		usb_kill_urb(mdc800->download_urb);
		mutex_unlock(&mdc800->io_lock);

		mdc800->dev = NULL;
		usb_set_intfdata(intf, NULL);
	}
	dev_info(&intf->dev, "Mustek MDC800 disconnected from USB.\n");
}