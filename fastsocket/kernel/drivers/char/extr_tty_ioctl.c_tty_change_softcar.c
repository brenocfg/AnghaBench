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
struct tty_struct {int /*<<< orphan*/  termios_mutex; struct ktermios* termios; TYPE_1__* ops; } ;
struct ktermios {int c_cflag; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_termios ) (struct tty_struct*,struct ktermios*) ;} ;

/* Variables and functions */
 int CLOCAL ; 
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*,struct ktermios*) ; 

__attribute__((used)) static int tty_change_softcar(struct tty_struct *tty, int arg)
{
	int ret = 0;
	int bit = arg ? CLOCAL : 0;
	struct ktermios old;

	mutex_lock(&tty->termios_mutex);
	old = *tty->termios;
	tty->termios->c_cflag &= ~CLOCAL;
	tty->termios->c_cflag |= bit;
	if (tty->ops->set_termios)
		tty->ops->set_termios(tty, &old);
	if ((tty->termios->c_cflag & CLOCAL) != bit)
		ret = -EINVAL;
	mutex_unlock(&tty->termios_mutex);
	return ret;
}