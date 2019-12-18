#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tty_struct {int flags; int /*<<< orphan*/  name; scalar_t__ driver_data; } ;
struct serial_struct {int dummy; } ;
struct m68k_serial {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int EIO ; 
 int ENODEV ; 
 int ENOIOCTLCMD ; 
#define  TCSBRK 133 
#define  TCSBRKP 132 
#define  TIOCGSERIAL 131 
 unsigned int TIOCSERCONFIG ; 
#define  TIOCSERGETLSR 130 
#define  TIOCSERGSTRUCT 129 
 unsigned int TIOCSERGWILD ; 
 unsigned int TIOCSERSWILD ; 
#define  TIOCSSERIAL 128 
 int TTY_IO_ERROR ; 
 int /*<<< orphan*/  VERIFY_WRITE ; 
 int /*<<< orphan*/  access_ok (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  copy_to_user (struct m68k_serial*,struct m68k_serial*,int) ; 
 int get_lsr_info (struct m68k_serial*,unsigned int*) ; 
 int get_serial_info (struct m68k_serial*,struct serial_struct*) ; 
 int /*<<< orphan*/  send_break (struct m68k_serial*,unsigned long) ; 
 scalar_t__ serial_paranoia_check (struct m68k_serial*,int /*<<< orphan*/ ,char*) ; 
 int set_serial_info (struct m68k_serial*,struct serial_struct*) ; 
 int tty_check_change (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_wait_until_sent (struct tty_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rs_ioctl(struct tty_struct *tty, struct file * file,
		    unsigned int cmd, unsigned long arg)
{
	int error;
	struct m68k_serial * info = (struct m68k_serial *)tty->driver_data;
	int retval;

	if (serial_paranoia_check(info, tty->name, "rs_ioctl"))
		return -ENODEV;

	if ((cmd != TIOCGSERIAL) && (cmd != TIOCSSERIAL) &&
	    (cmd != TIOCSERCONFIG) && (cmd != TIOCSERGWILD)  &&
	    (cmd != TIOCSERSWILD) && (cmd != TIOCSERGSTRUCT)) {
		if (tty->flags & (1 << TTY_IO_ERROR))
		    return -EIO;
	}
	
	switch (cmd) {
		case TCSBRK:	/* SVID version: non-zero arg --> no break */
			retval = tty_check_change(tty);
			if (retval)
				return retval;
			tty_wait_until_sent(tty, 0);
			if (!arg)
				send_break(info, 250);	/* 1/4 second */
			return 0;
		case TCSBRKP:	/* support for POSIX tcsendbreak() */
			retval = tty_check_change(tty);
			if (retval)
				return retval;
			tty_wait_until_sent(tty, 0);
			send_break(info, arg ? arg*(100) : 250);
			return 0;
		case TIOCGSERIAL:
			if (access_ok(VERIFY_WRITE, (void *) arg,
						sizeof(struct serial_struct)))
				return get_serial_info(info,
					       (struct serial_struct *) arg);
			return -EFAULT;
		case TIOCSSERIAL:
			return set_serial_info(info,
					       (struct serial_struct *) arg);
		case TIOCSERGETLSR: /* Get line status register */
			if (access_ok(VERIFY_WRITE, (void *) arg,
						sizeof(unsigned int)))
				return get_lsr_info(info, (unsigned int *) arg);
			return -EFAULT;
		case TIOCSERGSTRUCT:
			if (!access_ok(VERIFY_WRITE, (void *) arg,
						sizeof(struct m68k_serial)))
				return -EFAULT;
			copy_to_user((struct m68k_serial *) arg,
				    info, sizeof(struct m68k_serial));
			return 0;
			
		default:
			return -ENOIOCTLCMD;
		}
	return 0;
}