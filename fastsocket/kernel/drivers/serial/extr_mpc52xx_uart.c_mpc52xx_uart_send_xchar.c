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
struct uart_port {char x_char; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* start_tx ) (struct uart_port*) ;} ;

/* Variables and functions */
 TYPE_1__* psc_ops ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*) ; 

__attribute__((used)) static void
mpc52xx_uart_send_xchar(struct uart_port *port, char ch)
{
	unsigned long flags;
	spin_lock_irqsave(&port->lock, flags);

	port->x_char = ch;
	if (ch) {
		/* Make sure tx interrupts are on */
		/* Truly necessary ??? They should be anyway */
		psc_ops->start_tx(port);
	}

	spin_unlock_irqrestore(&port->lock, flags);
}