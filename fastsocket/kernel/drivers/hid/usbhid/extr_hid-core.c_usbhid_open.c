#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usbhid_device {TYPE_1__* intf; } ;
struct hid_device {int /*<<< orphan*/  open; struct usbhid_device* driver_data; } ;
struct TYPE_3__ {int needs_remote_wakeup; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  hid_io_error (struct hid_device*) ; 
 int /*<<< orphan*/  hid_open_mut ; 
 scalar_t__ hid_start_in (struct hid_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_autopm_get_interface (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (TYPE_1__*) ; 

int usbhid_open(struct hid_device *hid)
{
	struct usbhid_device *usbhid = hid->driver_data;
	int res;

	mutex_lock(&hid_open_mut);
	if (!hid->open++) {
		res = usb_autopm_get_interface(usbhid->intf);
		/* the device must be awake to reliable request remote wakeup */
		if (res < 0) {
			hid->open--;
			mutex_unlock(&hid_open_mut);
			return -EIO;
		}
		usbhid->intf->needs_remote_wakeup = 1;
		if (hid_start_in(hid))
			hid_io_error(hid);
 
		usb_autopm_put_interface(usbhid->intf);
	}
	mutex_unlock(&hid_open_mut);
	return 0;
}