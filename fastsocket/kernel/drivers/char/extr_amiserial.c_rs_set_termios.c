#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {TYPE_1__* termios; scalar_t__ hw_stopped; int /*<<< orphan*/  flags; struct async_struct* driver_data; } ;
struct ktermios {unsigned int c_cflag; } ;
struct async_struct {int MCR; int /*<<< orphan*/  open_wait; } ;
struct TYPE_2__ {unsigned int c_cflag; } ;

/* Variables and functions */
 unsigned int CBAUD ; 
 int CLOCAL ; 
 int CRTSCTS ; 
 int SER_DTR ; 
 int SER_RTS ; 
 int /*<<< orphan*/  TTY_THROTTLED ; 
 int /*<<< orphan*/  change_speed (struct async_struct*,struct ktermios*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  rs_start (struct tty_struct*) ; 
 int /*<<< orphan*/  rtsdtr_ctrl (int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rs_set_termios(struct tty_struct *tty, struct ktermios *old_termios)
{
	struct async_struct *info = tty->driver_data;
	unsigned long flags;
	unsigned int cflag = tty->termios->c_cflag;

	change_speed(info, old_termios);

	/* Handle transition to B0 status */
	if ((old_termios->c_cflag & CBAUD) &&
	    !(cflag & CBAUD)) {
		info->MCR &= ~(SER_DTR|SER_RTS);
		local_irq_save(flags);
		rtsdtr_ctrl(info->MCR);
		local_irq_restore(flags);
	}

	/* Handle transition away from B0 status */
	if (!(old_termios->c_cflag & CBAUD) &&
	    (cflag & CBAUD)) {
		info->MCR |= SER_DTR;
		if (!(tty->termios->c_cflag & CRTSCTS) || 
		    !test_bit(TTY_THROTTLED, &tty->flags)) {
			info->MCR |= SER_RTS;
		}
		local_irq_save(flags);
		rtsdtr_ctrl(info->MCR);
		local_irq_restore(flags);
	}

	/* Handle turning off CRTSCTS */
	if ((old_termios->c_cflag & CRTSCTS) &&
	    !(tty->termios->c_cflag & CRTSCTS)) {
		tty->hw_stopped = 0;
		rs_start(tty);
	}

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