#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  brk; int /*<<< orphan*/  rx; } ;
struct uart_port {int /*<<< orphan*/  lock; TYPE_3__ icount; scalar_t__ sysrq; TYPE_2__* state; } ;
struct tty_struct {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  command; int /*<<< orphan*/  mpc52xx_psc_status; } ;
struct TYPE_9__ {int (* raw_rx_rdy ) (struct uart_port*) ;unsigned char (* read_char ) (struct uart_port*) ;} ;
struct TYPE_6__ {struct tty_struct* tty; } ;
struct TYPE_7__ {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPC52xx_PSC_RST_ERR_STAT ; 
 unsigned short MPC52xx_PSC_SR_FE ; 
 unsigned short MPC52xx_PSC_SR_OE ; 
 unsigned short MPC52xx_PSC_SR_PE ; 
 unsigned short MPC52xx_PSC_SR_RB ; 
 TYPE_5__* PSC (struct uart_port*) ; 
 unsigned char TTY_BREAK ; 
 unsigned char TTY_FRAME ; 
 unsigned char TTY_NORMAL ; 
 unsigned char TTY_OVERRUN ; 
 unsigned char TTY_PARITY ; 
 unsigned short in_be16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* psc_ops ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct uart_port*) ; 
 unsigned char stub2 (struct uart_port*) ; 
 int stub3 (struct uart_port*) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_struct*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  uart_handle_break (struct uart_port*) ; 
 scalar_t__ uart_handle_sysrq_char (struct uart_port*,unsigned char) ; 

__attribute__((used)) static inline int
mpc52xx_uart_int_rx_chars(struct uart_port *port)
{
	struct tty_struct *tty = port->state->port.tty;
	unsigned char ch, flag;
	unsigned short status;

	/* While we can read, do so ! */
	while (psc_ops->raw_rx_rdy(port)) {
		/* Get the char */
		ch = psc_ops->read_char(port);

		/* Handle sysreq char */
#ifdef SUPPORT_SYSRQ
		if (uart_handle_sysrq_char(port, ch)) {
			port->sysrq = 0;
			continue;
		}
#endif

		/* Store it */

		flag = TTY_NORMAL;
		port->icount.rx++;

		status = in_be16(&PSC(port)->mpc52xx_psc_status);

		if (status & (MPC52xx_PSC_SR_PE |
			      MPC52xx_PSC_SR_FE |
			      MPC52xx_PSC_SR_RB)) {

			if (status & MPC52xx_PSC_SR_RB) {
				flag = TTY_BREAK;
				uart_handle_break(port);
				port->icount.brk++;
			} else if (status & MPC52xx_PSC_SR_PE) {
				flag = TTY_PARITY;
				port->icount.parity++;
			}
			else if (status & MPC52xx_PSC_SR_FE) {
				flag = TTY_FRAME;
				port->icount.frame++;
			}

			/* Clear error condition */
			out_8(&PSC(port)->command, MPC52xx_PSC_RST_ERR_STAT);

		}
		tty_insert_flip_char(tty, ch, flag);
		if (status & MPC52xx_PSC_SR_OE) {
			/*
			 * Overrun is special, since it's
			 * reported immediately, and doesn't
			 * affect the current character
			 */
			tty_insert_flip_char(tty, 0, TTY_OVERRUN);
			port->icount.overrun++;
		}
	}

	spin_unlock(&port->lock);
	tty_flip_buffer_push(tty);
	spin_lock(&port->lock);

	return psc_ops->raw_rx_rdy(port);
}