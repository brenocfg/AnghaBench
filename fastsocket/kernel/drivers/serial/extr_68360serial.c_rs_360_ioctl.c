#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int flags; int /*<<< orphan*/  name; scalar_t__ driver_data; } ;
struct serial_icounter_struct {int /*<<< orphan*/  dcd; int /*<<< orphan*/  rng; int /*<<< orphan*/  dsr; int /*<<< orphan*/  cts; } ;
struct file {int dummy; } ;
struct async_icount {int /*<<< orphan*/  dcd; int /*<<< orphan*/  rng; int /*<<< orphan*/  dsr; int /*<<< orphan*/  cts; } ;
struct TYPE_9__ {TYPE_1__* state; int /*<<< orphan*/  delta_msr_wait; } ;
typedef  TYPE_2__ ser_info_t ;
struct TYPE_8__ {struct async_icount icount; } ;

/* Variables and functions */
 int EINTR ; 
 int EIO ; 
 int ENODEV ; 
 int ENOIOCTLCMD ; 
 int ERESTARTSYS ; 
#define  TCSBRK 134 
#define  TCSBRKP 133 
#define  TIOCCBRK 132 
#define  TIOCGICOUNT 131 
#define  TIOCMIWAIT 130 
 unsigned long TIOCM_CD ; 
 unsigned long TIOCM_CTS ; 
 unsigned long TIOCM_DSR ; 
 unsigned long TIOCM_RNG ; 
#define  TIOCSBRK 129 
#define  TIOCSERGETLSR 128 
 int TTY_IO_ERROR ; 
 int /*<<< orphan*/  begin_break (TYPE_2__*) ; 
 struct async_icount cprev ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  end_break (TYPE_2__*) ; 
 int get_lsr_info (TYPE_2__*,unsigned int*) ; 
 int /*<<< orphan*/  interruptible_sleep_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  put_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_break (TYPE_2__*,unsigned long) ; 
 scalar_t__ serial_paranoia_check (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 
 int tty_check_change (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_wait_until_sent (struct tty_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rs_360_ioctl(struct tty_struct *tty, struct file * file,
		    unsigned int cmd, unsigned long arg)
{
	int error;
	ser_info_t *info = (ser_info_t *)tty->driver_data;
	int retval;
	struct async_icount cnow; 
	/* struct async_icount_24 cnow;*/ 	/* kernel counter temps */
	struct serial_icounter_struct *p_cuser;	/* user space */

	if (serial_paranoia_check(info, tty->name, "rs_ioctl"))
		return -ENODEV;

	if ((cmd != TIOCMIWAIT) && (cmd != TIOCGICOUNT)) {
		if (tty->flags & (1 << TTY_IO_ERROR))
		    return -EIO;
	}
	
	switch (cmd) {
		case TCSBRK:	/* SVID version: non-zero arg --> no break */
			retval = tty_check_change(tty);
			if (retval)
				return retval;
			tty_wait_until_sent(tty, 0);
			if (signal_pending(current))
				return -EINTR;
			if (!arg) {
				send_break(info, 250);	/* 1/4 second */
				if (signal_pending(current))
					return -EINTR;
			}
			return 0;
		case TCSBRKP:	/* support for POSIX tcsendbreak() */
			retval = tty_check_change(tty);
			if (retval)
				return retval;
			tty_wait_until_sent(tty, 0);
			if (signal_pending(current))
				return -EINTR;
			send_break(info, arg ? arg*100 : 250);
			if (signal_pending(current))
				return -EINTR;
			return 0;
		case TIOCSBRK:
			retval = tty_check_change(tty);
			if (retval)
				return retval;
			tty_wait_until_sent(tty, 0);
			begin_break(info);
			return 0;
		case TIOCCBRK:
			retval = tty_check_change(tty);
			if (retval)
				return retval;
			end_break(info);
			return 0;
#ifdef maybe
		case TIOCSERGETLSR: /* Get line status register */
			return get_lsr_info(info, (unsigned int *) arg);
#endif
		/*
		 * Wait for any of the 4 modem inputs (DCD,RI,DSR,CTS) to change
		 * - mask passed in arg for lines of interest
 		 *   (use |'ed TIOCM_RNG/DSR/CD/CTS for masking)
		 * Caller should use TIOCGICOUNT to see which one it was
		 */
		 case TIOCMIWAIT:
#ifdef modem_control
			local_irq_disable();
			/* note the counters on entry */
			cprev = info->state->icount;
			local_irq_enable();
			while (1) {
				interruptible_sleep_on(&info->delta_msr_wait);
				/* see if a signal did it */
				if (signal_pending(current))
					return -ERESTARTSYS;
				local_irq_disable();
				cnow = info->state->icount; /* atomic copy */
				local_irq_enable();
				if (cnow.rng == cprev.rng && cnow.dsr == cprev.dsr && 
				    cnow.dcd == cprev.dcd && cnow.cts == cprev.cts)
					return -EIO; /* no change => error */
				if ( ((arg & TIOCM_RNG) && (cnow.rng != cprev.rng)) ||
				     ((arg & TIOCM_DSR) && (cnow.dsr != cprev.dsr)) ||
				     ((arg & TIOCM_CD)  && (cnow.dcd != cprev.dcd)) ||
				     ((arg & TIOCM_CTS) && (cnow.cts != cprev.cts)) ) {
					return 0;
				}
				cprev = cnow;
			}
			/* NOTREACHED */
#else
			return 0;
#endif

		/* 
		 * Get counter of input serial line interrupts (DCD,RI,DSR,CTS)
		 * Return: write counters to the user passed counter struct
		 * NB: both 1->0 and 0->1 transitions are counted except for
		 *     RI where only 0->1 is counted.
		 */
		case TIOCGICOUNT:
			local_irq_disable();
			cnow = info->state->icount;
			local_irq_enable();
			p_cuser = (struct serial_icounter_struct *) arg;
/* 			error = put_user(cnow.cts, &p_cuser->cts); */
/* 			if (error) return error; */
/* 			error = put_user(cnow.dsr, &p_cuser->dsr); */
/* 			if (error) return error; */
/* 			error = put_user(cnow.rng, &p_cuser->rng); */
/* 			if (error) return error; */
/* 			error = put_user(cnow.dcd, &p_cuser->dcd); */
/* 			if (error) return error; */

			put_user(cnow.cts, &p_cuser->cts);
			put_user(cnow.dsr, &p_cuser->dsr);
			put_user(cnow.rng, &p_cuser->rng);
			put_user(cnow.dcd, &p_cuser->dcd);
			return 0;

		default:
			return -ENOIOCTLCMD;
		}
	return 0;
}