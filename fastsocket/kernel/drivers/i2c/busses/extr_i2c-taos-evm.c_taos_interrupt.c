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
struct taos_data {int state; unsigned char* buffer; size_t pos; } ;
struct serio {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  TAOS_BUFFER_SIZE ; 
#define  TAOS_STATE_EOFF 130 
 void* TAOS_STATE_IDLE ; 
#define  TAOS_STATE_INIT 129 
#define  TAOS_STATE_RECV 128 
 struct taos_data* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wq ; 

__attribute__((used)) static irqreturn_t taos_interrupt(struct serio *serio, unsigned char data,
				  unsigned int flags)
{
	struct taos_data *taos = serio_get_drvdata(serio);

	switch (taos->state) {
	case TAOS_STATE_INIT:
		taos->buffer[taos->pos++] = data;
		if (data == ':'
		 || taos->pos == TAOS_BUFFER_SIZE - 1) {
			taos->buffer[taos->pos] = '\0';
			taos->state = TAOS_STATE_IDLE;
			wake_up_interruptible(&wq);
		}
		break;
	case TAOS_STATE_EOFF:
		taos->state = TAOS_STATE_IDLE;
		wake_up_interruptible(&wq);
		break;
	case TAOS_STATE_RECV:
		taos->buffer[taos->pos++] = data;
		if (data == ']') {
			taos->buffer[taos->pos] = '\0';
			taos->state = TAOS_STATE_IDLE;
			wake_up_interruptible(&wq);
		}
		break;
	}

	return IRQ_HANDLED;
}