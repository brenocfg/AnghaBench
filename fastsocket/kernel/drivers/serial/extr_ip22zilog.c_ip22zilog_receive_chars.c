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
struct zilog_channel {int /*<<< orphan*/  data; int /*<<< orphan*/  control; } ;
struct TYPE_8__ {int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  brk; int /*<<< orphan*/  rx; } ;
struct TYPE_9__ {unsigned int read_status_mask; TYPE_3__ icount; TYPE_2__* state; } ;
struct uart_ip22zilog_port {unsigned char parity_mask; unsigned int tty_break; TYPE_4__ port; } ;
struct tty_struct {int dummy; } ;
struct TYPE_6__ {struct tty_struct* tty; } ;
struct TYPE_7__ {TYPE_1__ port; } ;

/* Variables and functions */
 unsigned int CRC_ERR ; 
 int /*<<< orphan*/  ERR_RES ; 
 unsigned int PAR_ERR ; 
 int /*<<< orphan*/  R1 ; 
 unsigned int Rx_BRK ; 
 unsigned char Rx_CH_AV ; 
 unsigned int Rx_OVR ; 
 unsigned int Rx_SYS ; 
 unsigned char TTY_BREAK ; 
 unsigned char TTY_FRAME ; 
 unsigned char TTY_NORMAL ; 
 unsigned char TTY_PARITY ; 
 int /*<<< orphan*/  ZSDELAY () ; 
 int /*<<< orphan*/  ZS_WSYNC (struct zilog_channel*) ; 
 unsigned int read_zsreg (struct zilog_channel*,int /*<<< orphan*/ ) ; 
 unsigned char readb (int /*<<< orphan*/ *) ; 
 scalar_t__ uart_handle_sysrq_char (TYPE_4__*,unsigned char) ; 
 int /*<<< orphan*/  uart_insert_char (TYPE_4__*,unsigned int,unsigned int,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct tty_struct *ip22zilog_receive_chars(struct uart_ip22zilog_port *up,
						  struct zilog_channel *channel)
{
	struct tty_struct *tty;
	unsigned char ch, flag;
	unsigned int r1;

	tty = NULL;
	if (up->port.state != NULL &&
	    up->port.state->port.tty != NULL)
		tty = up->port.state->port.tty;

	for (;;) {
		ch = readb(&channel->control);
		ZSDELAY();
		if (!(ch & Rx_CH_AV))
			break;

		r1 = read_zsreg(channel, R1);
		if (r1 & (PAR_ERR | Rx_OVR | CRC_ERR)) {
			writeb(ERR_RES, &channel->control);
			ZSDELAY();
			ZS_WSYNC(channel);
		}

		ch = readb(&channel->data);
		ZSDELAY();

		ch &= up->parity_mask;

		/* Handle the null char got when BREAK is removed.  */
		if (!ch)
			r1 |= up->tty_break;

		/* A real serial line, record the character and status.  */
		flag = TTY_NORMAL;
		up->port.icount.rx++;
		if (r1 & (PAR_ERR | Rx_OVR | CRC_ERR | Rx_SYS | Rx_BRK)) {
			up->tty_break = 0;

			if (r1 & (Rx_SYS | Rx_BRK)) {
				up->port.icount.brk++;
				if (r1 & Rx_SYS)
					continue;
				r1 &= ~(PAR_ERR | CRC_ERR);
			}
			else if (r1 & PAR_ERR)
				up->port.icount.parity++;
			else if (r1 & CRC_ERR)
				up->port.icount.frame++;
			if (r1 & Rx_OVR)
				up->port.icount.overrun++;
			r1 &= up->port.read_status_mask;
			if (r1 & Rx_BRK)
				flag = TTY_BREAK;
			else if (r1 & PAR_ERR)
				flag = TTY_PARITY;
			else if (r1 & CRC_ERR)
				flag = TTY_FRAME;
		}

		if (uart_handle_sysrq_char(&up->port, ch))
			continue;

		if (tty)
			uart_insert_char(&up->port, r1, Rx_OVR, ch, flag);
	}
	return tty;
}