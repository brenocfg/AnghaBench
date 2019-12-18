#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tx; } ;
struct TYPE_6__ {TYPE_2__ icount; TYPE_1__* state; } ;
struct uart_sio_port {int ier; TYPE_3__ port; } ;
struct uart_port {int dummy; } ;
struct circ_buf {int* buf; size_t tail; } ;
struct TYPE_4__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int UART_EMPTY ; 
 int /*<<< orphan*/  UART_IER ; 
 int UART_IER_THRI ; 
 int /*<<< orphan*/  UART_LSR ; 
 int /*<<< orphan*/  UART_TX ; 
 int UART_XMIT_SIZE ; 
 int serial_in (struct uart_sio_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct uart_sio_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void m32r_sio_start_tx(struct uart_port *port)
{
#ifdef CONFIG_SERIAL_M32R_PLDSIO
	struct uart_sio_port *up = (struct uart_sio_port *)port;
	struct circ_buf *xmit = &up->port.state->xmit;

	if (!(up->ier & UART_IER_THRI)) {
		up->ier |= UART_IER_THRI;
		serial_out(up, UART_IER, up->ier);
		serial_out(up, UART_TX, xmit->buf[xmit->tail]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		up->port.icount.tx++;
	}
	while((serial_in(up, UART_LSR) & UART_EMPTY) != UART_EMPTY);
#else
	struct uart_sio_port *up = (struct uart_sio_port *)port;

	if (!(up->ier & UART_IER_THRI)) {
		up->ier |= UART_IER_THRI;
		serial_out(up, UART_IER, up->ier);
	}
#endif
}