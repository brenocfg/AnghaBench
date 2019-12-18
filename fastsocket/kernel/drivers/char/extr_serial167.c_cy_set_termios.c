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
struct tty_struct {TYPE_1__* termios; scalar_t__ stopped; int /*<<< orphan*/  name; struct cyclades_port* driver_data; } ;
struct ktermios {int c_cflag; } ;
struct cyclades_port {int /*<<< orphan*/  open_wait; } ;
struct TYPE_2__ {int c_cflag; } ;

/* Variables and functions */
 int CLOCAL ; 
 int CRTSCTS ; 
 int /*<<< orphan*/  config_setup (struct cyclades_port*) ; 
 int /*<<< orphan*/  cy_start (struct tty_struct*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cy_set_termios(struct tty_struct *tty, struct ktermios *old_termios)
{
	struct cyclades_port *info = tty->driver_data;

#ifdef SERIAL_DEBUG_OTHER
	printk("cy_set_termios %s\n", tty->name);
#endif

	if (tty->termios->c_cflag == old_termios->c_cflag)
		return;
	config_setup(info);

	if ((old_termios->c_cflag & CRTSCTS) &&
	    !(tty->termios->c_cflag & CRTSCTS)) {
		tty->stopped = 0;
		cy_start(tty);
	}
#ifdef tytso_patch_94Nov25_1726
	if (!(old_termios->c_cflag & CLOCAL) &&
	    (tty->termios->c_cflag & CLOCAL))
		wake_up_interruptible(&info->open_wait);
#endif
}