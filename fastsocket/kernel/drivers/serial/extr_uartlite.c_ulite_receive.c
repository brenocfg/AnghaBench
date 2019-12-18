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
struct TYPE_6__ {int /*<<< orphan*/  frame; int /*<<< orphan*/  overrun; int /*<<< orphan*/  parity; int /*<<< orphan*/  rx; } ;
struct uart_port {int ignore_status_mask; int read_status_mask; TYPE_3__ icount; scalar_t__ membase; TYPE_2__* state; } ;
struct tty_struct {int dummy; } ;
struct TYPE_4__ {struct tty_struct* tty; } ;
struct TYPE_5__ {TYPE_1__ port; } ;

/* Variables and functions */
 char TTY_FRAME ; 
 char TTY_NORMAL ; 
 char TTY_OVERRUN ; 
 char TTY_PARITY ; 
 scalar_t__ ULITE_RX ; 
 int ULITE_STATUS_FRAME ; 
 int ULITE_STATUS_OVERRUN ; 
 int ULITE_STATUS_PARITY ; 
 int ULITE_STATUS_RXVALID ; 
 unsigned char readb (scalar_t__) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_struct*,unsigned char,char) ; 

__attribute__((used)) static int ulite_receive(struct uart_port *port, int stat)
{
	struct tty_struct *tty = port->state->port.tty;
	unsigned char ch = 0;
	char flag = TTY_NORMAL;

	if ((stat & (ULITE_STATUS_RXVALID | ULITE_STATUS_OVERRUN
		     | ULITE_STATUS_FRAME)) == 0)
		return 0;

	/* stats */
	if (stat & ULITE_STATUS_RXVALID) {
		port->icount.rx++;
		ch = readb(port->membase + ULITE_RX);

		if (stat & ULITE_STATUS_PARITY)
			port->icount.parity++;
	}

	if (stat & ULITE_STATUS_OVERRUN)
		port->icount.overrun++;

	if (stat & ULITE_STATUS_FRAME)
		port->icount.frame++;


	/* drop byte with parity error if IGNPAR specificed */
	if (stat & port->ignore_status_mask & ULITE_STATUS_PARITY)
		stat &= ~ULITE_STATUS_RXVALID;

	stat &= port->read_status_mask;

	if (stat & ULITE_STATUS_PARITY)
		flag = TTY_PARITY;


	stat &= ~port->ignore_status_mask;

	if (stat & ULITE_STATUS_RXVALID)
		tty_insert_flip_char(tty, ch, flag);

	if (stat & ULITE_STATUS_FRAME)
		tty_insert_flip_char(tty, 0, TTY_FRAME);

	if (stat & ULITE_STATUS_OVERRUN)
		tty_insert_flip_char(tty, 0, TTY_OVERRUN);

	return 1;
}