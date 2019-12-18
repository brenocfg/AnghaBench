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
struct h3600_dev {int event; int* buf; int /*<<< orphan*/  len; struct input_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int BTN_TOUCH ; 
#define  H3600_SCANCODE_CALENDAR 138 
#define  H3600_SCANCODE_CONTACTS 137 
#define  H3600_SCANCODE_DOWN 136 
#define  H3600_SCANCODE_LEFT 135 
#define  H3600_SCANCODE_Q 134 
#define  H3600_SCANCODE_RECORD 133 
#define  H3600_SCANCODE_RIGHT 132 
#define  H3600_SCANCODE_START 131 
#define  H3600_SCANCODE_UP 130 
#define  KEYBD_ID 129 
 int KEY_DOWN ; 
 int KEY_LEFT ; 
 int KEY_PROG1 ; 
 int KEY_PROG2 ; 
 int KEY_PROG3 ; 
 int KEY_Q ; 
 int KEY_RECORD ; 
 int KEY_RIGHT ; 
 int KEY_UP ; 
#define  TOUCHS_ID 128 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void h3600ts_process_packet(struct h3600_dev *ts)
{
	struct input_dev *dev = ts->dev;
	static int touched = 0;
	int key, down = 0;

	switch (ts->event) {
		/*
		   Buttons - returned as a single byte
			7 6 5 4 3 2 1 0
			S x x x N N N N

		   S       switch state ( 0=pressed 1=released)
		   x       Unused.
		   NNNN    switch number 0-15

		   Note: This is true for non interrupt generated key events.
		*/
		case KEYBD_ID:
			down = (ts->buf[0] & 0x80) ? 0 : 1;

			switch (ts->buf[0] & 0x7f) {
				case H3600_SCANCODE_RECORD:
					key = KEY_RECORD;
					break;
				case H3600_SCANCODE_CALENDAR:
					key = KEY_PROG1;
                                        break;
				case H3600_SCANCODE_CONTACTS:
					key = KEY_PROG2;
					break;
				case H3600_SCANCODE_Q:
					key = KEY_Q;
					break;
				case H3600_SCANCODE_START:
					key = KEY_PROG3;
					break;
				case H3600_SCANCODE_UP:
					key = KEY_UP;
					break;
				case H3600_SCANCODE_RIGHT:
					key = KEY_RIGHT;
					break;
				case H3600_SCANCODE_LEFT:
					key = KEY_LEFT;
					break;
				case H3600_SCANCODE_DOWN:
					key = KEY_DOWN;
					break;
				default:
					key = 0;
			}
			if (key)
				input_report_key(dev, key, down);
			break;
		/*
		 * Native touchscreen event data is formatted as shown below:-
		 *
		 *      +-------+-------+-------+-------+
		 *      | Xmsb  | Xlsb  | Ymsb  | Ylsb  |
		 *      +-------+-------+-------+-------+
		 *       byte 0    1       2       3
		 */
		case TOUCHS_ID:
			if (!touched) {
				input_report_key(dev, BTN_TOUCH, 1);
				touched = 1;
			}

			if (ts->len) {
				unsigned short x, y;

				x = ts->buf[0]; x <<= 8; x += ts->buf[1];
				y = ts->buf[2]; y <<= 8; y += ts->buf[3];

				input_report_abs(dev, ABS_X, x);
				input_report_abs(dev, ABS_Y, y);
			} else {
				input_report_key(dev, BTN_TOUCH, 0);
				touched = 0;
			}
			break;
		default:
			/* Send a non input event elsewhere */
			break;
	}

	input_sync(dev);
}