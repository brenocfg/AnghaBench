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
struct uart_port {unsigned char read_status_mask; TYPE_3__ icount; scalar_t__ membase; TYPE_2__* state; } ;
struct tty_struct {int dummy; } ;
struct TYPE_4__ {struct tty_struct* tty; } ;
struct TYPE_5__ {TYPE_1__ port; } ;

/* Variables and functions */
 unsigned char FR_RXFE ; 
 unsigned char SR_BE ; 
 unsigned char SR_FE ; 
 unsigned char SR_OE ; 
 unsigned char SR_PE ; 
 unsigned char TTY_BREAK ; 
 unsigned char TTY_FRAME ; 
 unsigned char TTY_NORMAL ; 
 unsigned char TTY_PARITY ; 
 scalar_t__ UART_DR ; 
 scalar_t__ UART_FR ; 
 scalar_t__ UART_SR ; 
 unsigned char readl (scalar_t__) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 scalar_t__ uart_handle_break (struct uart_port*) ; 
 scalar_t__ uart_handle_sysrq_char (struct uart_port*,unsigned char) ; 
 int /*<<< orphan*/  uart_insert_char (struct uart_port*,unsigned char,unsigned char,unsigned char,unsigned char) ; 
 scalar_t__ unlikely (unsigned char) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void netx_rxint(struct uart_port *port)
{
	unsigned char rx, flg, status;
	struct tty_struct *tty = port->state->port.tty;

	while (!(readl(port->membase + UART_FR) & FR_RXFE)) {
		rx = readl(port->membase + UART_DR);
		flg = TTY_NORMAL;
		port->icount.rx++;
		status = readl(port->membase + UART_SR);
		if (status & SR_BE) {
			writel(0, port->membase + UART_SR);
			if (uart_handle_break(port))
				continue;
		}

		if (unlikely(status & (SR_FE | SR_PE | SR_OE))) {

			if (status & SR_PE)
				port->icount.parity++;
			else if (status & SR_FE)
				port->icount.frame++;
			if (status & SR_OE)
				port->icount.overrun++;

			status &= port->read_status_mask;

			if (status & SR_BE)
				flg = TTY_BREAK;
			else if (status & SR_PE)
				flg = TTY_PARITY;
			else if (status & SR_FE)
				flg = TTY_FRAME;
		}

		if (uart_handle_sysrq_char(port, rx))
			continue;

		uart_insert_char(port, status, SR_OE, rx, flg);
	}

	tty_flip_buffer_push(tty);
	return;
}