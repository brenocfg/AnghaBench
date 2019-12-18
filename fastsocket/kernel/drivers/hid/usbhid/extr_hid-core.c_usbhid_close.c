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
struct usbhid_device {int /*<<< orphan*/  lock; TYPE_1__* intf; int /*<<< orphan*/  urbin; } ;
struct hid_device {int /*<<< orphan*/  open; struct usbhid_device* driver_data; } ;
struct TYPE_2__ {scalar_t__ needs_remote_wakeup; } ;

/* Variables and functions */
 int /*<<< orphan*/  hid_cancel_delayed_stuff (struct usbhid_device*) ; 
 int /*<<< orphan*/  hid_open_mut ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

void usbhid_close(struct hid_device *hid)
{
	struct usbhid_device *usbhid = hid->driver_data;

	mutex_lock(&hid_open_mut);

	/* protecting hid->open to make sure we don't restart
	 * data acquistion due to a resumption we no longer
	 * care about
	 */
	spin_lock_irq(&usbhid->lock);
	if (!--hid->open) {
		spin_unlock_irq(&usbhid->lock);
		hid_cancel_delayed_stuff(usbhid);
		usb_kill_urb(usbhid->urbin);
		usbhid->intf->needs_remote_wakeup = 0;
	} else {
		spin_unlock_irq(&usbhid->lock);
	}
	mutex_unlock(&hid_open_mut);
}