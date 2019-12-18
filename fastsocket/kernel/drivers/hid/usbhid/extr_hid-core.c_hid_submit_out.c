#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usbhid_device {size_t outtail; int /*<<< orphan*/  restart_work; int /*<<< orphan*/  last_out; TYPE_2__* urbout; TYPE_1__* out; int /*<<< orphan*/  outbuf; int /*<<< orphan*/  iofl; } ;
struct hid_report {int size; scalar_t__ id; } ;
struct hid_device {struct usbhid_device* driver_data; } ;
struct TYPE_4__ {int transfer_buffer_length; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {char* raw_report; struct hid_report* report; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HID_REPORTED_IDLE ; 
 int /*<<< orphan*/  dbg_hid (char*) ; 
 int /*<<< orphan*/  err_hid (char*) ; 
 int /*<<< orphan*/  hid_to_usb_dev (struct hid_device*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resumption_waker ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ usb_submit_urb (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hid_submit_out(struct hid_device *hid)
{
	struct hid_report *report;
	char *raw_report;
	struct usbhid_device *usbhid = hid->driver_data;

	report = usbhid->out[usbhid->outtail].report;
	raw_report = usbhid->out[usbhid->outtail].raw_report;

	if (!test_bit(HID_REPORTED_IDLE, &usbhid->iofl)) {
		usbhid->urbout->transfer_buffer_length = ((report->size - 1) >> 3) + 1 + (report->id > 0);
		usbhid->urbout->dev = hid_to_usb_dev(hid);
		if (raw_report) {
			memcpy(usbhid->outbuf, raw_report,
				usbhid->urbout->transfer_buffer_length);
			kfree(raw_report);
			usbhid->out[usbhid->outtail].raw_report = NULL;
		}

		dbg_hid("submitting out urb\n");

		if (usb_submit_urb(usbhid->urbout, GFP_ATOMIC)) {
			err_hid("usb_submit_urb(out) failed");
			return -1;
		}
		usbhid->last_out = jiffies;
	} else {
		/*
		 * queue work to wake up the device.
		 * as the work queue is freezeable, this is safe
		 * with respect to STD and STR
		 */
		queue_work(resumption_waker, &usbhid->restart_work);
	}

	return 0;
}