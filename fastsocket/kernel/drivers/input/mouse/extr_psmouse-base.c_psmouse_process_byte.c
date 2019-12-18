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
struct psmouse {unsigned char* packet; scalar_t__ pktcnt; scalar_t__ pktsize; scalar_t__ type; struct input_dev* dev; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  psmouse_ret_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_EXTRA ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  BTN_SIDE ; 
 scalar_t__ PSMOUSE_CORTRON ; 
 int /*<<< orphan*/  PSMOUSE_FULL_PACKET ; 
 scalar_t__ PSMOUSE_GENPS ; 
 int /*<<< orphan*/  PSMOUSE_GOOD_DATA ; 
 scalar_t__ PSMOUSE_IMEX ; 
 scalar_t__ PSMOUSE_IMPS ; 
 scalar_t__ PSMOUSE_THINKPS ; 
 int /*<<< orphan*/  REL_HWHEEL ; 
 int /*<<< orphan*/  REL_WHEEL ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_report_rel (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static psmouse_ret_t psmouse_process_byte(struct psmouse *psmouse)
{
	struct input_dev *dev = psmouse->dev;
	unsigned char *packet = psmouse->packet;

	if (psmouse->pktcnt < psmouse->pktsize)
		return PSMOUSE_GOOD_DATA;

/*
 * Full packet accumulated, process it
 */

/*
 * Scroll wheel on IntelliMice, scroll buttons on NetMice
 */

	if (psmouse->type == PSMOUSE_IMPS || psmouse->type == PSMOUSE_GENPS)
		input_report_rel(dev, REL_WHEEL, -(signed char) packet[3]);

/*
 * Scroll wheel and buttons on IntelliMouse Explorer
 */

	if (psmouse->type == PSMOUSE_IMEX) {
		switch (packet[3] & 0xC0) {
			case 0x80: /* vertical scroll on IntelliMouse Explorer 4.0 */
				input_report_rel(dev, REL_WHEEL, (int) (packet[3] & 32) - (int) (packet[3] & 31));
				break;
			case 0x40: /* horizontal scroll on IntelliMouse Explorer 4.0 */
				input_report_rel(dev, REL_HWHEEL, (int) (packet[3] & 32) - (int) (packet[3] & 31));
				break;
			case 0x00:
			case 0xC0:
				input_report_rel(dev, REL_WHEEL, (int) (packet[3] & 8) - (int) (packet[3] & 7));
				input_report_key(dev, BTN_SIDE, (packet[3] >> 4) & 1);
				input_report_key(dev, BTN_EXTRA, (packet[3] >> 5) & 1);
				break;
		}
	}

/*
 * Extra buttons on Genius NewNet 3D
 */

	if (psmouse->type == PSMOUSE_GENPS) {
		input_report_key(dev, BTN_SIDE, (packet[0] >> 6) & 1);
		input_report_key(dev, BTN_EXTRA, (packet[0] >> 7) & 1);
	}

/*
 * Extra button on ThinkingMouse
 */
	if (psmouse->type == PSMOUSE_THINKPS) {
		input_report_key(dev, BTN_EXTRA, (packet[0] >> 3) & 1);
		/* Without this bit of weirdness moving up gives wildly high Y changes. */
		packet[1] |= (packet[0] & 0x40) << 1;
	}

/*
 * Cortron PS2 Trackball reports SIDE button on the 4th bit of the first
 * byte.
 */
	if (psmouse->type == PSMOUSE_CORTRON) {
		input_report_key(dev, BTN_SIDE, (packet[0] >> 3) & 1);
		packet[0] |= 0x08;
	}

/*
 * Generic PS/2 Mouse
 */

	input_report_key(dev, BTN_LEFT,    packet[0]       & 1);
	input_report_key(dev, BTN_MIDDLE, (packet[0] >> 2) & 1);
	input_report_key(dev, BTN_RIGHT,  (packet[0] >> 1) & 1);

	input_report_rel(dev, REL_X, packet[1] ? (int) packet[1] - (int) ((packet[0] << 4) & 0x100) : 0);
	input_report_rel(dev, REL_Y, packet[2] ? (int) ((packet[0] << 3) & 0x100) - (int) packet[2] : 0);

	input_sync(dev);

	return PSMOUSE_FULL_PACKET;
}