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
struct gunze {scalar_t__ idx; unsigned char* data; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ GUNZE_MAX_LENGTH ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  gunze_process_packet (struct gunze*) ; 
 struct gunze* serio_get_drvdata (struct serio*) ; 

__attribute__((used)) static irqreturn_t gunze_interrupt(struct serio *serio,
		unsigned char data, unsigned int flags)
{
	struct gunze* gunze = serio_get_drvdata(serio);

	if (data == '\r') {
		gunze_process_packet(gunze);
		gunze->idx = 0;
	} else {
		if (gunze->idx < GUNZE_MAX_LENGTH)
			gunze->data[gunze->idx++] = data;
	}
	return IRQ_HANDLED;
}