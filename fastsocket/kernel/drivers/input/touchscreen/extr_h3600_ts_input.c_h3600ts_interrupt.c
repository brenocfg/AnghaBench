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
struct serio {int dummy; } ;
struct h3600_dev {unsigned char event; unsigned char len; size_t idx; unsigned char chksum; unsigned char* buf; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned char CHAR_EOF ; 
 unsigned char CHAR_SOF ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned char MAX_ID ; 
#define  STATE_DATA 131 
#define  STATE_EOF 130 
#define  STATE_ID 129 
#define  STATE_SOF 128 
 int /*<<< orphan*/  h3600ts_process_packet (struct h3600_dev*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 struct h3600_dev* serio_get_drvdata (struct serio*) ; 
 int state ; 

__attribute__((used)) static irqreturn_t h3600ts_interrupt(struct serio *serio, unsigned char data,
                                     unsigned int flags)
{
	struct h3600_dev *ts = serio_get_drvdata(serio);

	/*
	 * We have a new frame coming in.
	 */
	switch (state) {
		case STATE_SOF:
			if (data == CHAR_SOF)
				state = STATE_ID;
			break;
		case STATE_ID:
			ts->event = (data & 0xf0) >> 4;
			ts->len = (data & 0xf);
			ts->idx = 0;
			if (ts->event >= MAX_ID) {
				state = STATE_SOF;
				break;
			}
			ts->chksum = data;
			state = (ts->len > 0) ? STATE_DATA : STATE_EOF;
			break;
		case STATE_DATA:
			ts->chksum += data;
			ts->buf[ts->idx]= data;
			if (++ts->idx == ts->len)
				state = STATE_EOF;
			break;
		case STATE_EOF:
			state = STATE_SOF;
			if (data == CHAR_EOF || data == ts->chksum)
				h3600ts_process_packet(ts);
			break;
		default:
			printk("Error3\n");
			break;
	}

	return IRQ_HANDLED;
}