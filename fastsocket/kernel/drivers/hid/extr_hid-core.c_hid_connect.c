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
struct hidraw {int minor; } ;
struct hid_device {int bus; int claimed; int minor; unsigned int maxcollection; int version; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; struct hid_collection* collection; scalar_t__ hidraw; int /*<<< orphan*/  (* ff_init ) (struct hid_device*) ;int /*<<< orphan*/  (* hiddev_connect ) (struct hid_device*,unsigned int) ;} ;
struct hid_collection {scalar_t__ type; int usage; } ;

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
#define  BUS_BLUETOOTH 129 
#define  BUS_USB 128 
 int ENODEV ; 
 int HID_CLAIMED_HIDDEV ; 
 int HID_CLAIMED_HIDRAW ; 
 int HID_CLAIMED_INPUT ; 
 scalar_t__ HID_COLLECTION_APPLICATION ; 
 unsigned int HID_CONNECT_FF ; 
 unsigned int HID_CONNECT_HIDDEV ; 
 unsigned int HID_CONNECT_HIDDEV_FORCE ; 
 unsigned int HID_CONNECT_HIDINPUT ; 
 unsigned int HID_CONNECT_HIDINPUT_FORCE ; 
 unsigned int HID_CONNECT_HIDRAW ; 
 int HID_UP_GENDESK ; 
 int HID_USAGE_PAGE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*,char const*,int,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hid_hiddev (struct hid_device*) ; 
 int /*<<< orphan*/  hidinput_connect (struct hid_device*,unsigned int) ; 
 int /*<<< orphan*/  hidraw_connect (struct hid_device*) ; 
 scalar_t__ sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  stub1 (struct hid_device*,unsigned int) ; 
 int /*<<< orphan*/  stub2 (struct hid_device*) ; 

int hid_connect(struct hid_device *hdev, unsigned int connect_mask)
{
	static const char *types[] = { "Device", "Pointer", "Mouse", "Device",
		"Joystick", "Gamepad", "Keyboard", "Keypad",
		"Multi-Axis Controller"
	};
	const char *type, *bus;
	char buf[64];
	unsigned int i;
	int len;

	if (hdev->bus != BUS_USB)
		connect_mask &= ~HID_CONNECT_HIDDEV;
	if (hid_hiddev(hdev))
		connect_mask |= HID_CONNECT_HIDDEV_FORCE;

	if ((connect_mask & HID_CONNECT_HIDINPUT) && !hidinput_connect(hdev,
				connect_mask & HID_CONNECT_HIDINPUT_FORCE))
		hdev->claimed |= HID_CLAIMED_INPUT;
	if ((connect_mask & HID_CONNECT_HIDDEV) && hdev->hiddev_connect &&
			!hdev->hiddev_connect(hdev,
				connect_mask & HID_CONNECT_HIDDEV_FORCE))
		hdev->claimed |= HID_CLAIMED_HIDDEV;
	if ((connect_mask & HID_CONNECT_HIDRAW) && !hidraw_connect(hdev))
		hdev->claimed |= HID_CLAIMED_HIDRAW;

	if (!hdev->claimed) {
		dev_err(&hdev->dev, "claimed by neither input, hiddev nor "
				"hidraw\n");
		return -ENODEV;
	}

	if ((hdev->claimed & HID_CLAIMED_INPUT) &&
			(connect_mask & HID_CONNECT_FF) && hdev->ff_init)
		hdev->ff_init(hdev);

	len = 0;
	if (hdev->claimed & HID_CLAIMED_INPUT)
		len += sprintf(buf + len, "input");
	if (hdev->claimed & HID_CLAIMED_HIDDEV)
		len += sprintf(buf + len, "%shiddev%d", len ? "," : "",
				hdev->minor);
	if (hdev->claimed & HID_CLAIMED_HIDRAW)
		len += sprintf(buf + len, "%shidraw%d", len ? "," : "",
				((struct hidraw *)hdev->hidraw)->minor);

	type = "Device";
	for (i = 0; i < hdev->maxcollection; i++) {
		struct hid_collection *col = &hdev->collection[i];
		if (col->type == HID_COLLECTION_APPLICATION &&
		   (col->usage & HID_USAGE_PAGE) == HID_UP_GENDESK &&
		   (col->usage & 0xffff) < ARRAY_SIZE(types)) {
			type = types[col->usage & 0xffff];
			break;
		}
	}

	switch (hdev->bus) {
	case BUS_USB:
		bus = "USB";
		break;
	case BUS_BLUETOOTH:
		bus = "BLUETOOTH";
		break;
	default:
		bus = "<UNKNOWN>";
	}

	dev_info(&hdev->dev, "%s: %s HID v%x.%02x %s [%s] on %s\n",
			buf, bus, hdev->version >> 8, hdev->version & 0xff,
			type, hdev->name, hdev->phys);

	return 0;
}