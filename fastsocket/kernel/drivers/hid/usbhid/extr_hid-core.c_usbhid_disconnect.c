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
struct usbhid_device {int dummy; } ;
struct usb_interface {int dummy; } ;
struct hid_device {struct usbhid_device* driver_data; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  hid_destroy_device (struct hid_device*) ; 
 int /*<<< orphan*/  kfree (struct usbhid_device*) ; 
 struct hid_device* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static void usbhid_disconnect(struct usb_interface *intf)
{
	struct hid_device *hid = usb_get_intfdata(intf);
	struct usbhid_device *usbhid;

	if (WARN_ON(!hid))
		return;

	usbhid = hid->driver_data;
	hid_destroy_device(hid);
	kfree(usbhid);
}