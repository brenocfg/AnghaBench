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
struct TYPE_6__ {int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  brk; int /*<<< orphan*/  rx; } ;
struct uart_port {unsigned int read_status_mask; TYPE_3__ icount; TYPE_2__* state; } ;
struct tty_struct {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {struct tty_struct* tty; } ;
struct TYPE_5__ {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int TTY_BREAK ; 
 unsigned int TTY_FRAME ; 
 unsigned int TTY_NORMAL ; 
 unsigned int TTY_PARITY ; 
 unsigned int UART_DUMMY_LSR_RX ; 
 unsigned int UART_GET_CHAR (struct uart_port*) ; 
 unsigned int UART_GET_LSR (struct uart_port*) ; 
 unsigned int URLS_URBI ; 
 unsigned int URLS_URDR ; 
 unsigned int URLS_URFE ; 
 unsigned int URLS_URPE ; 
 unsigned int URLS_URROE ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 scalar_t__ uart_handle_break (struct uart_port*) ; 
 scalar_t__ uart_handle_sysrq_char (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  uart_insert_char (struct uart_port*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static irqreturn_t ks8695uart_rx_chars(int irq, void *dev_id)
{
	struct uart_port *port = dev_id;
	struct tty_struct *tty = port->state->port.tty;
	unsigned int status, ch, lsr, flg, max_count = 256;

	status = UART_GET_LSR(port);		/* clears pending LSR interrupts */
	while ((status & URLS_URDR) && max_count--) {
		ch = UART_GET_CHAR(port);
		flg = TTY_NORMAL;

		port->icount.rx++;

		/*
		 * Note that the error handling code is
		 * out of the main execution path
		 */
		lsr = UART_GET_LSR(port) | UART_DUMMY_LSR_RX;
		if (unlikely(lsr & (URLS_URBI | URLS_URPE | URLS_URFE | URLS_URROE))) {
			if (lsr & URLS_URBI) {
				lsr &= ~(URLS_URFE | URLS_URPE);
				port->icount.brk++;
				if (uart_handle_break(port))
					goto ignore_char;
			}
			if (lsr & URLS_URPE)
				port->icount.parity++;
			if (lsr & URLS_URFE)
				port->icount.frame++;
			if (lsr & URLS_URROE)
				port->icount.overrun++;

			lsr &= port->read_status_mask;

			if (lsr & URLS_URBI)
				flg = TTY_BREAK;
			else if (lsr & URLS_URPE)
				flg = TTY_PARITY;
			else if (lsr & URLS_URFE)
				flg = TTY_FRAME;
		}

		if (uart_handle_sysrq_char(port, ch))
			goto ignore_char;

		uart_insert_char(port, lsr, URLS_URROE, ch, flg);

ignore_char:
		status = UART_GET_LSR(port);
	}
	tty_flip_buffer_push(tty);

	return IRQ_HANDLED;
}