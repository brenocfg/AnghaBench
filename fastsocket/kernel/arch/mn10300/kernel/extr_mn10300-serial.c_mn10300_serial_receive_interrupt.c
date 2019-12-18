#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct uart_icount {int /*<<< orphan*/  overrun; int /*<<< orphan*/  parity; int /*<<< orphan*/  frame; int /*<<< orphan*/  brk; int /*<<< orphan*/  rx; } ;
struct tty_struct {int /*<<< orphan*/  low_latency; } ;
struct TYPE_7__ {scalar_t__ read_status_mask; scalar_t__ ignore_status_mask; struct uart_icount icount; TYPE_2__* state; } ;
struct mn10300_serial_port {unsigned int rx_inp; unsigned int rx_outp; scalar_t__* rx_buffer; int rx_brk; TYPE_3__ uart; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {struct tty_struct* tty; } ;
struct TYPE_6__ {TYPE_1__ port; } ;

/* Variables and functions */
 int CIRC_CNT (unsigned int,unsigned int,int) ; 
 int MNSC_BUFFER_SIZE ; 
 scalar_t__ SC01STR_FEF ; 
 scalar_t__ SC01STR_OEF ; 
 scalar_t__ SC01STR_PEF ; 
 int TTY_BREAK ; 
 int TTY_FRAME ; 
 int TTY_NORMAL ; 
 int TTY_OVERRUN ; 
 int TTY_PARITY ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _proto (char*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int tty_buffer_request_room (struct tty_struct*,int) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_struct*,scalar_t__,int) ; 
 int /*<<< orphan*/  uart_handle_break (TYPE_3__*) ; 
 scalar_t__ uart_handle_sysrq_char (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static void mn10300_serial_receive_interrupt(struct mn10300_serial_port *port)
{
	struct uart_icount *icount = &port->uart.icount;
	struct tty_struct *tty = port->uart.state->port.tty;
	unsigned ix;
	int count;
	u8 st, ch, push, status, overrun;

	_enter("%s", port->name);

	push = 0;

	count = CIRC_CNT(port->rx_inp, port->rx_outp, MNSC_BUFFER_SIZE);
	count = tty_buffer_request_room(tty, count);
	if (count == 0) {
		if (!tty->low_latency)
			tty_flip_buffer_push(tty);
		return;
	}

try_again:
	/* pull chars out of the hat */
	ix = port->rx_outp;
	if (ix == port->rx_inp) {
		if (push && !tty->low_latency)
			tty_flip_buffer_push(tty);
		return;
	}

	ch = port->rx_buffer[ix++];
	st = port->rx_buffer[ix++];
	smp_rmb();
	port->rx_outp = ix & (MNSC_BUFFER_SIZE - 1);
	port->uart.icount.rx++;

	st &= SC01STR_FEF | SC01STR_PEF | SC01STR_OEF;
	status = 0;
	overrun = 0;

	/* the UART doesn't detect BREAK, so we have to do that ourselves
	 * - it starts as a framing error on a NUL character
	 * - then we count another two NUL characters before issuing TTY_BREAK
	 * - then we end on a normal char or one that has all the bottom bits
	 *   zero and the top bits set
	 */
	switch (port->rx_brk) {
	case 0:
		/* not breaking at the moment */
		break;

	case 1:
		if (st & SC01STR_FEF && ch == 0) {
			port->rx_brk = 2;
			goto try_again;
		}
		goto not_break;

	case 2:
		if (st & SC01STR_FEF && ch == 0) {
			port->rx_brk = 3;
			_proto("Rx Break Detected");
			icount->brk++;
			if (uart_handle_break(&port->uart))
				goto ignore_char;
			status |= 1 << TTY_BREAK;
			goto insert;
		}
		goto not_break;

	default:
		if (st & (SC01STR_FEF | SC01STR_PEF | SC01STR_OEF))
			goto try_again; /* still breaking */

		port->rx_brk = 0; /* end of the break */

		switch (ch) {
		case 0xFF:
		case 0xFE:
		case 0xFC:
		case 0xF8:
		case 0xF0:
		case 0xE0:
		case 0xC0:
		case 0x80:
		case 0x00:
			/* discard char at probable break end */
			goto try_again;
		}
		break;
	}

process_errors:
	/* handle framing error */
	if (st & SC01STR_FEF) {
		if (ch == 0) {
			/* framing error with NUL char is probably a BREAK */
			port->rx_brk = 1;
			goto try_again;
		}

		_proto("Rx Framing Error");
		icount->frame++;
		status |= 1 << TTY_FRAME;
	}

	/* handle parity error */
	if (st & SC01STR_PEF) {
		_proto("Rx Parity Error");
		icount->parity++;
		status = TTY_PARITY;
	}

	/* handle normal char */
	if (status == 0) {
		if (uart_handle_sysrq_char(&port->uart, ch))
			goto ignore_char;
		status = (1 << TTY_NORMAL);
	}

	/* handle overrun error */
	if (st & SC01STR_OEF) {
		if (port->rx_brk)
			goto try_again;

		_proto("Rx Overrun Error");
		icount->overrun++;
		overrun = 1;
	}

insert:
	status &= port->uart.read_status_mask;

	if (!overrun && !(status & port->uart.ignore_status_mask)) {
		int flag;

		if (status & (1 << TTY_BREAK))
			flag = TTY_BREAK;
		else if (status & (1 << TTY_PARITY))
			flag = TTY_PARITY;
		else if (status & (1 << TTY_FRAME))
			flag = TTY_FRAME;
		else
			flag = TTY_NORMAL;

		tty_insert_flip_char(tty, ch, flag);
	}

	/* overrun is special, since it's reported immediately, and doesn't
	 * affect the current character
	 */
	if (overrun)
		tty_insert_flip_char(tty, 0, TTY_OVERRUN);

	count--;
	if (count <= 0) {
		if (!tty->low_latency)
			tty_flip_buffer_push(tty);
		return;
	}

ignore_char:
	push = 1;
	goto try_again;

not_break:
	port->rx_brk = 0;
	goto process_errors;
}