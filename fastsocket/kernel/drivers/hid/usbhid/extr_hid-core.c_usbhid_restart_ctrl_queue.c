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
struct usbhid_device {scalar_t__ ctrlhead; scalar_t__ ctrltail; int /*<<< orphan*/  wait; int /*<<< orphan*/  iofl; int /*<<< orphan*/  intf; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_CTRL_RUNNING ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ hid_submit_ctrl (struct hid_device*) ; 
 struct hid_device* usb_get_intfdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int usbhid_restart_ctrl_queue(struct usbhid_device *usbhid)
{
	struct hid_device *hid = usb_get_intfdata(usbhid->intf);
	int kicked;

	WARN_ON(hid == NULL);
	if (!hid)
		return 0;

	if ((kicked = (usbhid->ctrlhead != usbhid->ctrltail))) {
		dbg("Kicking head %d tail %d", usbhid->ctrlhead, usbhid->ctrltail);
		if (hid_submit_ctrl(hid)) {
			clear_bit(HID_CTRL_RUNNING, &usbhid->iofl);
			wake_up(&usbhid->wait);
		}
	}
	return kicked;
}