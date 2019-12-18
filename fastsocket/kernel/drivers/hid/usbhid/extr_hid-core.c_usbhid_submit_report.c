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
struct usbhid_device {int /*<<< orphan*/  lock; } ;
struct hid_report {int dummy; } ;
struct hid_device {struct usbhid_device* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  __usbhid_submit_report (struct hid_device*,struct hid_report*,unsigned char) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void usbhid_submit_report(struct hid_device *hid, struct hid_report *report, unsigned char dir)
{
	struct usbhid_device *usbhid = hid->driver_data;
	unsigned long flags;

	spin_lock_irqsave(&usbhid->lock, flags);
	__usbhid_submit_report(hid, report, dir);
	spin_unlock_irqrestore(&usbhid->lock, flags);
}