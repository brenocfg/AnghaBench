#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct uart_state {struct uart_port* uart_port; } ;
struct uart_port {int /*<<< orphan*/  lock; } ;
struct tty_struct {struct uart_state* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  __uart_start (struct tty_struct*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void uart_start(struct tty_struct *tty)
{
	struct uart_state *state = tty->driver_data;
	struct uart_port *port = state->uart_port;
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);
	__uart_start(tty);
	spin_unlock_irqrestore(&port->lock, flags);
}