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
struct usbhid_device {int retry_delay; int /*<<< orphan*/  lock; int /*<<< orphan*/  io_retry; int /*<<< orphan*/  reset_work; int /*<<< orphan*/  iofl; scalar_t__ stop_retry; } ;
struct hid_device {struct usbhid_device* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_DISCONNECTED ; 
 int /*<<< orphan*/  HID_RESET_PENDING ; 
 int HZ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void hid_io_error(struct hid_device *hid)
{
	unsigned long flags;
	struct usbhid_device *usbhid = hid->driver_data;

	spin_lock_irqsave(&usbhid->lock, flags);

	/* Stop when disconnected */
	if (test_bit(HID_DISCONNECTED, &usbhid->iofl))
		goto done;

	/* If it has been a while since the last error, we'll assume
	 * this a brand new error and reset the retry timeout. */
	if (time_after(jiffies, usbhid->stop_retry + HZ/2))
		usbhid->retry_delay = 0;

	/* When an error occurs, retry at increasing intervals */
	if (usbhid->retry_delay == 0) {
		usbhid->retry_delay = 13;	/* Then 26, 52, 104, 104, ... */
		usbhid->stop_retry = jiffies + msecs_to_jiffies(1000);
	} else if (usbhid->retry_delay < 100)
		usbhid->retry_delay *= 2;

	if (time_after(jiffies, usbhid->stop_retry)) {

		/* Retries failed, so do a port reset */
		if (!test_and_set_bit(HID_RESET_PENDING, &usbhid->iofl)) {
			schedule_work(&usbhid->reset_work);
			goto done;
		}
	}

	mod_timer(&usbhid->io_retry,
			jiffies + msecs_to_jiffies(usbhid->retry_delay));
done:
	spin_unlock_irqrestore(&usbhid->lock, flags);
}