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
struct tty_struct {TYPE_1__* termios; struct sdio_uart_port* driver_data; } ;
struct sdio_uart_port {int /*<<< orphan*/  func; scalar_t__ x_char; } ;
struct TYPE_2__ {int c_cflag; } ;

/* Variables and functions */
 int CRTSCTS ; 
 scalar_t__ I_IXOFF (struct tty_struct*) ; 
 scalar_t__ START_CHAR (struct tty_struct*) ; 
 int /*<<< orphan*/  TIOCM_RTS ; 
 scalar_t__ sdio_uart_claim_func (struct sdio_uart_port*) ; 
 int /*<<< orphan*/  sdio_uart_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_uart_release_func (struct sdio_uart_port*) ; 
 int /*<<< orphan*/  sdio_uart_set_mctrl (struct sdio_uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_uart_start_tx (struct sdio_uart_port*) ; 

__attribute__((used)) static void sdio_uart_unthrottle(struct tty_struct *tty)
{
	struct sdio_uart_port *port = tty->driver_data;

	if (!I_IXOFF(tty) && !(tty->termios->c_cflag & CRTSCTS))
		return;

	if (sdio_uart_claim_func(port) != 0)
		return;

	if (I_IXOFF(tty)) {
		if (port->x_char) {
			port->x_char = 0;
		} else {
			port->x_char = START_CHAR(tty);
			sdio_uart_start_tx(port);
		}
	}

	if (tty->termios->c_cflag & CRTSCTS)
		sdio_uart_set_mctrl(port, TIOCM_RTS);

	sdio_uart_irq(port->func);
	sdio_uart_release_func(port);
}