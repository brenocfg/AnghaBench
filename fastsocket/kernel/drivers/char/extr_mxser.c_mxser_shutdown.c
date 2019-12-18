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
struct tty_struct {int /*<<< orphan*/  flags; TYPE_1__* termios; struct mxser_port* driver_data; } ;
struct TYPE_5__ {int flags; int /*<<< orphan*/ * xmit_buf; int /*<<< orphan*/  delta_msr_wait; } ;
struct mxser_port {int MCR; int /*<<< orphan*/  slock; scalar_t__ ioaddr; TYPE_3__* board; TYPE_2__ port; scalar_t__ IER; } ;
struct TYPE_6__ {scalar_t__ chip_flag; } ;
struct TYPE_4__ {int c_cflag; } ;

/* Variables and functions */
 int ASYNC_INITIALIZED ; 
 int HUPCL ; 
 int MOXA_MUST_FCR_GDA_MODE_ENABLE ; 
 int /*<<< orphan*/  SET_MOXA_MUST_NO_SOFTWARE_FLOW_CONTROL (scalar_t__) ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 scalar_t__ UART_FCR ; 
 int UART_FCR_CLEAR_RCVR ; 
 int UART_FCR_CLEAR_XMIT ; 
 scalar_t__ UART_IER ; 
 scalar_t__ UART_MCR ; 
 int UART_MCR_DTR ; 
 int UART_MCR_RTS ; 
 scalar_t__ UART_RX ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mxser_shutdown(struct tty_struct *tty)
{
	struct mxser_port *info = tty->driver_data;
	unsigned long flags;

	if (!(info->port.flags & ASYNC_INITIALIZED))
		return;

	spin_lock_irqsave(&info->slock, flags);

	/*
	 * clear delta_msr_wait queue to avoid mem leaks: we may free the irq
	 * here so the queue might never be waken up
	 */
	wake_up_interruptible(&info->port.delta_msr_wait);

	/*
	 * Free the IRQ, if necessary
	 */
	if (info->port.xmit_buf) {
		free_page((unsigned long) info->port.xmit_buf);
		info->port.xmit_buf = NULL;
	}

	info->IER = 0;
	outb(0x00, info->ioaddr + UART_IER);

	if (tty->termios->c_cflag & HUPCL)
		info->MCR &= ~(UART_MCR_DTR | UART_MCR_RTS);
	outb(info->MCR, info->ioaddr + UART_MCR);

	/* clear Rx/Tx FIFO's */
	if (info->board->chip_flag)
		outb(UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT |
				MOXA_MUST_FCR_GDA_MODE_ENABLE,
				info->ioaddr + UART_FCR);
	else
		outb(UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT,
			info->ioaddr + UART_FCR);

	/* read data port to reset things */
	(void) inb(info->ioaddr + UART_RX);

	set_bit(TTY_IO_ERROR, &tty->flags);

	info->port.flags &= ~ASYNC_INITIALIZED;

	if (info->board->chip_flag)
		SET_MOXA_MUST_NO_SOFTWARE_FLOW_CONTROL(info->ioaddr);

	spin_unlock_irqrestore(&info->slock, flags);
}