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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct uart_sunsab_port {TYPE_1__ port; } ;
struct uart_port {int dummy; } ;
struct ktermios {int /*<<< orphan*/  c_iflag; int /*<<< orphan*/  c_cflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sunsab_convert_to_sab (struct uart_sunsab_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int /*<<< orphan*/ ,int) ; 
 unsigned int uart_get_divisor (struct uart_port*,unsigned int) ; 

__attribute__((used)) static void sunsab_set_termios(struct uart_port *port, struct ktermios *termios,
			       struct ktermios *old)
{
	struct uart_sunsab_port *up = (struct uart_sunsab_port *) port;
	unsigned long flags;
	unsigned int baud = uart_get_baud_rate(port, termios, old, 0, 4000000);
	unsigned int quot = uart_get_divisor(port, baud);

	spin_lock_irqsave(&up->port.lock, flags);
	sunsab_convert_to_sab(up, termios->c_cflag, termios->c_iflag, baud, quot);
	spin_unlock_irqrestore(&up->port.lock, flags);
}