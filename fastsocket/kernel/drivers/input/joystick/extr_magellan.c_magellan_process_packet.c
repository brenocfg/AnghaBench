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
struct magellan {unsigned char* data; int idx; struct input_dev* dev; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/ * magellan_axes ; 
 int /*<<< orphan*/ * magellan_buttons ; 
 int /*<<< orphan*/  magellan_crunch_nibbles (unsigned char*,int) ; 

__attribute__((used)) static void magellan_process_packet(struct magellan* magellan)
{
	struct input_dev *dev = magellan->dev;
	unsigned char *data = magellan->data;
	int i, t;

	if (!magellan->idx) return;

	switch (magellan->data[0]) {

		case 'd':				/* Axis data */
			if (magellan->idx != 25) return;
			if (magellan_crunch_nibbles(data, 24)) return;
			for (i = 0; i < 6; i++)
				input_report_abs(dev, magellan_axes[i],
					(data[(i << 2) + 1] << 12 | data[(i << 2) + 2] << 8 |
					 data[(i << 2) + 3] <<  4 | data[(i << 2) + 4]) - 32768);
			break;

		case 'k':				/* Button data */
			if (magellan->idx != 4) return;
			if (magellan_crunch_nibbles(data, 3)) return;
			t = (data[1] << 1) | (data[2] << 5) | data[3];
			for (i = 0; i < 9; i++) input_report_key(dev, magellan_buttons[i], (t >> i) & 1);
			break;
	}

	input_sync(dev);
}