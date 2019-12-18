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
struct wacom_wac {unsigned char* data; scalar_t__* tool; unsigned char* id; TYPE_1__* features; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_DISTANCE ; 
 int /*<<< orphan*/  ABS_MISC ; 
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_WHEEL ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 scalar_t__ BTN_0 ; 
 scalar_t__ BTN_1 ; 
 scalar_t__ BTN_4 ; 
 scalar_t__ BTN_5 ; 
 scalar_t__ BTN_LEFT ; 
 scalar_t__ BTN_MIDDLE ; 
 scalar_t__ BTN_RIGHT ; 
 scalar_t__ BTN_STYLUS ; 
 scalar_t__ BTN_STYLUS2 ; 
 scalar_t__ BTN_TOOL_FINGER ; 
 scalar_t__ BTN_TOOL_MOUSE ; 
 scalar_t__ BTN_TOOL_PEN ; 
 scalar_t__ BTN_TOOL_RUBBER ; 
 scalar_t__ BTN_TOUCH ; 
 unsigned char CURSOR_DEVICE_ID ; 
 unsigned char ERASER_DEVICE_ID ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  MSC_SERIAL ; 
 void* PAD_DEVICE_ID ; 
 int /*<<< orphan*/  REL_WHEEL ; 
 unsigned char STYLUS_DEVICE_ID ; 
#define  WACOM_G4 129 
#define  WACOM_MO 128 
 int /*<<< orphan*/  dbg (char*,unsigned char) ; 
 int /*<<< orphan*/  wacom_input_event (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wacom_input_sync (void*) ; 
 int wacom_le16_to_cpu (unsigned char*) ; 
 int /*<<< orphan*/  wacom_report_abs (void*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  wacom_report_key (void*,scalar_t__,unsigned char) ; 
 int /*<<< orphan*/  wacom_report_rel (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wacom_graphire_irq(struct wacom_wac *wacom, void *wcombo)
{
	unsigned char *data = wacom->data;
	int x, y, rw;

	if (data[0] != 2) {
		dbg("wacom_graphire_irq: received unknown report #%d", data[0]);
		return 0;
	}

	if (data[1] & 0x80) {
		/* in prox and not a pad data */

		switch ((data[1] >> 5) & 3) {

			case 0:	/* Pen */
				wacom->tool[0] = BTN_TOOL_PEN;
				wacom->id[0] = STYLUS_DEVICE_ID;
				break;

			case 1: /* Rubber */
				wacom->tool[0] = BTN_TOOL_RUBBER;
				wacom->id[0] = ERASER_DEVICE_ID;
				break;

			case 2: /* Mouse with wheel */
				wacom_report_key(wcombo, BTN_MIDDLE, data[1] & 0x04);
				if (wacom->features->type == WACOM_G4 ||
						wacom->features->type == WACOM_MO) {
					rw = data[7] & 0x04 ? (data[7] & 0x03)-4 : (data[7] & 0x03);
					wacom_report_rel(wcombo, REL_WHEEL, -rw);
				} else
					wacom_report_rel(wcombo, REL_WHEEL, -(signed char) data[6]);
				/* fall through */

			case 3: /* Mouse without wheel */
				wacom->tool[0] = BTN_TOOL_MOUSE;
				wacom->id[0] = CURSOR_DEVICE_ID;
				wacom_report_key(wcombo, BTN_LEFT, data[1] & 0x01);
				wacom_report_key(wcombo, BTN_RIGHT, data[1] & 0x02);
				if (wacom->features->type == WACOM_G4 ||
						wacom->features->type == WACOM_MO)
					wacom_report_abs(wcombo, ABS_DISTANCE, data[6] & 0x3f);
				else
					wacom_report_abs(wcombo, ABS_DISTANCE, data[7] & 0x3f);
				break;
		}
		x = wacom_le16_to_cpu(&data[2]);
		y = wacom_le16_to_cpu(&data[4]);
		wacom_report_abs(wcombo, ABS_X, x);
		wacom_report_abs(wcombo, ABS_Y, y);
		if (wacom->tool[0] != BTN_TOOL_MOUSE) {
			wacom_report_abs(wcombo, ABS_PRESSURE, data[6] | ((data[7] & 0x01) << 8));
			wacom_report_key(wcombo, BTN_TOUCH, data[1] & 0x01);
			wacom_report_key(wcombo, BTN_STYLUS, data[1] & 0x02);
			wacom_report_key(wcombo, BTN_STYLUS2, data[1] & 0x04);
		}
		wacom_report_abs(wcombo, ABS_MISC, wacom->id[0]); /* report tool id */
		wacom_report_key(wcombo, wacom->tool[0], 1);
	} else if (wacom->id[0]) {
		wacom_report_abs(wcombo, ABS_X, 0);
		wacom_report_abs(wcombo, ABS_Y, 0);
		if (wacom->tool[0] == BTN_TOOL_MOUSE) {
			wacom_report_key(wcombo, BTN_LEFT, 0);
			wacom_report_key(wcombo, BTN_RIGHT, 0);
			wacom_report_abs(wcombo, ABS_DISTANCE, 0);
		} else {
			wacom_report_abs(wcombo, ABS_PRESSURE, 0);
			wacom_report_key(wcombo, BTN_TOUCH, 0);
			wacom_report_key(wcombo, BTN_STYLUS, 0);
			wacom_report_key(wcombo, BTN_STYLUS2, 0);
		}
		wacom->id[0] = 0;
		wacom_report_abs(wcombo, ABS_MISC, 0); /* reset tool id */
		wacom_report_key(wcombo, wacom->tool[0], 0);
	}

	/* send pad data */
	switch (wacom->features->type) {
	    case WACOM_G4:
		if (data[7] & 0xf8) {
			wacom_input_sync(wcombo); /* sync last event */
			wacom->id[1] = PAD_DEVICE_ID;
			wacom_report_key(wcombo, BTN_0, (data[7] & 0x40));
			wacom_report_key(wcombo, BTN_4, (data[7] & 0x80));
			rw = ((data[7] & 0x18) >> 3) - ((data[7] & 0x20) >> 3);
			wacom_report_rel(wcombo, REL_WHEEL, rw);
			wacom_report_key(wcombo, BTN_TOOL_FINGER, 0xf0);
			wacom_report_abs(wcombo, ABS_MISC, wacom->id[1]);
			wacom_input_event(wcombo, EV_MSC, MSC_SERIAL, 0xf0);
		} else if (wacom->id[1]) {
			wacom_input_sync(wcombo); /* sync last event */
			wacom->id[1] = 0;
			wacom_report_key(wcombo, BTN_0, (data[7] & 0x40));
			wacom_report_key(wcombo, BTN_4, (data[7] & 0x80));
			wacom_report_key(wcombo, BTN_TOOL_FINGER, 0);
			wacom_report_abs(wcombo, ABS_MISC, 0);
			wacom_input_event(wcombo, EV_MSC, MSC_SERIAL, 0xf0);
		}
		break;
	    case WACOM_MO:
		if ((data[7] & 0xf8) || (data[8] & 0xff)) {
			wacom_input_sync(wcombo); /* sync last event */
			wacom->id[1] = PAD_DEVICE_ID;
			wacom_report_key(wcombo, BTN_0, (data[7] & 0x08));
			wacom_report_key(wcombo, BTN_1, (data[7] & 0x20));
			wacom_report_key(wcombo, BTN_4, (data[7] & 0x10));
			wacom_report_key(wcombo, BTN_5, (data[7] & 0x40));
			wacom_report_abs(wcombo, ABS_WHEEL, (data[8] & 0x7f));
			wacom_report_key(wcombo, BTN_TOOL_FINGER, 0xf0);
			wacom_report_abs(wcombo, ABS_MISC, wacom->id[1]);
			wacom_input_event(wcombo, EV_MSC, MSC_SERIAL, 0xf0);
		} else if (wacom->id[1]) {
			wacom_input_sync(wcombo); /* sync last event */
			wacom->id[1] = 0;
			wacom_report_key(wcombo, BTN_0, (data[7] & 0x08));
			wacom_report_key(wcombo, BTN_1, (data[7] & 0x20));
			wacom_report_key(wcombo, BTN_4, (data[7] & 0x10));
			wacom_report_key(wcombo, BTN_5, (data[7] & 0x40));
			wacom_report_abs(wcombo, ABS_WHEEL, (data[8] & 0x7f));
			wacom_report_key(wcombo, BTN_TOOL_FINGER, 0);
			wacom_report_abs(wcombo, ABS_MISC, 0);
			wacom_input_event(wcombo, EV_MSC, MSC_SERIAL, 0xf0);
		}
		break;
	}
	return 1;
}