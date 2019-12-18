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
struct usbhid_device {TYPE_1__* intf; } ;
struct hid_device {struct usbhid_device* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hid_io_error (struct hid_device*) ; 
 scalar_t__ hid_start_in (struct hid_device*) ; 

__attribute__((used)) static void hid_retry_timeout(unsigned long _hid)
{
	struct hid_device *hid = (struct hid_device *) _hid;
	struct usbhid_device *usbhid = hid->driver_data;

	dev_dbg(&usbhid->intf->dev, "retrying intr urb\n");
	if (hid_start_in(hid))
		hid_io_error(hid);
}