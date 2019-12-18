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
struct tty_struct {int index; TYPE_1__* driver; struct ktermios* termios; } ;
struct ktermios {int dummy; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/ ** termios; } ;

/* Variables and functions */
 int TTY_DRIVER_RESET_TERMIOS ; 
 int /*<<< orphan*/  kfree (struct ktermios*) ; 

void tty_free_termios(struct tty_struct *tty)
{
	struct ktermios *tp;
	int idx = tty->index;
	/* Kill this flag and push into drivers for locking etc */
	if (tty->driver->flags & TTY_DRIVER_RESET_TERMIOS) {
		/* FIXME: Locking on ->termios array */
		tp = tty->termios;
		tty->driver->termios[idx] = NULL;
		kfree(tp);
	}
}