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
struct usbhid_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  iofl; int /*<<< orphan*/  urbin; } ;
struct hid_device {scalar_t__ open; struct usbhid_device* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HID_DISCONNECTED ; 
 int /*<<< orphan*/  HID_IN_RUNNING ; 
 int /*<<< orphan*/  HID_REPORTED_IDLE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hid_start_in(struct hid_device *hid)
{
	unsigned long flags;
	int rc = 0;
	struct usbhid_device *usbhid = hid->driver_data;

	spin_lock_irqsave(&usbhid->lock, flags);
	if (hid->open > 0 &&
			!test_bit(HID_DISCONNECTED, &usbhid->iofl) &&
			!test_bit(HID_REPORTED_IDLE, &usbhid->iofl) &&
			!test_and_set_bit(HID_IN_RUNNING, &usbhid->iofl)) {
		rc = usb_submit_urb(usbhid->urbin, GFP_ATOMIC);
		if (rc != 0)
			clear_bit(HID_IN_RUNNING, &usbhid->iofl);
	}
	spin_unlock_irqrestore(&usbhid->lock, flags);
	return rc;
}