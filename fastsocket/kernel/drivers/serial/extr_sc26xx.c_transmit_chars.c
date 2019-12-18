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
struct TYPE_3__ {int /*<<< orphan*/  tx; } ;
struct uart_port {TYPE_1__ icount; TYPE_2__* state; } ;
struct circ_buf {size_t tail; int /*<<< orphan*/ * buf; } ;
struct TYPE_4__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMR_TXRDY ; 
 int READ_SC_PORT (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SR ; 
 int SR_TXRDY ; 
 int /*<<< orphan*/  THR ; 
 int UART_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 int /*<<< orphan*/  WRITE_SC_PORT (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc26xx_disable_irq (struct uart_port*,int /*<<< orphan*/ ) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 scalar_t__ uart_tx_stopped (struct uart_port*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 

__attribute__((used)) static void transmit_chars(struct uart_port *port)
{
	struct circ_buf *xmit;

	if (!port->state)
		return;

	xmit = &port->state->xmit;
	if (uart_circ_empty(xmit) || uart_tx_stopped(port)) {
		sc26xx_disable_irq(port, IMR_TXRDY);
		return;
	}
	while (!uart_circ_empty(xmit)) {
		if (!(READ_SC_PORT(port, SR) & SR_TXRDY))
			break;

		WRITE_SC_PORT(port, THR, xmit->buf[xmit->tail]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
	}
	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(port);
}