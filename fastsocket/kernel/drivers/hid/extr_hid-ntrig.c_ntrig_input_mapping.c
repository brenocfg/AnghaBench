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
struct hid_usage {int hid; } ;
struct hid_input {int /*<<< orphan*/  input; } ;
struct hid_field {int logical_maximum; int /*<<< orphan*/  logical_minimum; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_ORIENTATION ; 
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MINOR ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOOL_DOUBLETAP ; 
 int /*<<< orphan*/  EV_ABS ; 
#define  HID_DG_CONFIDENCE 139 
#define  HID_DG_CONTACTCOUNT 138 
#define  HID_DG_CONTACTID 137 
#define  HID_DG_CONTACTMAX 136 
#define  HID_DG_DEVICEINDEX 135 
#define  HID_DG_HEIGHT 134 
#define  HID_DG_INPUTMODE 133 
#define  HID_DG_WIDTH 132 
#define  HID_GD_X 131 
#define  HID_GD_Y 130 
#define  HID_UP_DIGITIZER 129 
#define  HID_UP_GENDESK 128 
 int HID_USAGE_PAGE ; 
 int /*<<< orphan*/  hid_map_usage (struct hid_input*,struct hid_usage*,unsigned long**,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_abs_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nt_map_key_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ntrig_input_mapping(struct hid_device *hdev, struct hid_input *hi,
		struct hid_field *field, struct hid_usage *usage,
		unsigned long **bit, int *max)
{
	switch (usage->hid & HID_USAGE_PAGE) {

	case HID_UP_GENDESK:
		switch (usage->hid) {
		case HID_GD_X:
			hid_map_usage(hi, usage, bit, max,
					EV_ABS, ABS_MT_POSITION_X);
			input_set_abs_params(hi->input, ABS_X,
					field->logical_minimum,
					field->logical_maximum, 0, 0);
			return 1;
		case HID_GD_Y:
			hid_map_usage(hi, usage, bit, max,
					EV_ABS, ABS_MT_POSITION_Y);
			input_set_abs_params(hi->input, ABS_Y,
					field->logical_minimum,
					field->logical_maximum, 0, 0);
			return 1;
		}
		return 0;

	case HID_UP_DIGITIZER:
		switch (usage->hid) {
		/* we do not want to map these for now */
		case HID_DG_CONTACTID: /* value is useless */
		case HID_DG_INPUTMODE:
		case HID_DG_DEVICEINDEX:
		case HID_DG_CONTACTCOUNT:
		case HID_DG_CONTACTMAX:
			return -1;

		/* original mapping by Rafi Rubin */
		case HID_DG_CONFIDENCE:
			nt_map_key_clear(BTN_TOOL_DOUBLETAP);
			return 1;

		/* width/height mapped on TouchMajor/TouchMinor/Orientation */
		case HID_DG_WIDTH:
			hid_map_usage(hi, usage, bit, max,
					EV_ABS, ABS_MT_TOUCH_MAJOR);
			return 1;
		case HID_DG_HEIGHT:
			hid_map_usage(hi, usage, bit, max,
					EV_ABS, ABS_MT_TOUCH_MINOR);
			input_set_abs_params(hi->input, ABS_MT_ORIENTATION,
					0, 1, 0, 0);
			return 1;
		}
		return 0;

	case 0xff000000:
		/* we do not want to map these: no input-oriented meaning */
		return -1;
	}

	return 0;
}