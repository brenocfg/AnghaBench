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
typedef  scalar_t__ u32 ;
struct usb_device_id {scalar_t__ driver_info; } ;
struct TYPE_2__ {scalar_t__ bDeviceClass; } ;
struct usb_device {int autosuspend_disabled; int persist_enabled; TYPE_1__ descriptor; scalar_t__ quirks; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ USB_CLASS_HUB ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 struct usb_device_id* find_id (struct usb_device*) ; 
 struct usb_device_id* usb_quirk_list ; 

void usb_detect_quirks(struct usb_device *udev)
{
	const struct usb_device_id *id = usb_quirk_list;

	id = find_id(udev);
	if (id)
		udev->quirks = (u32)(id->driver_info);
	if (udev->quirks)
		dev_dbg(&udev->dev, "USB quirks for this device: %x\n",
				udev->quirks);

	/* By default, disable autosuspend for all non-hubs */
#ifdef	CONFIG_USB_SUSPEND
	if (udev->descriptor.bDeviceClass != USB_CLASS_HUB)
		udev->autosuspend_disabled = 1;
#endif

	/* For the present, all devices default to USB-PERSIST enabled */
#if 0		/* was: #ifdef CONFIG_PM */
	/* Hubs are automatically enabled for USB-PERSIST */
	if (udev->descriptor.bDeviceClass == USB_CLASS_HUB)
		udev->persist_enabled = 1;

#else
	/* In the absence of PM, we can safely enable USB-PERSIST
	 * for all devices.  It will affect things like hub resets
	 * and EMF-related port disables.
	 */
	udev->persist_enabled = 1;
#endif	/* CONFIG_PM */
}