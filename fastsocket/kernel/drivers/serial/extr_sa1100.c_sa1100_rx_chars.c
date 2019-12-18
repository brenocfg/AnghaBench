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
struct tty_struct {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  rx; } ;
struct TYPE_9__ {unsigned int read_status_mask; scalar_t__ sysrq; TYPE_3__ icount; TYPE_2__* state; } ;
struct sa1100_port {TYPE_4__ port; } ;
struct TYPE_6__ {struct tty_struct* tty; } ;
struct TYPE_7__ {TYPE_1__ port; } ;

/* Variables and functions */
 unsigned int TTY_FRAME ; 
 unsigned int TTY_NORMAL ; 
 unsigned int TTY_PARITY ; 
 unsigned int UART_GET_CHAR (struct sa1100_port*) ; 
 int /*<<< orphan*/  UART_GET_UTSR0 (struct sa1100_port*) ; 
 int UART_GET_UTSR1 (struct sa1100_port*) ; 
 unsigned int UTSR0_TO_SM (int /*<<< orphan*/ ) ; 
 int UTSR1_FRE ; 
 int UTSR1_PRE ; 
 int UTSR1_RNE ; 
 int UTSR1_ROR ; 
 unsigned int UTSR1_TO_SM (int) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 scalar_t__ uart_handle_sysrq_char (TYPE_4__*,unsigned int) ; 
 int /*<<< orphan*/  uart_insert_char (TYPE_4__*,unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void
sa1100_rx_chars(struct sa1100_port *sport)
{
	struct tty_struct *tty = sport->port.state->port.tty;
	unsigned int status, ch, flg;

	status = UTSR1_TO_SM(UART_GET_UTSR1(sport)) |
		 UTSR0_TO_SM(UART_GET_UTSR0(sport));
	while (status & UTSR1_TO_SM(UTSR1_RNE)) {
		ch = UART_GET_CHAR(sport);

		sport->port.icount.rx++;

		flg = TTY_NORMAL;

		/*
		 * note that the error handling code is
		 * out of the main execution path
		 */
		if (status & UTSR1_TO_SM(UTSR1_PRE | UTSR1_FRE | UTSR1_ROR)) {
			if (status & UTSR1_TO_SM(UTSR1_PRE))
				sport->port.icount.parity++;
			else if (status & UTSR1_TO_SM(UTSR1_FRE))
				sport->port.icount.frame++;
			if (status & UTSR1_TO_SM(UTSR1_ROR))
				sport->port.icount.overrun++;

			status &= sport->port.read_status_mask;

			if (status & UTSR1_TO_SM(UTSR1_PRE))
				flg = TTY_PARITY;
			else if (status & UTSR1_TO_SM(UTSR1_FRE))
				flg = TTY_FRAME;

#ifdef SUPPORT_SYSRQ
			sport->port.sysrq = 0;
#endif
		}

		if (uart_handle_sysrq_char(&sport->port, ch))
			goto ignore_char;

		uart_insert_char(&sport->port, status, UTSR1_TO_SM(UTSR1_ROR), ch, flg);

	ignore_char:
		status = UTSR1_TO_SM(UART_GET_UTSR1(sport)) |
			 UTSR0_TO_SM(UART_GET_UTSR0(sport));
	}
	tty_flip_buffer_push(tty);
}