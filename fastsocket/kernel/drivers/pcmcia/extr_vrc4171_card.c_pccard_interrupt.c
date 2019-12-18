#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ slot; int csc_irq; int /*<<< orphan*/  pcmcia_socket; } ;
typedef  TYPE_1__ vrc4171_socket_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 size_t CARD_SLOTA ; 
 size_t CARD_SLOTB ; 
 int IRQ_A ; 
 int IRQ_B ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ SLOT_INITIALIZED ; 
 unsigned int get_events (size_t) ; 
 int /*<<< orphan*/  pcmcia_parse_events (int /*<<< orphan*/ *,unsigned int) ; 
 int vrc4171_get_irq_status () ; 
 TYPE_1__* vrc4171_sockets ; 

__attribute__((used)) static irqreturn_t pccard_interrupt(int irq, void *dev_id)
{
	vrc4171_socket_t *socket;
	unsigned int events;
	irqreturn_t retval = IRQ_NONE;
	uint16_t status;

	status = vrc4171_get_irq_status();
	if (status & IRQ_A) {
		socket = &vrc4171_sockets[CARD_SLOTA];
		if (socket->slot == SLOT_INITIALIZED) {
			if (status & (1 << socket->csc_irq)) {
				events = get_events(CARD_SLOTA);
				if (events != 0) {
					pcmcia_parse_events(&socket->pcmcia_socket, events);
					retval = IRQ_HANDLED;
				}
			}
		}
	}

	if (status & IRQ_B) {
		socket = &vrc4171_sockets[CARD_SLOTB];
		if (socket->slot == SLOT_INITIALIZED) {
			if (status & (1 << socket->csc_irq)) {
				events = get_events(CARD_SLOTB);
				if (events != 0) {
					pcmcia_parse_events(&socket->pcmcia_socket, events);
					retval = IRQ_HANDLED;
				}
			}
		}
	}

	return retval;
}