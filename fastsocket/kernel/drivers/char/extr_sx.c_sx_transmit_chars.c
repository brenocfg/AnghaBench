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
struct TYPE_5__ {scalar_t__ tty; } ;
struct TYPE_6__ {int xmit_cnt; int xmit_tail; int xmit_buf; int wakeup_chars; TYPE_2__ port; } ;
struct sx_port {int /*<<< orphan*/  locks; TYPE_3__ gs; TYPE_1__* board; } ;
struct TYPE_4__ {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ CHAN_OFFSET (struct sx_port*,int /*<<< orphan*/ ) ; 
 int SERIAL_XMIT_SIZE ; 
 int /*<<< orphan*/  SX_DEBUG_TRANSMIT ; 
 int /*<<< orphan*/  SX_PORT_TRANSMIT_LOCK ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  func_enter2 () ; 
 int /*<<< orphan*/  func_exit () ; 
 int /*<<< orphan*/  hi_txbuf ; 
 int /*<<< orphan*/  hi_txipos ; 
 int /*<<< orphan*/  hi_txopos ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,int,int) ; 
 int /*<<< orphan*/  sx_disable_tx_interrupts (struct sx_port*) ; 
 int /*<<< orphan*/  sx_dprintk (int /*<<< orphan*/ ,char*,...) ; 
 int sx_read_channel_byte (struct sx_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_write_channel_byte (struct sx_port*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_wakeup (scalar_t__) ; 

__attribute__((used)) static void sx_transmit_chars(struct sx_port *port)
{
	int c;
	int tx_ip;
	int txroom;

	func_enter2();
	sx_dprintk(SX_DEBUG_TRANSMIT, "Port %p: transmit %d chars\n",
			port, port->gs.xmit_cnt);

	if (test_and_set_bit(SX_PORT_TRANSMIT_LOCK, &port->locks)) {
		return;
	}

	while (1) {
		c = port->gs.xmit_cnt;

		sx_dprintk(SX_DEBUG_TRANSMIT, "Copying %d ", c);
		tx_ip = sx_read_channel_byte(port, hi_txipos);

		/* Took me 5 minutes to deduce this formula. 
		   Luckily it is literally in the manual in section 6.5.4.3.5 */
		txroom = (sx_read_channel_byte(port, hi_txopos) - tx_ip - 1) &
				0xff;

		/* Don't copy more bytes than there is room for in the buffer */
		if (c > txroom)
			c = txroom;
		sx_dprintk(SX_DEBUG_TRANSMIT, " %d(%d) ", c, txroom);

		/* Don't copy past the end of the hardware transmit buffer */
		if (c > 0x100 - tx_ip)
			c = 0x100 - tx_ip;

		sx_dprintk(SX_DEBUG_TRANSMIT, " %d(%d) ", c, 0x100 - tx_ip);

		/* Don't copy pas the end of the source buffer */
		if (c > SERIAL_XMIT_SIZE - port->gs.xmit_tail)
			c = SERIAL_XMIT_SIZE - port->gs.xmit_tail;

		sx_dprintk(SX_DEBUG_TRANSMIT, " %d(%ld) \n",
				c, SERIAL_XMIT_SIZE - port->gs.xmit_tail);

		/* If for one reason or another, we can't copy more data, we're
		   done! */
		if (c == 0)
			break;

		memcpy_toio(port->board->base + CHAN_OFFSET(port, hi_txbuf) +
			tx_ip, port->gs.xmit_buf + port->gs.xmit_tail, c);

		/* Update the pointer in the card */
		sx_write_channel_byte(port, hi_txipos, (tx_ip + c) & 0xff);

		/* Update the kernel buffer end */
		port->gs.xmit_tail = (port->gs.xmit_tail + c) &
				(SERIAL_XMIT_SIZE - 1);

		/* This one last. (this is essential)
		   It would allow others to start putting more data into the
		   buffer! */
		port->gs.xmit_cnt -= c;
	}

	if (port->gs.xmit_cnt == 0) {
		sx_disable_tx_interrupts(port);
	}

	if ((port->gs.xmit_cnt <= port->gs.wakeup_chars) && port->gs.port.tty) {
		tty_wakeup(port->gs.port.tty);
		sx_dprintk(SX_DEBUG_TRANSMIT, "Waking up.... ldisc (%d)....\n",
				port->gs.wakeup_chars);
	}

	clear_bit(SX_PORT_TRANSMIT_LOCK, &port->locks);
	func_exit();
}