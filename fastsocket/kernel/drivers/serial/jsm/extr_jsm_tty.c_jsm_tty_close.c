#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct uart_port {TYPE_3__* state; } ;
struct ktermios {int dummy; } ;
struct jsm_channel {int ch_c_cflag; int ch_mostat; struct jsm_board* ch_bd; scalar_t__ ch_old_baud; int /*<<< orphan*/  ch_open_count; int /*<<< orphan*/  ch_flags; } ;
struct jsm_board {int /*<<< orphan*/  pci_dev; TYPE_4__* bd_ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* uart_off ) (struct jsm_channel*) ;int /*<<< orphan*/  (* assert_modem_signals ) (struct jsm_channel*) ;} ;
struct TYPE_6__ {TYPE_1__* tty; } ;
struct TYPE_7__ {TYPE_2__ port; } ;
struct TYPE_5__ {struct ktermios* termios; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_STOPI ; 
 int /*<<< orphan*/  CLOSE ; 
 int HUPCL ; 
 int /*<<< orphan*/  INFO ; 
 int UART_MCR_DTR ; 
 int UART_MCR_RTS ; 
 int /*<<< orphan*/  jsm_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (struct jsm_channel*) ; 
 int /*<<< orphan*/  stub2 (struct jsm_channel*) ; 

__attribute__((used)) static void jsm_tty_close(struct uart_port *port)
{
	struct jsm_board *bd;
	struct ktermios *ts;
	struct jsm_channel *channel = (struct jsm_channel *)port;

	jsm_printk(CLOSE, INFO, &channel->ch_bd->pci_dev, "start\n");

	bd = channel->ch_bd;
	ts = port->state->port.tty->termios;

	channel->ch_flags &= ~(CH_STOPI);

	channel->ch_open_count--;

	/*
	 * If we have HUPCL set, lower DTR and RTS
	 */
	if (channel->ch_c_cflag & HUPCL) {
		jsm_printk(CLOSE, INFO, &channel->ch_bd->pci_dev,
			"Close. HUPCL set, dropping DTR/RTS\n");

		/* Drop RTS/DTR */
		channel->ch_mostat &= ~(UART_MCR_DTR | UART_MCR_RTS);
		bd->bd_ops->assert_modem_signals(channel);
	}

	channel->ch_old_baud = 0;

	/* Turn off UART interrupts for this port */
	channel->ch_bd->bd_ops->uart_off(channel);

	jsm_printk(CLOSE, INFO, &channel->ch_bd->pci_dev, "finish\n");
}