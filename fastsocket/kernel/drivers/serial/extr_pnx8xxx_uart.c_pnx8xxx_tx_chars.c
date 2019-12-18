#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  tx; } ;
struct TYPE_8__ {TYPE_2__ icount; scalar_t__ x_char; TYPE_1__* state; } ;
struct pnx8xxx_port {TYPE_3__ port; } ;
struct circ_buf {size_t tail; scalar_t__* buf; } ;
struct TYPE_6__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNX8XXX_FIFO ; 
 int PNX8XXX_UART_FIFO_TXFIFO ; 
 int UART_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 int /*<<< orphan*/  pnx8xxx_mctrl_check (struct pnx8xxx_port*) ; 
 int /*<<< orphan*/  pnx8xxx_stop_tx (TYPE_3__*) ; 
 int serial_in (struct pnx8xxx_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct pnx8xxx_port*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 scalar_t__ uart_tx_stopped (TYPE_3__*) ; 
 int /*<<< orphan*/  uart_write_wakeup (TYPE_3__*) ; 

__attribute__((used)) static void pnx8xxx_tx_chars(struct pnx8xxx_port *sport)
{
	struct circ_buf *xmit = &sport->port.state->xmit;

	if (sport->port.x_char) {
		serial_out(sport, PNX8XXX_FIFO, sport->port.x_char);
		sport->port.icount.tx++;
		sport->port.x_char = 0;
		return;
	}

	/*
	 * Check the modem control lines before
	 * transmitting anything.
	 */
	pnx8xxx_mctrl_check(sport);

	if (uart_circ_empty(xmit) || uart_tx_stopped(&sport->port)) {
		pnx8xxx_stop_tx(&sport->port);
		return;
	}

	/*
	 * TX while bytes available
	 */
	while (((serial_in(sport, PNX8XXX_FIFO) &
					PNX8XXX_UART_FIFO_TXFIFO) >> 16) < 16) {
		serial_out(sport, PNX8XXX_FIFO, xmit->buf[xmit->tail]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		sport->port.icount.tx++;
		if (uart_circ_empty(xmit))
			break;
	}

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(&sport->port);

	if (uart_circ_empty(xmit))
		pnx8xxx_stop_tx(&sport->port);
}