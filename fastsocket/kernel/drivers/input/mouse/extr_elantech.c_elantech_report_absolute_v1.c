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
struct psmouse {unsigned char* packet; struct elantech_data* private; struct input_dev* dev; } ;
struct input_dev {int dummy; } ;
struct elantech_data {int fw_version_maj; int capabilities; scalar_t__ jumpy_cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_BACK ; 
 int /*<<< orphan*/  BTN_FORWARD ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  BTN_TOOL_DOUBLETAP ; 
 int /*<<< orphan*/  BTN_TOOL_FINGER ; 
 int /*<<< orphan*/  BTN_TOOL_TRIPLETAP ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int ETP_CAP_HAS_ROCKER ; 
 unsigned char ETP_YMAX_V1 ; 
 int /*<<< orphan*/  elantech_debug (char*) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void elantech_report_absolute_v1(struct psmouse *psmouse)
{
	struct input_dev *dev = psmouse->dev;
	struct elantech_data *etd = psmouse->private;
	unsigned char *packet = psmouse->packet;
	int fingers;
	static int old_fingers;

	if (etd->fw_version_maj == 0x01) {
		/* byte 0:  D   U  p1  p2   1  p3   R   L
		   byte 1:  f   0  th  tw  x9  x8  y9  y8 */
		fingers = ((packet[1] & 0x80) >> 7) +
				((packet[1] & 0x30) >> 4);
	} else {
		/* byte 0: n1  n0  p2  p1   1  p3   R   L
		   byte 1:  0   0   0   0  x9  x8  y9  y8 */
		fingers = (packet[0] & 0xc0) >> 6;
	}

	if (etd->jumpy_cursor) {
		/* Discard packets that are likely to have bogus coordinates */
		if (fingers > old_fingers) {
			elantech_debug("elantech.c: discarding packet\n");
			goto discard_packet_v1;
		}
	}

	input_report_key(dev, BTN_TOUCH, fingers != 0);

	/* byte 2: x7  x6  x5  x4  x3  x2  x1  x0
	   byte 3: y7  y6  y5  y4  y3  y2  y1  y0 */
	if (fingers) {
		input_report_abs(dev, ABS_X,
			((packet[1] & 0x0c) << 6) | packet[2]);
		input_report_abs(dev, ABS_Y, ETP_YMAX_V1 -
			(((packet[1] & 0x03) << 8) | packet[3]));
	}

	input_report_key(dev, BTN_TOOL_FINGER, fingers == 1);
	input_report_key(dev, BTN_TOOL_DOUBLETAP, fingers == 2);
	input_report_key(dev, BTN_TOOL_TRIPLETAP, fingers == 3);
	input_report_key(dev, BTN_LEFT, packet[0] & 0x01);
	input_report_key(dev, BTN_RIGHT, packet[0] & 0x02);

	if ((etd->fw_version_maj == 0x01) &&
	    (etd->capabilities & ETP_CAP_HAS_ROCKER)) {
		/* rocker up */
		input_report_key(dev, BTN_FORWARD, packet[0] & 0x40);
		/* rocker down */
		input_report_key(dev, BTN_BACK, packet[0] & 0x80);
	}

	input_sync(dev);

 discard_packet_v1:
	old_fingers = fingers;
}