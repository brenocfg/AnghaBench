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
struct TYPE_6__ {scalar_t__ buf; } ;
struct sdio_uart_port {int lcr; TYPE_3__ xmit; int /*<<< orphan*/  func; scalar_t__ ier; TYPE_2__* tty; } ;
struct TYPE_5__ {TYPE_1__* termios; } ;
struct TYPE_4__ {int c_cflag; } ;

/* Variables and functions */
 int HUPCL ; 
 int TIOCM_DTR ; 
 int TIOCM_OUT2 ; 
 int TIOCM_RTS ; 
 int /*<<< orphan*/  UART_FCR ; 
 int UART_FCR_CLEAR_RCVR ; 
 int UART_FCR_CLEAR_XMIT ; 
 int UART_FCR_ENABLE_FIFO ; 
 int /*<<< orphan*/  UART_IER ; 
 int /*<<< orphan*/  UART_LCR ; 
 int UART_LCR_SBC ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  sdio_disable_func (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_out (struct sdio_uart_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdio_release_irq (int /*<<< orphan*/ ) ; 
 int sdio_uart_claim_func (struct sdio_uart_port*) ; 
 int /*<<< orphan*/  sdio_uart_clear_mctrl (struct sdio_uart_port*,int) ; 
 int /*<<< orphan*/  sdio_uart_release_func (struct sdio_uart_port*) ; 
 int /*<<< orphan*/  sdio_uart_stop_rx (struct sdio_uart_port*) ; 

__attribute__((used)) static void sdio_uart_shutdown(struct sdio_uart_port *port)
{
	int ret;

	ret = sdio_uart_claim_func(port);
	if (ret)
		goto skip;

	sdio_uart_stop_rx(port);

	/* TODO: wait here for TX FIFO to drain */

	/* Turn off DTR and RTS early. */
	if (port->tty->termios->c_cflag & HUPCL)
		sdio_uart_clear_mctrl(port, TIOCM_DTR | TIOCM_RTS);

	 /* Disable interrupts from this port */
	sdio_release_irq(port->func);
	port->ier = 0;
	sdio_out(port, UART_IER, 0);

	sdio_uart_clear_mctrl(port, TIOCM_OUT2);

	/* Disable break condition and FIFOs. */
	port->lcr &= ~UART_LCR_SBC;
	sdio_out(port, UART_LCR, port->lcr);
	sdio_out(port, UART_FCR, UART_FCR_ENABLE_FIFO |
				 UART_FCR_CLEAR_RCVR |
				 UART_FCR_CLEAR_XMIT);
	sdio_out(port, UART_FCR, 0);

	sdio_disable_func(port->func);

	sdio_uart_release_func(port);

skip:
	/* Free the transmit buffer page. */
	free_page((unsigned long)port->xmit.buf);
}