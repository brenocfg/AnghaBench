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
struct usb_device_id {scalar_t__ driver_info; scalar_t__ bInterfaceClass; scalar_t__ bDeviceClass; scalar_t__ idVendor; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ usb_match_device (struct usb_device*,struct usb_device_id const*) ; 
 struct usb_device_id* usb_quirk_list ; 

__attribute__((used)) static const struct usb_device_id *find_id(struct usb_device *udev)
{
	const struct usb_device_id *id = usb_quirk_list;

	for (; id->idVendor || id->bDeviceClass || id->bInterfaceClass ||
			id->driver_info; id++) {
		if (usb_match_device(udev, id))
			return id;
	}
	return NULL;
}