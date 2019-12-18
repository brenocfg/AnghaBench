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
struct hid_device {int vendor; scalar_t__ type; int /*<<< orphan*/  product; } ;

/* Variables and functions */
 scalar_t__ HID_TYPE_USBMOUSE ; 
 int /*<<< orphan*/  USB_DEVICE_ID_CODEMERCS_IOW_FIRST ; 
 int /*<<< orphan*/  USB_DEVICE_ID_CODEMERCS_IOW_LAST ; 
 int /*<<< orphan*/  USB_DEVICE_ID_LOGITECH_HARMONY_FIRST ; 
 int /*<<< orphan*/  USB_DEVICE_ID_LOGITECH_HARMONY_LAST ; 
 int /*<<< orphan*/  USB_DEVICE_ID_SOUNDGRAPH_IMON_FIRST ; 
 int /*<<< orphan*/  USB_DEVICE_ID_SOUNDGRAPH_IMON_LAST ; 
#define  USB_VENDOR_ID_CODEMERCS 130 
#define  USB_VENDOR_ID_LOGITECH 129 
#define  USB_VENDOR_ID_SOUNDGRAPH 128 
 int /*<<< orphan*/  hid_ignore_list ; 
 scalar_t__ hid_match_id (struct hid_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_mouse_ignore_list ; 

__attribute__((used)) static bool hid_ignore(struct hid_device *hdev)
{
	switch (hdev->vendor) {
	case USB_VENDOR_ID_CODEMERCS:
		/* ignore all Code Mercenaries IOWarrior devices */
		if (hdev->product >= USB_DEVICE_ID_CODEMERCS_IOW_FIRST &&
				hdev->product <= USB_DEVICE_ID_CODEMERCS_IOW_LAST)
			return true;
		break;
	case USB_VENDOR_ID_LOGITECH:
		if (hdev->product >= USB_DEVICE_ID_LOGITECH_HARMONY_FIRST &&
				hdev->product <= USB_DEVICE_ID_LOGITECH_HARMONY_LAST)
			return true;
		break;
	case USB_VENDOR_ID_SOUNDGRAPH:
		if (hdev->product >= USB_DEVICE_ID_SOUNDGRAPH_IMON_FIRST &&
		    hdev->product <= USB_DEVICE_ID_SOUNDGRAPH_IMON_LAST)
			return true;
		break;
	}

	if (hdev->type == HID_TYPE_USBMOUSE &&
			hid_match_id(hdev, hid_mouse_ignore_list))
		return true;

	return !!hid_match_id(hdev, hid_ignore_list);
}