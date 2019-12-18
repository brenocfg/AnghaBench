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
typedef  int u16 ;
struct TYPE_6__ {int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  brk; int /*<<< orphan*/  rx; } ;
struct uart_port {int read_status_mask; scalar_t__ sysrq; TYPE_3__ icount; int /*<<< orphan*/  dev; TYPE_2__* state; } ;
struct uart_qe_port {struct qe_bd* rx_cur; struct qe_bd* rx_bd_base; struct uart_port port; } ;
struct tty_struct {int dummy; } ;
struct qe_bd {int /*<<< orphan*/  status; int /*<<< orphan*/  buf; int /*<<< orphan*/  length; } ;
struct TYPE_4__ {struct tty_struct* tty; } ;
struct TYPE_5__ {TYPE_1__ port; } ;

/* Variables and functions */
 int BD_SC_BR ; 
 int BD_SC_EMPTY ; 
 int BD_SC_FR ; 
 int BD_SC_ID ; 
 int BD_SC_OV ; 
 int BD_SC_PR ; 
 int BD_SC_WRAP ; 
 unsigned int TTY_BREAK ; 
 unsigned int TTY_FRAME ; 
 unsigned int TTY_NORMAL ; 
 unsigned int TTY_OVERRUN ; 
 unsigned int TTY_PARITY ; 
 int /*<<< orphan*/  clrsetbits_be16 (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int in_be16 (int /*<<< orphan*/ *) ; 
 unsigned char* qe2cpu_addr (int /*<<< orphan*/ ,struct uart_qe_port*) ; 
 int tty_buffer_request_room (struct tty_struct*,int) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_struct*,unsigned char,unsigned int) ; 
 scalar_t__ uart_handle_sysrq_char (struct uart_port*,unsigned char) ; 

__attribute__((used)) static void qe_uart_int_rx(struct uart_qe_port *qe_port)
{
	int i;
	unsigned char ch, *cp;
	struct uart_port *port = &qe_port->port;
	struct tty_struct *tty = port->state->port.tty;
	struct qe_bd *bdp;
	u16 status;
	unsigned int flg;

	/* Just loop through the closed BDs and copy the characters into
	 * the buffer.
	 */
	bdp = qe_port->rx_cur;
	while (1) {
		status = in_be16(&bdp->status);

		/* If this one is empty, then we assume we've read them all */
		if (status & BD_SC_EMPTY)
			break;

		/* get number of characters, and check space in RX buffer */
		i = in_be16(&bdp->length);

		/* If we don't have enough room in RX buffer for the entire BD,
		 * then we try later, which will be the next RX interrupt.
		 */
		if (tty_buffer_request_room(tty, i) < i) {
			dev_dbg(port->dev, "ucc-uart: no room in RX buffer\n");
			return;
		}

		/* get pointer */
		cp = qe2cpu_addr(bdp->buf, qe_port);

		/* loop through the buffer */
		while (i-- > 0) {
			ch = *cp++;
			port->icount.rx++;
			flg = TTY_NORMAL;

			if (!i && status &
			    (BD_SC_BR | BD_SC_FR | BD_SC_PR | BD_SC_OV))
				goto handle_error;
			if (uart_handle_sysrq_char(port, ch))
				continue;

error_return:
			tty_insert_flip_char(tty, ch, flg);

		}

		/* This BD is ready to be used again. Clear status. get next */
		clrsetbits_be16(&bdp->status, BD_SC_BR | BD_SC_FR | BD_SC_PR |
			BD_SC_OV | BD_SC_ID, BD_SC_EMPTY);
		if (in_be16(&bdp->status) & BD_SC_WRAP)
			bdp = qe_port->rx_bd_base;
		else
			bdp++;

	}

	/* Write back buffer pointer */
	qe_port->rx_cur = bdp;

	/* Activate BH processing */
	tty_flip_buffer_push(tty);

	return;

	/* Error processing */

handle_error:
	/* Statistics */
	if (status & BD_SC_BR)
		port->icount.brk++;
	if (status & BD_SC_PR)
		port->icount.parity++;
	if (status & BD_SC_FR)
		port->icount.frame++;
	if (status & BD_SC_OV)
		port->icount.overrun++;

	/* Mask out ignored conditions */
	status &= port->read_status_mask;

	/* Handle the remaining ones */
	if (status & BD_SC_BR)
		flg = TTY_BREAK;
	else if (status & BD_SC_PR)
		flg = TTY_PARITY;
	else if (status & BD_SC_FR)
		flg = TTY_FRAME;

	/* Overrun does not affect the current character ! */
	if (status & BD_SC_OV)
		tty_insert_flip_char(tty, 0, TTY_OVERRUN);
#ifdef SUPPORT_SYSRQ
	port->sysrq = 0;
#endif
	goto error_return;
}