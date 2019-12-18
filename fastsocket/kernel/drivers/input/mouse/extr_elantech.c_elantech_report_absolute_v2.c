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
struct psmouse {unsigned char* packet; struct input_dev* dev; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_HAT0X ; 
 int /*<<< orphan*/  ABS_HAT0Y ; 
 int /*<<< orphan*/  ABS_HAT1X ; 
 int /*<<< orphan*/  ABS_HAT1Y ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  BTN_TOOL_DOUBLETAP ; 
 int /*<<< orphan*/  BTN_TOOL_FINGER ; 
 int /*<<< orphan*/  BTN_TOOL_TRIPLETAP ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  ETP_2FT_YMAX ; 
 int /*<<< orphan*/  ETP_YMAX_V2 ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void elantech_report_absolute_v2(struct psmouse *psmouse)
{
	struct input_dev *dev = psmouse->dev;
	unsigned char *packet = psmouse->packet;
	int fingers, x1, y1, x2, y2;

	/* byte 0: n1  n0   .   .   .   .   R   L */
	fingers = (packet[0] & 0xc0) >> 6;
	input_report_key(dev, BTN_TOUCH, fingers != 0);

	switch (fingers) {
	case 1:
		/* byte 1: x15 x14 x13 x12 x11 x10 x9  x8
		   byte 2: x7  x6  x5  x4  x4  x2  x1  x0 */
		input_report_abs(dev, ABS_X, (packet[1] << 8) | packet[2]);
		/* byte 4: y15 y14 y13 y12 y11 y10 y8  y8
		   byte 5: y7  y6  y5  y4  y3  y2  y1  y0 */
		input_report_abs(dev, ABS_Y, ETP_YMAX_V2 -
			((packet[4] << 8) | packet[5]));
		break;

	case 2:
		/* The coordinate of each finger is reported separately with
		   a lower resolution for two finger touches */
		/* byte 0:  .   .  ay8 ax8  .   .   .   .
		   byte 1: ax7 ax6 ax5 ax4 ax3 ax2 ax1 ax0 */
		x1 = ((packet[0] & 0x10) << 4) | packet[1];
		/* byte 2: ay7 ay6 ay5 ay4 ay3 ay2 ay1 ay0 */
		y1 = ETP_2FT_YMAX - (((packet[0] & 0x20) << 3) | packet[2]);
		/* byte 3:  .   .  by8 bx8  .   .   .   .
		   byte 4: bx7 bx6 bx5 bx4 bx3 bx2 bx1 bx0 */
		x2 = ((packet[3] & 0x10) << 4) | packet[4];
		/* byte 5: by7 by8 by5 by4 by3 by2 by1 by0 */
		y2 = ETP_2FT_YMAX - (((packet[3] & 0x20) << 3) | packet[5]);
		/* For compatibility with the X Synaptics driver scale up one
		   coordinate and report as ordinary mouse movent */
		input_report_abs(dev, ABS_X, x1 << 2);
		input_report_abs(dev, ABS_Y, y1 << 2);
		/* For compatibility with the proprietary X Elantech driver
		   report both coordinates as hat coordinates */
		input_report_abs(dev, ABS_HAT0X, x1);
		input_report_abs(dev, ABS_HAT0Y, y1);
		input_report_abs(dev, ABS_HAT1X, x2);
		input_report_abs(dev, ABS_HAT1Y, y2);
		break;
	}

	input_report_key(dev, BTN_TOOL_FINGER, fingers == 1);
	input_report_key(dev, BTN_TOOL_DOUBLETAP, fingers == 2);
	input_report_key(dev, BTN_TOOL_TRIPLETAP, fingers == 3);
	input_report_key(dev, BTN_LEFT, packet[0] & 0x01);
	input_report_key(dev, BTN_RIGHT, packet[0] & 0x02);

	input_sync(dev);
}