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
struct tty_struct {scalar_t__ hw_stopped; TYPE_1__* termios; struct r_port* driver_data; } ;
struct r_port {int /*<<< orphan*/  channel; } ;
struct ktermios {unsigned int c_cflag; } ;
struct TYPE_2__ {unsigned int c_cflag; } ;
typedef  int /*<<< orphan*/  CHANNEL_t ;

/* Variables and functions */
 int CBAUD ; 
 unsigned int CMSPAR ; 
 int CRTSCTS ; 
 unsigned int CS5 ; 
 unsigned int CS6 ; 
 unsigned int CSIZE ; 
 int /*<<< orphan*/  configure_r_port (struct tty_struct*,struct r_port*,struct ktermios*) ; 
 scalar_t__ rocket_paranoia_check (struct r_port*,char*) ; 
 int /*<<< orphan*/  rp_start (struct tty_struct*) ; 
 int /*<<< orphan*/  sClrDTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sClrRTS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sSetDTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sSetRTS (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rp_set_termios(struct tty_struct *tty,
			   struct ktermios *old_termios)
{
	struct r_port *info = tty->driver_data;
	CHANNEL_t *cp;
	unsigned cflag;

	if (rocket_paranoia_check(info, "rp_set_termios"))
		return;

	cflag = tty->termios->c_cflag;

	/*
	 * This driver doesn't support CS5 or CS6
	 */
	if (((cflag & CSIZE) == CS5) || ((cflag & CSIZE) == CS6))
		tty->termios->c_cflag =
		    ((cflag & ~CSIZE) | (old_termios->c_cflag & CSIZE));
	/* Or CMSPAR */
	tty->termios->c_cflag &= ~CMSPAR;

	configure_r_port(tty, info, old_termios);

	cp = &info->channel;

	/* Handle transition to B0 status */
	if ((old_termios->c_cflag & CBAUD) && !(tty->termios->c_cflag & CBAUD)) {
		sClrDTR(cp);
		sClrRTS(cp);
	}

	/* Handle transition away from B0 status */
	if (!(old_termios->c_cflag & CBAUD) && (tty->termios->c_cflag & CBAUD)) {
		if (!tty->hw_stopped || !(tty->termios->c_cflag & CRTSCTS))
			sSetRTS(cp);
		sSetDTR(cp);
	}

	if ((old_termios->c_cflag & CRTSCTS) && !(tty->termios->c_cflag & CRTSCTS)) {
		tty->hw_stopped = 0;
		rp_start(tty);
	}
}