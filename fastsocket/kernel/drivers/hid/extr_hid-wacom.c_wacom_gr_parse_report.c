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
struct wacom_data {int tool; int butstate; } ;
struct input_dev {unsigned char* absmax; } ;
struct hid_device {int dummy; } ;
typedef  int __u16 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 size_t ABS_DISTANCE ; 
 size_t ABS_PRESSURE ; 
 size_t ABS_X ; 
 size_t ABS_Y ; 
 int BTN_0 ; 
 int BTN_1 ; 
 int BTN_LEFT ; 
 int BTN_MIDDLE ; 
 int BTN_RIGHT ; 
 int BTN_STYLUS ; 
 int BTN_STYLUS2 ; 
 int BTN_TOOL_FINGER ; 
 int BTN_TOOL_MOUSE ; 
 int BTN_TOOL_PEN ; 
 int BTN_TOOL_RUBBER ; 
 int BTN_TOUCH ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  MSC_SERIAL ; 
 int /*<<< orphan*/  REL_WHEEL ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,size_t,unsigned char) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int,int) ; 
 int /*<<< orphan*/  input_report_rel (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wacom_gr_parse_report(struct hid_device *hdev,
			struct wacom_data *wdata,
			struct input_dev *input, unsigned char *data)
{
	int tool, x, y, rw;

	tool = 0;
	/* Get X & Y positions */
	x = le16_to_cpu(*(__le16 *) &data[2]);
	y = le16_to_cpu(*(__le16 *) &data[4]);

	/* Get current tool identifier */
	if (data[1] & 0x90) { /* If pen is in the in/active area */
		switch ((data[1] >> 5) & 3) {
		case 0:	/* Pen */
			tool = BTN_TOOL_PEN;
			break;

		case 1: /* Rubber */
			tool = BTN_TOOL_RUBBER;
			break;

		case 2: /* Mouse with wheel */
		case 3: /* Mouse without wheel */
			tool = BTN_TOOL_MOUSE;
			break;
		}

		/* Reset tool if out of active tablet area */
		if (!(data[1] & 0x10))
			tool = 0;
	}

	/* If tool changed, notify input subsystem */
	if (wdata->tool != tool) {
		if (wdata->tool) {
			/* Completely reset old tool state */
			if (wdata->tool == BTN_TOOL_MOUSE) {
				input_report_key(input, BTN_LEFT, 0);
				input_report_key(input, BTN_RIGHT, 0);
				input_report_key(input, BTN_MIDDLE, 0);
				input_report_abs(input, ABS_DISTANCE,
						input->absmax[ABS_DISTANCE]);
			} else {
				input_report_key(input, BTN_TOUCH, 0);
				input_report_key(input, BTN_STYLUS, 0);
				input_report_key(input, BTN_STYLUS2, 0);
				input_report_abs(input, ABS_PRESSURE, 0);
			}
			input_report_key(input, wdata->tool, 0);
			input_sync(input);
		}
		wdata->tool = tool;
		if (tool)
			input_report_key(input, tool, 1);
	}

	if (tool) {
		input_report_abs(input, ABS_X, x);
		input_report_abs(input, ABS_Y, y);

		switch ((data[1] >> 5) & 3) {
		case 2: /* Mouse with wheel */
			input_report_key(input, BTN_MIDDLE, data[1] & 0x04);
			rw = (data[6] & 0x01) ? -1 :
				(data[6] & 0x02) ? 1 : 0;
			input_report_rel(input, REL_WHEEL, rw);
			/* fall through */

		case 3: /* Mouse without wheel */
			input_report_key(input, BTN_LEFT, data[1] & 0x01);
			input_report_key(input, BTN_RIGHT, data[1] & 0x02);
			/* Compute distance between mouse and tablet */
			rw = 44 - (data[6] >> 2);
			if (rw < 0)
				rw = 0;
			else if (rw > 31)
				rw = 31;
			input_report_abs(input, ABS_DISTANCE, rw);
			break;

		default:
			input_report_abs(input, ABS_PRESSURE,
					data[6] | (((__u16) (data[1] & 0x08)) << 5));
			input_report_key(input, BTN_TOUCH, data[1] & 0x01);
			input_report_key(input, BTN_STYLUS, data[1] & 0x02);
			input_report_key(input, BTN_STYLUS2, (tool == BTN_TOOL_PEN) && data[1] & 0x04);
			break;
		}

		input_sync(input);
	}

	/* Report the state of the two buttons at the top of the tablet
	 * as two extra fingerpad keys (buttons 4 & 5). */
	rw = data[7] & 0x03;
	if (rw != wdata->butstate) {
		wdata->butstate = rw;
		input_report_key(input, BTN_0, rw & 0x02);
		input_report_key(input, BTN_1, rw & 0x01);
		input_report_key(input, BTN_TOOL_FINGER, 0xf0);
		input_event(input, EV_MSC, MSC_SERIAL, 0xf0);
		input_sync(input);
	}

	return 1;
}