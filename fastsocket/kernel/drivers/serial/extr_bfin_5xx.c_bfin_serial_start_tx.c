#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int dummy; } ;
struct tty_struct {TYPE_1__* termios; } ;
struct TYPE_9__ {TYPE_3__* state; } ;
struct bfin_serial_port {scalar_t__ tx_done; scalar_t__ scts; TYPE_4__ port; } ;
struct TYPE_7__ {struct tty_struct* tty; } ;
struct TYPE_8__ {TYPE_2__ port; } ;
struct TYPE_6__ {scalar_t__ c_line; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETBEI ; 
 scalar_t__ N_IRDA ; 
 int TIOCM_CTS ; 
 int /*<<< orphan*/  UART_SET_IER (struct bfin_serial_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_serial_dma_tx_chars (struct bfin_serial_port*) ; 
 int bfin_serial_get_mctrl (TYPE_4__*) ; 
 int /*<<< orphan*/  bfin_serial_reset_irda (struct uart_port*) ; 
 int /*<<< orphan*/  bfin_serial_tx_chars (struct bfin_serial_port*) ; 
 int /*<<< orphan*/  uart_handle_cts_change (TYPE_4__*,scalar_t__) ; 

__attribute__((used)) static void bfin_serial_start_tx(struct uart_port *port)
{
	struct bfin_serial_port *uart = (struct bfin_serial_port *)port;
	struct tty_struct *tty = uart->port.state->port.tty;

#ifdef CONFIG_SERIAL_BFIN_HARD_CTSRTS
	if (uart->scts && !(bfin_serial_get_mctrl(&uart->port) & TIOCM_CTS)) {
		uart->scts = 0;
		uart_handle_cts_change(&uart->port, uart->scts);
	}
#endif

	/*
	 * To avoid losting RX interrupt, we reset IR function
	 * before sending data.
	 */
	if (tty->termios->c_line == N_IRDA)
		bfin_serial_reset_irda(port);

#ifdef CONFIG_SERIAL_BFIN_DMA
	if (uart->tx_done)
		bfin_serial_dma_tx_chars(uart);
#else
	UART_SET_IER(uart, ETBEI);
	bfin_serial_tx_chars(uart);
#endif
}