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
struct uart_state {int /*<<< orphan*/  uart_port; } ;
struct tty_struct {TYPE_1__* termios; struct uart_state* driver_data; } ;
struct TYPE_2__ {int c_cflag; } ;

/* Variables and functions */
 int CDTRDSR ; 
 int CRTSCTS ; 
 scalar_t__ I_IXOFF (struct tty_struct*) ; 
 int /*<<< orphan*/  STOP_CHAR (struct tty_struct*) ; 
 int /*<<< orphan*/  TIOCM_DTR ; 
 int /*<<< orphan*/  TIOCM_RTS ; 
 int /*<<< orphan*/  uart_clear_mctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_send_xchar (struct tty_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uart_throttle(struct tty_struct *tty)
{
	struct uart_state *state = tty->driver_data;

	if (I_IXOFF(tty))
		uart_send_xchar(tty, STOP_CHAR(tty));

	if (tty->termios->c_cflag & CRTSCTS)
		uart_clear_mctrl(state->uart_port, TIOCM_RTS);
	if (tty->termios->c_cflag & CDTRDSR)
		uart_clear_mctrl(state->uart_port, TIOCM_DTR);
}