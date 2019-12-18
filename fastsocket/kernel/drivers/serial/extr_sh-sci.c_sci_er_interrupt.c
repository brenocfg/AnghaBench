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
struct uart_port {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ PORT_SCI ; 
 int /*<<< orphan*/  SCxSR ; 
 int /*<<< orphan*/  SCxSR_ERROR_CLEAR (struct uart_port*) ; 
 int /*<<< orphan*/  SCxSR_RDxF_CLEAR (struct uart_port*) ; 
 scalar_t__ sci_handle_errors (struct uart_port*) ; 
 int /*<<< orphan*/  sci_handle_fifo_overrun (struct uart_port*) ; 
 int /*<<< orphan*/  sci_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_out (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_rx_interrupt (int,void*) ; 
 int /*<<< orphan*/  sci_tx_interrupt (int,void*) ; 

__attribute__((used)) static irqreturn_t sci_er_interrupt(int irq, void *ptr)
{
	struct uart_port *port = ptr;

	/* Handle errors */
	if (port->type == PORT_SCI) {
		if (sci_handle_errors(port)) {
			/* discard character in rx buffer */
			sci_in(port, SCxSR);
			sci_out(port, SCxSR, SCxSR_RDxF_CLEAR(port));
		}
	} else {
		sci_handle_fifo_overrun(port);
		sci_rx_interrupt(irq, ptr);
	}

	sci_out(port, SCxSR, SCxSR_ERROR_CLEAR(port));

	/* Kick the transmission */
	sci_tx_interrupt(irq, ptr);

	return IRQ_HANDLED;
}