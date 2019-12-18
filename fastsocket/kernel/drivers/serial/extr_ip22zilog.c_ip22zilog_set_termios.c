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
struct uart_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct uart_ip22zilog_port {TYPE_1__ port; int /*<<< orphan*/  flags; } ;
struct ktermios {int /*<<< orphan*/  c_cflag; int /*<<< orphan*/  c_iflag; } ;

/* Variables and functions */
 int BPS_TO_BRG (int,int) ; 
 int /*<<< orphan*/  IP22ZILOG_FLAG_MODEM_STATUS ; 
 scalar_t__ UART_ENABLE_MS (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZILOG_CHANNEL_FROM_PORT (struct uart_port*) ; 
 int ZS_CLOCK ; 
 int ZS_CLOCK_DIVISOR ; 
 int /*<<< orphan*/  ip22zilog_convert_to_zs (struct uart_ip22zilog_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ip22zilog_maybe_update_regs (struct uart_ip22zilog_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int,int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ip22zilog_set_termios(struct uart_port *port, struct ktermios *termios,
		      struct ktermios *old)
{
	struct uart_ip22zilog_port *up = (struct uart_ip22zilog_port *) port;
	unsigned long flags;
	int baud, brg;

	baud = uart_get_baud_rate(port, termios, old, 1200, 76800);

	spin_lock_irqsave(&up->port.lock, flags);

	brg = BPS_TO_BRG(baud, ZS_CLOCK / ZS_CLOCK_DIVISOR);

	ip22zilog_convert_to_zs(up, termios->c_cflag, termios->c_iflag, brg);

	if (UART_ENABLE_MS(&up->port, termios->c_cflag))
		up->flags |= IP22ZILOG_FLAG_MODEM_STATUS;
	else
		up->flags &= ~IP22ZILOG_FLAG_MODEM_STATUS;

	ip22zilog_maybe_update_regs(up, ZILOG_CHANNEL_FROM_PORT(port));
	uart_update_timeout(port, termios->c_cflag, baud);

	spin_unlock_irqrestore(&up->port.lock, flags);
}