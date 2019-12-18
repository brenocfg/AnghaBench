#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct tty_struct* tty; } ;
struct uart_state {struct uart_port* uart_port; TYPE_2__ port; } ;
struct uart_port {TYPE_3__* cons; } ;
struct tty_struct {int flags; TYPE_1__* termios; } ;
struct TYPE_6__ {int cflag; } ;
struct TYPE_4__ {int c_cflag; } ;

/* Variables and functions */
 int CBAUD ; 
 int TIOCM_DTR ; 
 int TIOCM_RTS ; 
 int TTY_IO_ERROR ; 
 int /*<<< orphan*/  uart_change_speed (struct uart_state*,int /*<<< orphan*/ *) ; 
 scalar_t__ uart_console (struct uart_port*) ; 
 int /*<<< orphan*/  uart_set_mctrl (struct uart_port*,int) ; 

__attribute__((used)) static void uart_update_termios(struct uart_state *state)
{
	struct tty_struct *tty = state->port.tty;
	struct uart_port *port = state->uart_port;

	if (uart_console(port) && port->cons->cflag) {
		tty->termios->c_cflag = port->cons->cflag;
		port->cons->cflag = 0;
	}

	/*
	 * If the device failed to grab its irq resources,
	 * or some other error occurred, don't try to talk
	 * to the port hardware.
	 */
	if (!(tty->flags & (1 << TTY_IO_ERROR))) {
		/*
		 * Make termios settings take effect.
		 */
		uart_change_speed(state, NULL);

		/*
		 * And finally enable the RTS and DTR signals.
		 */
		if (tty->termios->c_cflag & CBAUD)
			uart_set_mctrl(port, TIOCM_DTR | TIOCM_RTS);
	}
}