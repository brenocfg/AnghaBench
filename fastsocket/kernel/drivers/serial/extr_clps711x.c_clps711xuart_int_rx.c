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
struct TYPE_6__ {int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  rx; } ;
struct uart_port {unsigned int read_status_mask; scalar_t__ sysrq; TYPE_3__ icount; TYPE_2__* state; } ;
struct tty_struct {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {struct tty_struct* tty; } ;
struct TYPE_5__ {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SYSFLG (struct uart_port*) ; 
 unsigned int SYSFLG_URXFE ; 
 unsigned int TTY_FRAME ; 
 unsigned int TTY_NORMAL ; 
 unsigned int TTY_PARITY ; 
 int /*<<< orphan*/  UARTDR (struct uart_port*) ; 
 unsigned int UARTDR_FRMERR ; 
 unsigned int UARTDR_OVERR ; 
 unsigned int UARTDR_PARERR ; 
 unsigned int UART_ANY_ERR ; 
 unsigned int clps_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 scalar_t__ uart_handle_sysrq_char (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  uart_insert_char (struct uart_port*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static irqreturn_t clps711xuart_int_rx(int irq, void *dev_id)
{
	struct uart_port *port = dev_id;
	struct tty_struct *tty = port->state->port.tty;
	unsigned int status, ch, flg;

	status = clps_readl(SYSFLG(port));
	while (!(status & SYSFLG_URXFE)) {
		ch = clps_readl(UARTDR(port));

		port->icount.rx++;

		flg = TTY_NORMAL;

		/*
		 * Note that the error handling code is
		 * out of the main execution path
		 */
		if (unlikely(ch & UART_ANY_ERR)) {
			if (ch & UARTDR_PARERR)
				port->icount.parity++;
			else if (ch & UARTDR_FRMERR)
				port->icount.frame++;
			if (ch & UARTDR_OVERR)
				port->icount.overrun++;

			ch &= port->read_status_mask;

			if (ch & UARTDR_PARERR)
				flg = TTY_PARITY;
			else if (ch & UARTDR_FRMERR)
				flg = TTY_FRAME;

#ifdef SUPPORT_SYSRQ
			port->sysrq = 0;
#endif
		}

		if (uart_handle_sysrq_char(port, ch))
			goto ignore_char;

		/*
		 * CHECK: does overrun affect the current character?
		 * ASSUMPTION: it does not.
		 */
		uart_insert_char(port, ch, UARTDR_OVERR, ch, flg);

	ignore_char:
		status = clps_readl(SYSFLG(port));
	}
	tty_flip_buffer_push(tty);
	return IRQ_HANDLED;
}