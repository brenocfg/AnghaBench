#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {TYPE_1__* termios; scalar_t__ hw_stopped; scalar_t__ driver_data; } ;
struct ktermios {int c_cflag; } ;
struct TYPE_6__ {int MCR; int /*<<< orphan*/  open_wait; } ;
typedef  TYPE_2__ ser_info_t ;
struct TYPE_5__ {int c_cflag; } ;

/* Variables and functions */
 int CBAUD ; 
 int CLOCAL ; 
 int CRTSCTS ; 
 int /*<<< orphan*/  UART_MCR ; 
 int UART_MCR_DTR ; 
 int UART_MCR_RTS ; 
 int /*<<< orphan*/  change_speed (TYPE_2__*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  rs_360_start (struct tty_struct*) ; 
 int /*<<< orphan*/  serial_out (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rs_360_set_termios(struct tty_struct *tty, struct ktermios *old_termios)
{
	ser_info_t *info = (ser_info_t *)tty->driver_data;

	change_speed(info);

#ifdef modem_control
	/* Handle transition to B0 status */
	if ((old_termios->c_cflag & CBAUD) &&
	    !(tty->termios->c_cflag & CBAUD)) {
		info->MCR &= ~(UART_MCR_DTR|UART_MCR_RTS);
		local_irq_disable();
		serial_out(info, UART_MCR, info->MCR);
		local_irq_enable();
	}
	
	/* Handle transition away from B0 status */
	if (!(old_termios->c_cflag & CBAUD) &&
	    (tty->termios->c_cflag & CBAUD)) {
		info->MCR |= UART_MCR_DTR;
		if (!tty->hw_stopped ||
		    !(tty->termios->c_cflag & CRTSCTS)) {
			info->MCR |= UART_MCR_RTS;
		}
		local_irq_disable();
		serial_out(info, UART_MCR, info->MCR);
		local_irq_enable();
	}
	
	/* Handle turning off CRTSCTS */
	if ((old_termios->c_cflag & CRTSCTS) &&
	    !(tty->termios->c_cflag & CRTSCTS)) {
		tty->hw_stopped = 0;
		rs_360_start(tty);
	}
#endif

#if 0
	/*
	 * No need to wake up processes in open wait, since they
	 * sample the CLOCAL flag once, and don't recheck it.
	 * XXX  It's not clear whether the current behavior is correct
	 * or not.  Hence, this may change.....
	 */
	if (!(old_termios->c_cflag & CLOCAL) &&
	    (tty->termios->c_cflag & CLOCAL))
		wake_up_interruptible(&info->open_wait);
#endif
}