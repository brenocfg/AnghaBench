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
struct uart_port {int dummy; } ;
struct jsm_channel {TYPE_2__* ch_bd; int /*<<< orphan*/  ch_mostat; } ;
struct TYPE_4__ {int /*<<< orphan*/  pci_dev; TYPE_1__* bd_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* assert_modem_signals ) (struct jsm_channel*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  IOCTL ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  UART_MCR_DTR ; 
 int /*<<< orphan*/  UART_MCR_RTS ; 
 int /*<<< orphan*/  jsm_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (struct jsm_channel*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void jsm_tty_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
	struct jsm_channel *channel = (struct jsm_channel *)port;

	jsm_printk(IOCTL, INFO, &channel->ch_bd->pci_dev, "start\n");

	if (mctrl & TIOCM_RTS)
		channel->ch_mostat |= UART_MCR_RTS;
	else
		channel->ch_mostat &= ~UART_MCR_RTS;

	if (mctrl & TIOCM_DTR)
		channel->ch_mostat |= UART_MCR_DTR;
	else
		channel->ch_mostat &= ~UART_MCR_DTR;

	channel->ch_bd->bd_ops->assert_modem_signals(channel);

	jsm_printk(IOCTL, INFO, &channel->ch_bd->pci_dev, "finish\n");
	udelay(10);
}