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
struct tty_port {int /*<<< orphan*/  delta_msr_wait; int /*<<< orphan*/  open_wait; int /*<<< orphan*/  lock; int /*<<< orphan*/ * tty; int /*<<< orphan*/  flags; scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_NORMAL_ACTIVE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_kref_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_shutdown (struct tty_port*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void tty_port_hangup(struct tty_port *port)
{
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);
	port->count = 0;
	port->flags &= ~ASYNC_NORMAL_ACTIVE;
	if (port->tty)
		tty_kref_put(port->tty);
	port->tty = NULL;
	spin_unlock_irqrestore(&port->lock, flags);
	wake_up_interruptible(&port->open_wait);
	wake_up_interruptible(&port->delta_msr_wait);
	tty_port_shutdown(port);
}