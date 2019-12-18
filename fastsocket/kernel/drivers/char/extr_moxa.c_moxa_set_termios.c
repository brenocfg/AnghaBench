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
struct tty_struct {struct moxa_port* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  open_wait; } ;
struct moxa_port {TYPE_1__ port; } ;
struct ktermios {int c_cflag; } ;

/* Variables and functions */
 int CLOCAL ; 
 scalar_t__ C_CLOCAL (struct tty_struct*) ; 
 int /*<<< orphan*/  moxa_set_tty_param (struct tty_struct*,struct ktermios*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void moxa_set_termios(struct tty_struct *tty,
		struct ktermios *old_termios)
{
	struct moxa_port *ch = tty->driver_data;

	if (ch == NULL)
		return;
	moxa_set_tty_param(tty, old_termios);
	if (!(old_termios->c_cflag & CLOCAL) && C_CLOCAL(tty))
		wake_up_interruptible(&ch->port.open_wait);
}