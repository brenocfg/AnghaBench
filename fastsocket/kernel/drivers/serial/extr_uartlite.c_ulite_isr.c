#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uart_port {TYPE_2__* state; scalar_t__ membase; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  tty; } ;
struct TYPE_4__ {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ ULITE_STATUS ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ ) ; 
 int ulite_receive (struct uart_port*,int) ; 
 int ulite_transmit (struct uart_port*,int) ; 

__attribute__((used)) static irqreturn_t ulite_isr(int irq, void *dev_id)
{
	struct uart_port *port = dev_id;
	int busy, n = 0;

	do {
		int stat = readb(port->membase + ULITE_STATUS);
		busy  = ulite_receive(port, stat);
		busy |= ulite_transmit(port, stat);
		n++;
	} while (busy);

	/* work done? */
	if (n > 1) {
		tty_flip_buffer_push(port->state->port.tty);
		return IRQ_HANDLED;
	} else {
		return IRQ_NONE;
	}
}