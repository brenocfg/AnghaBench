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
struct input_dev {int dummy; } ;
struct hid_usage {int hid; int /*<<< orphan*/  type; } ;
struct hid_field {TYPE_1__* hidinput; } ;
struct hid_device {int claimed; } ;
typedef  int __s32 ;
struct TYPE_2__ {struct input_dev* input; } ;

/* Variables and functions */
 int HID_CLAIMED_INPUT ; 
 int HID_UP_MSVENDOR ; 
 unsigned int KEY_F14 ; 
 unsigned int KEY_F15 ; 
 unsigned int KEY_F16 ; 
 unsigned int KEY_F17 ; 
 unsigned int KEY_F18 ; 
 unsigned long MS_ERGONOMY ; 
 scalar_t__ hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static int ms_event(struct hid_device *hdev, struct hid_field *field,
		struct hid_usage *usage, __s32 value)
{
	unsigned long quirks = (unsigned long)hid_get_drvdata(hdev);

	if (!(hdev->claimed & HID_CLAIMED_INPUT) || !field->hidinput ||
			!usage->type)
		return 0;

	/* Handling MS keyboards special buttons */
	if (quirks & MS_ERGONOMY && usage->hid == (HID_UP_MSVENDOR | 0xff05)) {
		struct input_dev *input = field->hidinput->input;
		static unsigned int last_key = 0;
		unsigned int key = 0;
		switch (value) {
		case 0x01: key = KEY_F14; break;
		case 0x02: key = KEY_F15; break;
		case 0x04: key = KEY_F16; break;
		case 0x08: key = KEY_F17; break;
		case 0x10: key = KEY_F18; break;
		}
		if (key) {
			input_event(input, usage->type, key, 1);
			last_key = key;
		} else
			input_event(input, usage->type, last_key, 0);

		return 1;
	}

	return 0;
}