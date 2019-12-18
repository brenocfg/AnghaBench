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
struct wacom_wac {unsigned char* data; unsigned char* serial; unsigned char* id; scalar_t__* tool; TYPE_1__* features; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_DISTANCE ; 
 int /*<<< orphan*/  ABS_MISC ; 
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_RZ ; 
 int /*<<< orphan*/  ABS_THROTTLE ; 
 int /*<<< orphan*/  ABS_TILT_X ; 
 int /*<<< orphan*/  ABS_TILT_Y ; 
 int /*<<< orphan*/  ABS_WHEEL ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  ABS_Z ; 
 scalar_t__ BTN_EXTRA ; 
 scalar_t__ BTN_LEFT ; 
 scalar_t__ BTN_MIDDLE ; 
 scalar_t__ BTN_RIGHT ; 
 scalar_t__ BTN_SIDE ; 
 scalar_t__ BTN_STYLUS ; 
 scalar_t__ BTN_STYLUS2 ; 
 scalar_t__ BTN_TOOL_AIRBRUSH ; 
 scalar_t__ BTN_TOOL_BRUSH ; 
 scalar_t__ BTN_TOOL_LENS ; 
 scalar_t__ BTN_TOOL_MOUSE ; 
 void* BTN_TOOL_PEN ; 
 scalar_t__ BTN_TOOL_PENCIL ; 
 scalar_t__ BTN_TOOL_RUBBER ; 
 scalar_t__ BTN_TOUCH ; 
 int /*<<< orphan*/  EV_MSC ; 
 scalar_t__ INTUOS ; 
 scalar_t__ INTUOS3S ; 
 int /*<<< orphan*/  MSC_SERIAL ; 
 scalar_t__ WACOM_21UX2 ; 
 scalar_t__ WACOM_24HD ; 
 int /*<<< orphan*/  wacom_input_event (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  wacom_report_abs (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wacom_report_key (void*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wacom_intuos_inout(struct wacom_wac *wacom, void *wcombo)
{
	unsigned char *data = wacom->data;
	int idx = 0;

	/* tool number */
	if (wacom->features->type == INTUOS)
		idx = data[1] & 0x01;

	/* Enter report */
	if ((data[1] & 0xfc) == 0xc0) {
		/* serial number of the tool */
		wacom->serial[idx] = ((data[3] & 0x0f) << 28) +
			(data[4] << 20) + (data[5] << 12) +
			(data[6] << 4) + (data[7] >> 4);

		wacom->id[idx] = (data[2] << 4) | (data[3] >> 4) |
			((data[7] & 0x0f) << 20) | ((data[8] & 0xf0) << 12);

		switch (wacom->id[idx] & 0xfffff) {
			case 0x812: /* Inking pen */
			case 0x801: /* Intuos3 Inking pen */
			case 0x20802: /* Intuos4 Classic Pen */
			case 0x012:
				wacom->tool[idx] = BTN_TOOL_PENCIL;
				break;
			case 0x822: /* Pen */
			case 0x842:
			case 0x852:
			case 0x823: /* Intuos3 Grip Pen */
			case 0x813: /* Intuos3 Classic Pen */
			case 0x885: /* Intuos3 Marker Pen */
			case 0x802: /* Intuos4 General Pen Eraser */
			case 0x804: /* Intuos4 Marker Pen */
			case 0x40802: /* Intuos4 Inking Pen */
			case 0x022:
				wacom->tool[idx] = BTN_TOOL_PEN;
				break;
			case 0x832: /* Stroke pen */
			case 0x032:
				wacom->tool[idx] = BTN_TOOL_BRUSH;
				break;
			case 0x007: /* Mouse 4D and 2D */
		        case 0x09c:
			case 0x094:
			case 0x017: /* Intuos3 2D Mouse */
			case 0x806: /* Intuos4 Mouse */
				wacom->tool[idx] = BTN_TOOL_MOUSE;
				break;
			case 0x096: /* Lens cursor */
			case 0x097: /* Intuos3 Lens cursor */
			case 0x006: /* Intuos4 Lens cursor */
				wacom->tool[idx] = BTN_TOOL_LENS;
				break;
			case 0x82a: /* Eraser */
			case 0x85a:
		        case 0x91a:
			case 0xd1a:
			case 0x0fa:
			case 0x82b: /* Intuos3 Grip Pen Eraser */
			case 0x81b: /* Intuos3 Classic Pen Eraser */
			case 0x91b: /* Intuos3 Airbrush Eraser */
			case 0x80c: /* Intuos4 Marker Pen Eraser */
			case 0x80a: /* Intuos4 General Pen Eraser */
			case 0x4080a: /* Intuos4 Classic Pen Eraser */
			case 0x90a: /* Intuos4 Airbrush Eraser */
				wacom->tool[idx] = BTN_TOOL_RUBBER;
				break;
			case 0xd12:
			case 0x912:
			case 0x112:
			case 0x913: /* Intuos3 Airbrush */
			case 0x902: /* Intuos4 Airbrush */
				wacom->tool[idx] = BTN_TOOL_AIRBRUSH;
				break;
			default: /* Unknown tool */
				wacom->tool[idx] = BTN_TOOL_PEN;
		}
		return 1;
	}

	/* older I4 styli don't work with new Cintiqs */
	if (!((wacom->id[idx] >> 20) & 0x01) &&
			(wacom->features->type >= WACOM_21UX2 &&
			 wacom->features->type <= WACOM_24HD))
		return 1;

	/* Exit report */
	if ((data[1] & 0xfe) == 0x80) {
		/*
		 * Reset all states otherwise we lose the initial states
		 * when in-prox next time
		 */
		wacom_report_abs(wcombo, ABS_X, 0);
		wacom_report_abs(wcombo, ABS_Y, 0);
		wacom_report_abs(wcombo, ABS_DISTANCE, 0);
		wacom_report_abs(wcombo, ABS_TILT_X, 0);
		wacom_report_abs(wcombo, ABS_TILT_Y, 0);
		if (wacom->tool[idx] >= BTN_TOOL_MOUSE) {
			wacom_report_key(wcombo, BTN_LEFT, 0);
			wacom_report_key(wcombo, BTN_MIDDLE, 0);
			wacom_report_key(wcombo, BTN_RIGHT, 0);
			wacom_report_key(wcombo, BTN_SIDE, 0);
			wacom_report_key(wcombo, BTN_EXTRA, 0);
			wacom_report_abs(wcombo, ABS_THROTTLE, 0);
			wacom_report_abs(wcombo, ABS_RZ, 0);
		} else {
			wacom_report_abs(wcombo, ABS_PRESSURE, 0);
			wacom_report_key(wcombo, BTN_STYLUS, 0);
			wacom_report_key(wcombo, BTN_STYLUS2, 0);
			wacom_report_key(wcombo, BTN_TOUCH, 0);
			wacom_report_abs(wcombo, ABS_WHEEL, 0);
			if (wacom->features->type >= INTUOS3S)
				wacom_report_abs(wcombo, ABS_Z, 0);
		}
		wacom_report_key(wcombo, wacom->tool[idx], 0);
		wacom_report_abs(wcombo, ABS_MISC, 0); /* reset tool id */
		wacom_input_event(wcombo, EV_MSC, MSC_SERIAL, wacom->serial[idx]);
		wacom->id[idx] = 0;
		return 2;
	}
	return 0;
}