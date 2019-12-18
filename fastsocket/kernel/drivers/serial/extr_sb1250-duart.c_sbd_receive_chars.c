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
struct uart_icount {int /*<<< orphan*/  overrun; int /*<<< orphan*/  parity; int /*<<< orphan*/  frame; int /*<<< orphan*/  brk; int /*<<< orphan*/  rx; } ;
struct uart_port {unsigned int read_status_mask; TYPE_2__* state; struct uart_icount icount; } ;
struct sbd_port {struct uart_port port; } ;
struct TYPE_3__ {int /*<<< orphan*/  tty; } ;
struct TYPE_4__ {TYPE_1__ port; } ;

/* Variables and functions */
 unsigned int M_DUART_FRM_ERR ; 
 unsigned int M_DUART_OVRUN_ERR ; 
 unsigned int M_DUART_PARITY_ERR ; 
 unsigned int M_DUART_RCVD_BRK ; 
 unsigned int M_DUART_RX_RDY ; 
 int /*<<< orphan*/  R_DUART_RX_HOLD ; 
 int /*<<< orphan*/  R_DUART_STATUS ; 
 unsigned int TTY_BREAK ; 
 unsigned int TTY_FRAME ; 
 unsigned int TTY_NORMAL ; 
 unsigned int TTY_PARITY ; 
 unsigned int read_sbdchn (struct sbd_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ ) ; 
 scalar_t__ uart_handle_break (struct uart_port*) ; 
 scalar_t__ uart_handle_sysrq_char (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  uart_insert_char (struct uart_port*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static void sbd_receive_chars(struct sbd_port *sport)
{
	struct uart_port *uport = &sport->port;
	struct uart_icount *icount;
	unsigned int status, ch, flag;
	int count;

	for (count = 16; count; count--) {
		status = read_sbdchn(sport, R_DUART_STATUS);
		if (!(status & M_DUART_RX_RDY))
			break;

		ch = read_sbdchn(sport, R_DUART_RX_HOLD);

		flag = TTY_NORMAL;

		icount = &uport->icount;
		icount->rx++;

		if (unlikely(status &
			     (M_DUART_RCVD_BRK | M_DUART_FRM_ERR |
			      M_DUART_PARITY_ERR | M_DUART_OVRUN_ERR))) {
			if (status & M_DUART_RCVD_BRK) {
				icount->brk++;
				if (uart_handle_break(uport))
					continue;
			} else if (status & M_DUART_FRM_ERR)
				icount->frame++;
			else if (status & M_DUART_PARITY_ERR)
				icount->parity++;
			if (status & M_DUART_OVRUN_ERR)
				icount->overrun++;

			status &= uport->read_status_mask;
			if (status & M_DUART_RCVD_BRK)
				flag = TTY_BREAK;
			else if (status & M_DUART_FRM_ERR)
				flag = TTY_FRAME;
			else if (status & M_DUART_PARITY_ERR)
				flag = TTY_PARITY;
		}

		if (uart_handle_sysrq_char(uport, ch))
			continue;

		uart_insert_char(uport, status, M_DUART_OVRUN_ERR, ch, flag);
	}

	tty_flip_buffer_push(uport->state->port.tty);
}