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
struct ntrig_data {int pen_active; int finger_active; int inverted; int x; int reading_a_point; int y; int id; int found_contact_id; int w; int h; } ;
struct input_dev {int dummy; } ;
struct hid_usage {int hid; } ;
struct hid_field {int application; TYPE_1__* hidinput; } ;
struct hid_device {int claimed; int /*<<< orphan*/  (* hiddev_hid_event ) (struct hid_device*,struct hid_field*,struct hid_usage*,int) ;} ;
typedef  int __s32 ;
struct TYPE_2__ {struct input_dev* input; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_ORIENTATION ; 
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MINOR ; 
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOOL_DOUBLETAP ; 
 int /*<<< orphan*/  BTN_TOOL_PEN ; 
 int /*<<< orphan*/  BTN_TOOL_RUBBER ; 
 int /*<<< orphan*/  EV_ABS ; 
 int HID_CLAIMED_HIDDEV ; 
 int HID_CLAIMED_INPUT ; 
#define  HID_DG_CONTACTID 135 
#define  HID_DG_HEIGHT 134 
#define  HID_DG_INRANGE 133 
#define  HID_DG_INVERT 132 
#define  HID_DG_TIPPRESSURE 131 
#define  HID_DG_WIDTH 130 
#define  HID_GD_X 129 
#define  HID_GD_Y 128 
 struct ntrig_data* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_sync (struct input_dev*) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct hid_device*,struct hid_field*,struct hid_usage*,int) ; 

__attribute__((used)) static int ntrig_event (struct hid_device *hid, struct hid_field *field,
		                        struct hid_usage *usage, __s32 value)
{
	struct input_dev *input = field->hidinput->input;
	struct ntrig_data *nd = hid_get_drvdata(hid);

        if (hid->claimed & HID_CLAIMED_INPUT) {
		switch (usage->hid) {

		case HID_DG_INRANGE:
			if (field->application & 0x3)
				nd->pen_active = (value != 0);
			else
				nd->finger_active = (value != 0);
			return 0;

		case HID_DG_INVERT:
			nd->inverted = value;
			return 0;

		case HID_GD_X:
			nd->x = value;
			nd->reading_a_point = 1;
			break;
		case HID_GD_Y:
			nd->y = value;
			break;
		case HID_DG_CONTACTID:
			nd->id = value;
			/* we receive this only when in multitouch mode */
			nd->found_contact_id = 1;
			break;
		case HID_DG_WIDTH:
			nd->w = value;
			break;
		case HID_DG_HEIGHT:
			nd->h = value;
			/*
			 * when in single touch mode, this is the last
			 * report received in a finger event. We want
			 * to emit a normal (X, Y) position
			 */
			if (!nd->found_contact_id) {
				if (nd->pen_active && nd->finger_active) {
					input_report_key(input, BTN_TOOL_DOUBLETAP, 0);
					input_report_key(input, BTN_TOOL_DOUBLETAP, 1);
				}
				input_event(input, EV_ABS, ABS_X, nd->x);
				input_event(input, EV_ABS, ABS_Y, nd->y);
			}
			break;
		case HID_DG_TIPPRESSURE:
			/*
			 * when in single touch mode, this is the last
			 * report received in a pen event. We want
			 * to emit a normal (X, Y) position
			 */
			if (! nd->found_contact_id) {
				if (nd->pen_active && nd->finger_active) {
					input_report_key(input,
							nd->inverted ? BTN_TOOL_RUBBER : BTN_TOOL_PEN
							, 0);
					input_report_key(input,
							nd->inverted ? BTN_TOOL_RUBBER : BTN_TOOL_PEN
							, 1);
				}
				input_event(input, EV_ABS, ABS_X, nd->x);
				input_event(input, EV_ABS, ABS_Y, nd->y);
				input_event(input, EV_ABS, ABS_PRESSURE, value);
			}
			break;
		case 0xff000002:
			/*
			 * we receive this when the device is in multitouch
			 * mode. The first of the three values tagged with
			 * this usage tells if the contact point is real
			 * or a placeholder
			 */
			if (!nd->reading_a_point || value != 1)
				break;
			/* emit a normal (X, Y) for the first point only */
			if (nd->id == 0) {
				input_event(input, EV_ABS, ABS_X, nd->x);
				input_event(input, EV_ABS, ABS_Y, nd->y);
			}
			input_event(input, EV_ABS, ABS_MT_POSITION_X, nd->x);
			input_event(input, EV_ABS, ABS_MT_POSITION_Y, nd->y);
			if (nd->w > nd->h) {
				input_event(input, EV_ABS,
						ABS_MT_ORIENTATION, 1);
				input_event(input, EV_ABS,
						ABS_MT_TOUCH_MAJOR, nd->w);
				input_event(input, EV_ABS,
						ABS_MT_TOUCH_MINOR, nd->h);
			} else {
				input_event(input, EV_ABS,
						ABS_MT_ORIENTATION, 0);
				input_event(input, EV_ABS,
						ABS_MT_TOUCH_MAJOR, nd->h);
				input_event(input, EV_ABS,
						ABS_MT_TOUCH_MINOR, nd->w);
			}
			input_mt_sync(field->hidinput->input);
			nd->reading_a_point = 0;
			nd->found_contact_id = 0;
			break;

		default:
			/* fallback to the generic hidinput handling */
			return 0;
		}
	}

	/* we have handled the hidinput part, now remains hiddev */
        if (hid->claimed & HID_CLAIMED_HIDDEV && hid->hiddev_hid_event)
                hid->hiddev_hid_event(hid, field, usage, value);

	return 1;
}