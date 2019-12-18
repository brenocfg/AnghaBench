#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wacom_wac {unsigned char* data; int* id; int /*<<< orphan*/ * tool; TYPE_2__* features; } ;
struct wacom_combo {TYPE_1__* wacom; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_4__ {unsigned char distance_max; } ;
struct TYPE_3__ {struct input_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_DISTANCE ; 
 int /*<<< orphan*/  ABS_MISC ; 
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_STYLUS ; 
 int /*<<< orphan*/  BTN_STYLUS2 ; 
 int /*<<< orphan*/  BTN_TOOL_PEN ; 
 int /*<<< orphan*/  BTN_TOOL_RUBBER ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int ERASER_DEVICE_ID ; 
 int STYLUS_DEVICE_ID ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int le16_to_cpup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wacom_bpt_pen(struct wacom_wac *wacom, struct wacom_combo *wcombo)
{
	struct input_dev *input = wcombo->wacom->dev;
	unsigned char *data = wacom->data;
	int prox = 0, x = 0, y = 0, p = 0, d = 0, pen = 0, btn1 = 0, btn2 = 0;

	if (data[0] != 0x02)
	    return 0;

	prox = (data[1] & 0x20) == 0x20;

	/*
	 * All reports shared between PEN and RUBBER tool must be
	 * forced to a known starting value (zero) when transitioning to
	 * out-of-prox.
	 *
	 * If not reset then, to userspace, it will look like lost events
	 * if new tool comes in-prox with same values as previous tool sent.
	 *
	 * Hardware does report zero in most out-of-prox cases but not all.
	 */
	if (prox) {
		if (!wacom->tool[0]) {
			if (data[1] & 0x08) {
				wacom->tool[0] = BTN_TOOL_RUBBER;
				wacom->id[0] = ERASER_DEVICE_ID;
			} else {
				wacom->tool[0] = BTN_TOOL_PEN;
				wacom->id[0] = STYLUS_DEVICE_ID;
			}
		}
		x = le16_to_cpup((__le16 *)&data[2]);
		y = le16_to_cpup((__le16 *)&data[4]);
		p = le16_to_cpup((__le16 *)&data[6]);
		/*
		 * Convert distance from out prox to distance from tablet.
		 * distance will be greater than distance_max once
		 * touching and applying pressure; do not report negative
		 * distance.
		 */
		if (data[8] <= wacom->features->distance_max)
			d = wacom->features->distance_max - data[8];

		pen = data[1] & 0x01;
		btn1 = data[1] & 0x02;
		btn2 = data[1] & 0x04;
	}

	input_report_key(input, BTN_TOUCH, pen);
	input_report_key(input, BTN_STYLUS, btn1);
	input_report_key(input, BTN_STYLUS2, btn2);

	input_report_abs(input, ABS_X, x);
	input_report_abs(input, ABS_Y, y);
	input_report_abs(input, ABS_PRESSURE, p);
	input_report_abs(input, ABS_DISTANCE, d);

	if (!prox)
		wacom->id[0] = 0;

	input_report_key(input, wacom->tool[0], prox); /* PEN or RUBBER */
	input_report_abs(input, ABS_MISC, wacom->id[0]); /* TOOL ID */

	if (!prox)
		wacom->tool[0] = 0;

	return 1;

}