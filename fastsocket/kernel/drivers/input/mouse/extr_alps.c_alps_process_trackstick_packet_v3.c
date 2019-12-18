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
struct psmouse {unsigned char* packet; struct alps_data* private; } ;
struct input_dev {int dummy; } ;
struct alps_data {int quirks; struct input_dev* dev2; } ;
typedef  int s8 ;

/* Variables and functions */
 int ALPS_QUIRK_TRACKSTICK_BUTTONS ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_rel (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void alps_process_trackstick_packet_v3(struct psmouse *psmouse)
{
	struct alps_data *priv = psmouse->private;
	unsigned char *packet = psmouse->packet;
	struct input_dev *dev = priv->dev2;
	int x, y, z, left, right, middle;

	/* Sanity check packet */
	if (!(packet[0] & 0x40)) {
		dbg("Bad trackstick packet, discarding\n");
		return;
	}

	/*
	 * There's a special packet that seems to indicate the end
	 * of a stream of trackstick data. Filter these out.
	 */
	if (packet[1] == 0x7f && packet[2] == 0x7f && packet[4] == 0x7f)
		return;

	x = (s8)(((packet[0] & 0x20) << 2) | (packet[1] & 0x7f));
	y = (s8)(((packet[0] & 0x10) << 3) | (packet[2] & 0x7f));
	z = (packet[4] & 0x7c) >> 2;

	/*
	 * The x and y values tend to be quite large, and when used
	 * alone the trackstick is difficult to use. Scale them down
	 * to compensate.
	 */
	x /= 8;
	y /= 8;

	input_report_rel(dev, REL_X, x);
	input_report_rel(dev, REL_Y, -y);

	/*
	 * Most ALPS models report the trackstick buttons in the touchpad
	 * packets, but a few report them here. No reliable way has been
	 * found to differentiate between the models upfront, so we enable
	 * the quirk in response to seeing a button press in the trackstick
	 * packet.
	 */
	left = packet[3] & 0x01;
	right = packet[3] & 0x02;
	middle = packet[3] & 0x04;

	if (!(priv->quirks & ALPS_QUIRK_TRACKSTICK_BUTTONS) &&
	    (left || right || middle))
		priv->quirks |= ALPS_QUIRK_TRACKSTICK_BUTTONS;

	if (priv->quirks & ALPS_QUIRK_TRACKSTICK_BUTTONS) {
		input_report_key(dev, BTN_LEFT, left);
		input_report_key(dev, BTN_RIGHT, right);
		input_report_key(dev, BTN_MIDDLE, middle);
	}

	input_sync(dev);
	return;
}