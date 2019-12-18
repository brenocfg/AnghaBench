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
struct input_dev {int dummy; } ;
struct gc {int* pads; struct input_dev** dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int GC_MAX_DEVICES ; 
 size_t GC_NES ; 
 int GC_NES_LENGTH ; 
 size_t GC_SNES ; 
 size_t GC_SNESMOUSE ; 
 int GC_SNESMOUSE_LENGTH ; 
 int GC_SNES_LENGTH ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 size_t* gc_nes_bytes ; 
 int /*<<< orphan*/  gc_nes_read_packet (struct gc*,int,unsigned char*) ; 
 int /*<<< orphan*/ * gc_snes_btn ; 
 size_t* gc_snes_bytes ; 
 int* gc_status_bit ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_rel (struct input_dev*,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void gc_nes_process_packet(struct gc *gc)
{
	unsigned char data[GC_SNESMOUSE_LENGTH];
	struct input_dev *dev;
	int i, j, s, len;
	char x_rel, y_rel;

	len = gc->pads[GC_SNESMOUSE] ? GC_SNESMOUSE_LENGTH :
			(gc->pads[GC_SNES] ? GC_SNES_LENGTH : GC_NES_LENGTH);

	gc_nes_read_packet(gc, len, data);

	for (i = 0; i < GC_MAX_DEVICES; i++) {

		dev = gc->dev[i];
		if (!dev)
			continue;

		s = gc_status_bit[i];

		if (s & (gc->pads[GC_NES] | gc->pads[GC_SNES])) {
			input_report_abs(dev, ABS_X, !(s & data[6]) - !(s & data[7]));
			input_report_abs(dev, ABS_Y, !(s & data[4]) - !(s & data[5]));
		}

		if (s & gc->pads[GC_NES])
			for (j = 0; j < 4; j++)
				input_report_key(dev, gc_snes_btn[j], s & data[gc_nes_bytes[j]]);

		if (s & gc->pads[GC_SNES])
			for (j = 0; j < 8; j++)
				input_report_key(dev, gc_snes_btn[j], s & data[gc_snes_bytes[j]]);

		if (s & gc->pads[GC_SNESMOUSE]) {
			/*
			 * The 4 unused bits from SNES controllers appear to be ID bits
			 * so use them to make sure iwe are dealing with a mouse.
			 * gamepad is connected. This is important since
			 * my SNES gamepad sends 1's for bits 16-31, which
			 * cause the mouse pointer to quickly move to the
			 * upper left corner of the screen.
			 */
			if (!(s & data[12]) && !(s & data[13]) &&
			    !(s & data[14]) && (s & data[15])) {
				input_report_key(dev, BTN_LEFT, s & data[9]);
				input_report_key(dev, BTN_RIGHT, s & data[8]);

				x_rel = y_rel = 0;
				for (j = 0; j < 7; j++) {
					x_rel <<= 1;
					if (data[25 + j] & s)
						x_rel |= 1;

					y_rel <<= 1;
					if (data[17 + j] & s)
						y_rel |= 1;
				}

				if (x_rel) {
					if (data[24] & s)
						x_rel = -x_rel;
					input_report_rel(dev, REL_X, x_rel);
				}

				if (y_rel) {
					if (data[16] & s)
						y_rel = -y_rel;
					input_report_rel(dev, REL_Y, y_rel);
				}
			}
		}
		input_sync(dev);
	}
}