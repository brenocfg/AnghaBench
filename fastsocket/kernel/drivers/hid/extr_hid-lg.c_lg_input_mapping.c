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
typedef  int u8 ;
struct hid_usage {unsigned int hid; } ;
struct hid_input {int dummy; } ;
struct hid_field {scalar_t__ application; } ;
struct hid_device {scalar_t__ product; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int const*) ; 
 int /*<<< orphan*/  EV_KEY ; 
 scalar_t__ HID_GD_MOUSE ; 
 unsigned int HID_UP_BUTTON ; 
 unsigned int HID_USAGE ; 
 unsigned int HID_USAGE_PAGE ; 
 unsigned long LG_EXPANDED_KEYMAP ; 
 unsigned long LG_IGNORE_DOUBLED_WHEEL ; 
 unsigned long LG_WIRELESS ; 
 scalar_t__ USB_DEVICE_ID_LOGITECH_RECEIVER ; 
 scalar_t__ hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_map_usage (struct hid_input*,struct hid_usage*,unsigned long**,int*,int /*<<< orphan*/ ,int const) ; 
 scalar_t__ lg_ultrax_remote_mapping (struct hid_input*,struct hid_usage*,unsigned long**,int*) ; 
 scalar_t__ lg_wireless_mapping (struct hid_input*,struct hid_usage*,unsigned long**,int*) ; 

__attribute__((used)) static int lg_input_mapping(struct hid_device *hdev, struct hid_input *hi,
		struct hid_field *field, struct hid_usage *usage,
		unsigned long **bit, int *max)
{
	/* extended mapping for certain Logitech hardware (Logitech cordless
	   desktop LX500) */
	static const u8 e_keymap[] = {
		  0,216,  0,213,175,156,  0,  0,  0,  0,
		144,  0,  0,  0,  0,  0,  0,  0,  0,212,
		174,167,152,161,112,  0,  0,  0,154,  0,
		  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		  0,  0,  0,  0,  0,183,184,185,186,187,
		188,189,190,191,192,193,194,  0,  0,  0
	};
	unsigned long quirks = (unsigned long)hid_get_drvdata(hdev);
	unsigned int hid = usage->hid;

	if (hdev->product == USB_DEVICE_ID_LOGITECH_RECEIVER &&
			lg_ultrax_remote_mapping(hi, usage, bit, max))
		return 1;

	if ((quirks & LG_WIRELESS) && lg_wireless_mapping(hi, usage, bit, max))
		return 1;

	if ((hid & HID_USAGE_PAGE) != HID_UP_BUTTON)
		return 0;

	hid &= HID_USAGE;

	/* Special handling for Logitech Cordless Desktop */
	if (field->application == HID_GD_MOUSE) {
		if ((quirks & LG_IGNORE_DOUBLED_WHEEL) &&
				(hid == 7 || hid == 8))
			return -1;
	} else {
		if ((quirks & LG_EXPANDED_KEYMAP) &&
				hid < ARRAY_SIZE(e_keymap) &&
				e_keymap[hid] != 0) {
			hid_map_usage(hi, usage, bit, max, EV_KEY,
					e_keymap[hid]);
			return 1;
		}
	}

	return 0;
}