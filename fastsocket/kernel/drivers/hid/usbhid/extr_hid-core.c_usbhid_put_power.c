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
struct usbhid_device {int /*<<< orphan*/  intf; } ;
struct hid_device {struct usbhid_device* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

void usbhid_put_power(struct hid_device *hid)
{
	struct usbhid_device *usbhid = hid->driver_data;

	usb_autopm_put_interface(usbhid->intf);
}