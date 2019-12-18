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
struct tty_struct {int hw_stopped; } ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  open_wait; int /*<<< orphan*/  delta_msr_wait; } ;
struct TYPE_6__ {int modem_status; } ;
struct TYPE_5__ {int /*<<< orphan*/  cts; int /*<<< orphan*/  dcd; int /*<<< orphan*/  dsr; int /*<<< orphan*/  rng; } ;
struct mxser_port {scalar_t__ type; int IER; scalar_t__ ioaddr; TYPE_4__* board; TYPE_3__ port; TYPE_2__ mon_data; TYPE_1__ icount; } ;
struct TYPE_8__ {int /*<<< orphan*/  chip_flag; } ;

/* Variables and functions */
 int ASYNC_CHECK_CD ; 
 int ASYNC_CTS_FLOW ; 
 scalar_t__ PORT_16550A ; 
 scalar_t__ UART_IER ; 
 int UART_IER_THRI ; 
 int UART_MSR_CTS ; 
 int UART_MSR_DCD ; 
 int UART_MSR_DCTS ; 
 int UART_MSR_DDCD ; 
 int UART_MSR_DDSR ; 
 int UART_MSR_TERI ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty_struct*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mxser_check_modem_status(struct tty_struct *tty,
				struct mxser_port *port, int status)
{
	/* update input line counters */
	if (status & UART_MSR_TERI)
		port->icount.rng++;
	if (status & UART_MSR_DDSR)
		port->icount.dsr++;
	if (status & UART_MSR_DDCD)
		port->icount.dcd++;
	if (status & UART_MSR_DCTS)
		port->icount.cts++;
	port->mon_data.modem_status = status;
	wake_up_interruptible(&port->port.delta_msr_wait);

	if ((port->port.flags & ASYNC_CHECK_CD) && (status & UART_MSR_DDCD)) {
		if (status & UART_MSR_DCD)
			wake_up_interruptible(&port->port.open_wait);
	}

	if (port->port.flags & ASYNC_CTS_FLOW) {
		if (tty->hw_stopped) {
			if (status & UART_MSR_CTS) {
				tty->hw_stopped = 0;

				if ((port->type != PORT_16550A) &&
						(!port->board->chip_flag)) {
					outb(port->IER & ~UART_IER_THRI,
						port->ioaddr + UART_IER);
					port->IER |= UART_IER_THRI;
					outb(port->IER, port->ioaddr +
							UART_IER);
				}
				tty_wakeup(tty);
			}
		} else {
			if (!(status & UART_MSR_CTS)) {
				tty->hw_stopped = 1;
				if (port->type != PORT_16550A &&
						!port->board->chip_flag) {
					port->IER &= ~UART_IER_THRI;
					outb(port->IER, port->ioaddr +
							UART_IER);
				}
			}
		}
	}
}