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
struct zilog_channel {int /*<<< orphan*/  control; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx; } ;
struct TYPE_7__ {TYPE_2__ icount; TYPE_1__* state; scalar_t__ x_char; } ;
struct uart_ip22zilog_port {TYPE_3__ port; int /*<<< orphan*/  flags; int /*<<< orphan*/  curregs; } ;
struct circ_buf {size_t tail; scalar_t__* buf; } ;
struct TYPE_5__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP22ZILOG_FLAG_REGS_HELD ; 
 int /*<<< orphan*/  IP22ZILOG_FLAG_TX_ACTIVE ; 
 int /*<<< orphan*/  IP22ZILOG_FLAG_TX_STOPPED ; 
 scalar_t__ RES_Tx_P ; 
 unsigned char Tx_BUF_EMP ; 
 int UART_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 int /*<<< orphan*/  ZSDELAY () ; 
 scalar_t__ ZS_IS_CONS (struct uart_ip22zilog_port*) ; 
 scalar_t__ ZS_REGS_HELD (struct uart_ip22zilog_port*) ; 
 scalar_t__ ZS_TX_STOPPED (struct uart_ip22zilog_port*) ; 
 int /*<<< orphan*/  ZS_WSYNC (struct zilog_channel*) ; 
 int /*<<< orphan*/  __load_zsregs (struct zilog_channel*,int /*<<< orphan*/ ) ; 
 unsigned char readb (int /*<<< orphan*/ *) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 scalar_t__ uart_tx_stopped (TYPE_3__*) ; 
 int /*<<< orphan*/  uart_write_wakeup (TYPE_3__*) ; 
 int /*<<< orphan*/  writeb (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ip22zilog_transmit_chars(struct uart_ip22zilog_port *up,
				    struct zilog_channel *channel)
{
	struct circ_buf *xmit;

	if (ZS_IS_CONS(up)) {
		unsigned char status = readb(&channel->control);
		ZSDELAY();

		/* TX still busy?  Just wait for the next TX done interrupt.
		 *
		 * It can occur because of how we do serial console writes.  It would
		 * be nice to transmit console writes just like we normally would for
		 * a TTY line. (ie. buffered and TX interrupt driven).  That is not
		 * easy because console writes cannot sleep.  One solution might be
		 * to poll on enough port->xmit space becomming free.  -DaveM
		 */
		if (!(status & Tx_BUF_EMP))
			return;
	}

	up->flags &= ~IP22ZILOG_FLAG_TX_ACTIVE;

	if (ZS_REGS_HELD(up)) {
		__load_zsregs(channel, up->curregs);
		up->flags &= ~IP22ZILOG_FLAG_REGS_HELD;
	}

	if (ZS_TX_STOPPED(up)) {
		up->flags &= ~IP22ZILOG_FLAG_TX_STOPPED;
		goto ack_tx_int;
	}

	if (up->port.x_char) {
		up->flags |= IP22ZILOG_FLAG_TX_ACTIVE;
		writeb(up->port.x_char, &channel->data);
		ZSDELAY();
		ZS_WSYNC(channel);

		up->port.icount.tx++;
		up->port.x_char = 0;
		return;
	}

	if (up->port.state == NULL)
		goto ack_tx_int;
	xmit = &up->port.state->xmit;
	if (uart_circ_empty(xmit))
		goto ack_tx_int;
	if (uart_tx_stopped(&up->port))
		goto ack_tx_int;

	up->flags |= IP22ZILOG_FLAG_TX_ACTIVE;
	writeb(xmit->buf[xmit->tail], &channel->data);
	ZSDELAY();
	ZS_WSYNC(channel);

	xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
	up->port.icount.tx++;

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(&up->port);

	return;

ack_tx_int:
	writeb(RES_Tx_P, &channel->control);
	ZSDELAY();
	ZS_WSYNC(channel);
}