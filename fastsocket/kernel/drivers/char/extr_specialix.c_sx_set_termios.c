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
struct tty_struct {scalar_t__ hw_stopped; TYPE_1__* termios; int /*<<< orphan*/  name; struct specialix_port* driver_data; } ;
struct specialix_port {int /*<<< orphan*/  lock; } ;
struct specialix_board {int dummy; } ;
struct ktermios {int c_cflag; } ;
struct TYPE_2__ {int c_cflag; } ;

/* Variables and functions */
 int CRTSCTS ; 
 struct specialix_board* port_Board (struct specialix_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sx_change_speed (struct specialix_board*,struct specialix_port*) ; 
 scalar_t__ sx_paranoia_check (struct specialix_port*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sx_start (struct tty_struct*) ; 

__attribute__((used)) static void sx_set_termios(struct tty_struct *tty,
					struct ktermios *old_termios)
{
	struct specialix_port *port = tty->driver_data;
	unsigned long flags;
	struct specialix_board  *bp;

	if (sx_paranoia_check(port, tty->name, "sx_set_termios"))
		return;

	bp = port_Board(port);
	spin_lock_irqsave(&port->lock, flags);
	sx_change_speed(port_Board(port), port);
	spin_unlock_irqrestore(&port->lock, flags);

	if ((old_termios->c_cflag & CRTSCTS) &&
	    !(tty->termios->c_cflag & CRTSCTS)) {
		tty->hw_stopped = 0;
		sx_start(tty);
	}
}