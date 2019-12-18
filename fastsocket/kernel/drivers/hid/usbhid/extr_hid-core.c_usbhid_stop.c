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
struct usbhid_device {int /*<<< orphan*/ * urbout; int /*<<< orphan*/ * urbctrl; int /*<<< orphan*/ * urbin; int /*<<< orphan*/  lock; int /*<<< orphan*/  iofl; } ;
struct hid_device {scalar_t__ claimed; struct usbhid_device* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_DISCONNECTED ; 
 int /*<<< orphan*/  HID_STARTED ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_cancel_delayed_stuff (struct usbhid_device*) ; 
 int /*<<< orphan*/  hid_free_buffers (int /*<<< orphan*/ ,struct hid_device*) ; 
 int /*<<< orphan*/  hid_to_usb_dev (struct hid_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usbhid_stop(struct hid_device *hid)
{
	struct usbhid_device *usbhid = hid->driver_data;

	if (WARN_ON(!usbhid))
		return;

	clear_bit(HID_STARTED, &usbhid->iofl);
	spin_lock_irq(&usbhid->lock);	/* Sync with error handler */
	set_bit(HID_DISCONNECTED, &usbhid->iofl);
	spin_unlock_irq(&usbhid->lock);
	usb_kill_urb(usbhid->urbin);
	usb_kill_urb(usbhid->urbout);
	usb_kill_urb(usbhid->urbctrl);

	hid_cancel_delayed_stuff(usbhid);

	hid->claimed = 0;

	usb_free_urb(usbhid->urbin);
	usb_free_urb(usbhid->urbctrl);
	usb_free_urb(usbhid->urbout);
	usbhid->urbin = NULL; /* don't mess up next start */
	usbhid->urbctrl = NULL;
	usbhid->urbout = NULL;

	hid_free_buffers(hid_to_usb_dev(hid), hid);
}