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
struct tty_port {int /*<<< orphan*/  flags; struct tty_struct* tty; } ;
struct uart_state {struct uart_port* uart_port; struct tty_port port; } ;
struct uart_port {scalar_t__ type; TYPE_1__* ops; } ;
struct tty_struct {struct ktermios* termios; } ;
struct ktermios {int c_cflag; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_termios ) (struct uart_port*,struct ktermios*,struct ktermios*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNCB_CHECK_CD ; 
 int /*<<< orphan*/  ASYNCB_CTS_FLOW ; 
 int /*<<< orphan*/  ASYNCB_DSR_FLOW ; 
 int CDTRDSR ; 
 int CLOCAL ; 
 int CRTSCTS ; 
 scalar_t__ PORT_UNKNOWN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*,struct ktermios*,struct ktermios*) ; 

__attribute__((used)) static void
uart_change_speed(struct uart_state *state, struct ktermios *old_termios)
{
	struct tty_port *port = &state->port;
	struct tty_struct *tty = port->tty;
	struct uart_port *uport = state->uart_port;
	struct ktermios *termios;

	/*
	 * If we have no tty, termios, or the port does not exist,
	 * then we can't set the parameters for this port.
	 */
	if (!tty || !tty->termios || uport->type == PORT_UNKNOWN)
		return;

	termios = tty->termios;

	/*
	 * Set flags based on termios cflag
	 */
	if (termios->c_cflag & CRTSCTS)
		set_bit(ASYNCB_CTS_FLOW, &port->flags);
	else
		clear_bit(ASYNCB_CTS_FLOW, &port->flags);

	if (termios->c_cflag & CDTRDSR)
		set_bit(ASYNCB_DSR_FLOW, &port->flags);
	else
		clear_bit(ASYNCB_DSR_FLOW, &port->flags);

	if (termios->c_cflag & CLOCAL)
		clear_bit(ASYNCB_CHECK_CD, &port->flags);
	else
		set_bit(ASYNCB_CHECK_CD, &port->flags);

	uport->ops->set_termios(uport, termios, old_termios);
}