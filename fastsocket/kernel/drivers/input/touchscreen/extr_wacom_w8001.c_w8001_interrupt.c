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
struct w8001_coord {int /*<<< orphan*/  tsw; int /*<<< orphan*/  pen_pressure; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct w8001 {unsigned char* data; size_t idx; int /*<<< orphan*/  cmd_done; int /*<<< orphan*/  response_type; int /*<<< orphan*/  response; struct input_dev* dev; } ;
struct serio {int dummy; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned char W8001_LEAD_BYTE ; 
 unsigned char W8001_LEAD_MASK ; 
 int /*<<< orphan*/  W8001_MAX_LENGTH ; 
 int /*<<< orphan*/  W8001_QUERY_PACKET ; 
 unsigned char W8001_TAB_BYTE ; 
 unsigned char W8001_TAB_MASK ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_data (unsigned char*,struct w8001_coord*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned char) ; 
 struct w8001* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static irqreturn_t w8001_interrupt(struct serio *serio,
				   unsigned char data, unsigned int flags)
{
	struct w8001 *w8001 = serio_get_drvdata(serio);
	struct input_dev *dev = w8001->dev;
	struct w8001_coord coord;
	unsigned char tmp;

	w8001->data[w8001->idx] = data;
	switch (w8001->idx++) {
	case 0:
		if ((data & W8001_LEAD_MASK) != W8001_LEAD_BYTE) {
			pr_debug("w8001: unsynchronized data: 0x%02x\n", data);
			w8001->idx = 0;
		}
		break;

	case 8:
		tmp = w8001->data[0] & W8001_TAB_MASK;
		if (unlikely(tmp == W8001_TAB_BYTE))
			break;

		w8001->idx = 0;
		parse_data(w8001->data, &coord);
		input_report_abs(dev, ABS_X, coord.x);
		input_report_abs(dev, ABS_Y, coord.y);
		input_report_abs(dev, ABS_PRESSURE, coord.pen_pressure);
		input_report_key(dev, BTN_TOUCH, coord.tsw);
		input_sync(dev);
		break;

	case 10:
		w8001->idx = 0;
		memcpy(w8001->response, w8001->data, W8001_MAX_LENGTH);
		w8001->response_type = W8001_QUERY_PACKET;
		complete(&w8001->cmd_done);
		break;
	}

	return IRQ_HANDLED;
}