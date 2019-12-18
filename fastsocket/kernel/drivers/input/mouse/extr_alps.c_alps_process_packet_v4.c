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
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  BTN_TOOL_FINGER ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void alps_process_packet_v4(struct psmouse *psmouse)
{
	unsigned char *packet = psmouse->packet;
	struct input_dev *dev = psmouse->dev;
	int x, y, z;
	int left, right;

	left = packet[4] & 0x01;
	right = packet[4] & 0x02;

	x = ((packet[1] & 0x7f) << 4) | ((packet[3] & 0x30) >> 2) |
	    ((packet[0] & 0x30) >> 4);
	y = ((packet[2] & 0x7f) << 4) | (packet[3] & 0x0f);
	z = packet[5] & 0x7f;

	if (z >= 64)
		input_report_key(dev, BTN_TOUCH, 1);
	else
		input_report_key(dev, BTN_TOUCH, 0);

	if (z > 0) {
		input_report_abs(dev, ABS_X, x);
		input_report_abs(dev, ABS_Y, y);
	}
	input_report_abs(dev, ABS_PRESSURE, z);

	input_report_key(dev, BTN_TOOL_FINGER, z > 0);
	input_report_key(dev, BTN_LEFT, left);
	input_report_key(dev, BTN_RIGHT, right);

	input_sync(dev);
}