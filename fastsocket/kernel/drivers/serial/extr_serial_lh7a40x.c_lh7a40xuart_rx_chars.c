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
struct uart_port {int read_status_mask; TYPE_3__ icount; TYPE_2__* state; } ;
struct tty_struct {int dummy; } ;
struct TYPE_4__ {struct tty_struct* tty; } ;
struct TYPE_5__ {TYPE_1__ port; } ;

/* Variables and functions */
 unsigned int RxBreak ; 
 unsigned int RxError ; 
 unsigned int RxFramingError ; 
 unsigned int RxOverrunError ; 
 unsigned int RxParityError ; 
 unsigned int TTY_BREAK ; 
 unsigned int TTY_FRAME ; 
 unsigned int TTY_NORMAL ; 
 unsigned int TTY_PARITY ; 
 int /*<<< orphan*/  UART_R_DATA ; 
 int /*<<< orphan*/  UART_R_STATUS ; 
 unsigned int UR (struct uart_port*,int /*<<< orphan*/ ) ; 
 unsigned int nRxRdy ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 scalar_t__ uart_handle_break (struct uart_port*) ; 
 scalar_t__ uart_handle_sysrq_char (struct uart_port*,unsigned char) ; 
 int /*<<< orphan*/  uart_insert_char (struct uart_port*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static void lh7a40xuart_rx_chars (struct uart_port* port)
{
	struct tty_struct* tty = port->state->port.tty;
	int cbRxMax = 256;	/* (Gross) limit on receive */
	unsigned int data;	/* Received data and status */
	unsigned int flag;

	while (!(UR (port, UART_R_STATUS) & nRxRdy) && --cbRxMax) {
		data = UR (port, UART_R_DATA);
		flag = TTY_NORMAL;
		++port->icount.rx;

		if (unlikely(data & RxError)) {
			if (data & RxBreak) {
				data &= ~(RxFramingError | RxParityError);
				++port->icount.brk;
				if (uart_handle_break (port))
					continue;
			}
			else if (data & RxParityError)
				++port->icount.parity;
			else if (data & RxFramingError)
				++port->icount.frame;
			if (data & RxOverrunError)
				++port->icount.overrun;

				/* Mask by termios, leave Rx'd byte */
			data &= port->read_status_mask | 0xff;

			if (data & RxBreak)
				flag = TTY_BREAK;
			else if (data & RxParityError)
				flag = TTY_PARITY;
			else if (data & RxFramingError)
				flag = TTY_FRAME;
		}

		if (uart_handle_sysrq_char (port, (unsigned char) data))
			continue;

		uart_insert_char(port, data, RxOverrunError, data, flag);
	}
	tty_flip_buffer_push (tty);
	return;
}