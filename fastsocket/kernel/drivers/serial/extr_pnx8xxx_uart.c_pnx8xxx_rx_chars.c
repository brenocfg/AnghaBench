#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  brk; int /*<<< orphan*/  rx; } ;
struct TYPE_10__ {unsigned int read_status_mask; scalar_t__ sysrq; TYPE_3__ icount; TYPE_2__* state; } ;
struct pnx8xxx_port {TYPE_4__ port; } ;
struct TYPE_7__ {struct tty_struct* tty; } ;
struct TYPE_8__ {TYPE_1__ port; } ;

/* Variables and functions */
 unsigned int FIFO_TO_SM (int) ; 
 unsigned int ISTAT_TO_SM (int) ; 
 int /*<<< orphan*/  PNX8XXX_FIFO ; 
 int /*<<< orphan*/  PNX8XXX_ISTAT ; 
 int /*<<< orphan*/  PNX8XXX_LCR ; 
 int PNX8XXX_UART_FIFO_RXBRK ; 
 int PNX8XXX_UART_FIFO_RXFE ; 
 int PNX8XXX_UART_FIFO_RXFIFO ; 
 int PNX8XXX_UART_FIFO_RXPAR ; 
 int PNX8XXX_UART_INT_RXOVRN ; 
 int PNX8XXX_UART_LCR_RX_NEXT ; 
 unsigned int TTY_FRAME ; 
 unsigned int TTY_NORMAL ; 
 unsigned int TTY_PARITY ; 
 int serial_in (struct pnx8xxx_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct pnx8xxx_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 scalar_t__ uart_handle_break (TYPE_4__*) ; 
 scalar_t__ uart_handle_sysrq_char (TYPE_4__*,unsigned int) ; 
 int /*<<< orphan*/  uart_insert_char (TYPE_4__*,unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void pnx8xxx_rx_chars(struct pnx8xxx_port *sport)
{
	struct tty_struct *tty = sport->port.state->port.tty;
	unsigned int status, ch, flg;

	status = FIFO_TO_SM(serial_in(sport, PNX8XXX_FIFO)) |
		 ISTAT_TO_SM(serial_in(sport, PNX8XXX_ISTAT));
	while (status & FIFO_TO_SM(PNX8XXX_UART_FIFO_RXFIFO)) {
		ch = serial_in(sport, PNX8XXX_FIFO) & 0xff;

		sport->port.icount.rx++;

		flg = TTY_NORMAL;

		/*
		 * note that the error handling code is
		 * out of the main execution path
		 */
		if (status & (FIFO_TO_SM(PNX8XXX_UART_FIFO_RXFE |
					PNX8XXX_UART_FIFO_RXPAR |
					PNX8XXX_UART_FIFO_RXBRK) |
			      ISTAT_TO_SM(PNX8XXX_UART_INT_RXOVRN))) {
			if (status & FIFO_TO_SM(PNX8XXX_UART_FIFO_RXBRK)) {
				status &= ~(FIFO_TO_SM(PNX8XXX_UART_FIFO_RXFE) |
					FIFO_TO_SM(PNX8XXX_UART_FIFO_RXPAR));
				sport->port.icount.brk++;
				if (uart_handle_break(&sport->port))
					goto ignore_char;
			} else if (status & FIFO_TO_SM(PNX8XXX_UART_FIFO_RXPAR))
				sport->port.icount.parity++;
			else if (status & FIFO_TO_SM(PNX8XXX_UART_FIFO_RXFE))
				sport->port.icount.frame++;
			if (status & ISTAT_TO_SM(PNX8XXX_UART_INT_RXOVRN))
				sport->port.icount.overrun++;

			status &= sport->port.read_status_mask;

			if (status & FIFO_TO_SM(PNX8XXX_UART_FIFO_RXPAR))
				flg = TTY_PARITY;
			else if (status & FIFO_TO_SM(PNX8XXX_UART_FIFO_RXFE))
				flg = TTY_FRAME;

#ifdef SUPPORT_SYSRQ
			sport->port.sysrq = 0;
#endif
		}

		if (uart_handle_sysrq_char(&sport->port, ch))
			goto ignore_char;

		uart_insert_char(&sport->port, status,
				ISTAT_TO_SM(PNX8XXX_UART_INT_RXOVRN), ch, flg);

	ignore_char:
		serial_out(sport, PNX8XXX_LCR, serial_in(sport, PNX8XXX_LCR) |
				PNX8XXX_UART_LCR_RX_NEXT);
		status = FIFO_TO_SM(serial_in(sport, PNX8XXX_FIFO)) |
			 ISTAT_TO_SM(serial_in(sport, PNX8XXX_ISTAT));
	}
	tty_flip_buffer_push(tty);
}