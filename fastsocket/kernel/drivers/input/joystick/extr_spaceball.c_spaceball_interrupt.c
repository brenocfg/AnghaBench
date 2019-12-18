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
struct spaceball {int escape; unsigned char* data; int /*<<< orphan*/  idx; } ;
struct serio {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SPACEBALL_MAX_LENGTH ; 
 struct spaceball* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  spaceball_process_packet (struct spaceball*) ; 

__attribute__((used)) static irqreturn_t spaceball_interrupt(struct serio *serio,
		unsigned char data, unsigned int flags)
{
	struct spaceball *spaceball = serio_get_drvdata(serio);

	switch (data) {
		case 0xd:
			spaceball_process_packet(spaceball);
			spaceball->idx = 0;
			spaceball->escape = 0;
			break;
		case '^':
			if (!spaceball->escape) {
				spaceball->escape = 1;
				break;
			}
			spaceball->escape = 0;
		case 'M':
		case 'Q':
		case 'S':
			if (spaceball->escape) {
				spaceball->escape = 0;
				data &= 0x1f;
			}
		default:
			if (spaceball->escape)
				spaceball->escape = 0;
			if (spaceball->idx < SPACEBALL_MAX_LENGTH)
				spaceball->data[spaceball->idx++] = data;
			break;
	}
	return IRQ_HANDLED;
}