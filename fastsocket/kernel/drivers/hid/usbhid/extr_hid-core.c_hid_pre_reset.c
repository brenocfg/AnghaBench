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
struct usbhid_device {int /*<<< orphan*/  restart_work; int /*<<< orphan*/  lock; int /*<<< orphan*/  iofl; } ;
struct usb_interface {int dummy; } ;
struct hid_device {struct usbhid_device* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_RESET_PENDING ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_cease_io (struct usbhid_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct hid_device* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int hid_pre_reset(struct usb_interface *intf)
{
	struct hid_device *hid = usb_get_intfdata(intf);
	struct usbhid_device *usbhid = hid->driver_data;

	spin_lock_irq(&usbhid->lock);
	set_bit(HID_RESET_PENDING, &usbhid->iofl);
	spin_unlock_irq(&usbhid->lock);
	cancel_work_sync(&usbhid->restart_work);
	hid_cease_io(usbhid);

	return 0;
}