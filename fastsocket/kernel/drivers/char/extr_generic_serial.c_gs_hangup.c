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
struct tty_struct {struct gs_port* driver_data; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  open_wait; int /*<<< orphan*/  lock; scalar_t__ count; struct tty_struct* tty; } ;
struct gs_port {TYPE_1__ port; } ;

/* Variables and functions */
 int ASYNC_NORMAL_ACTIVE ; 
 int GS_ACTIVE ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 int /*<<< orphan*/  gs_shutdown_port (struct gs_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void gs_hangup(struct tty_struct *tty)
{
	struct gs_port *port;
	unsigned long flags;

	func_enter ();

	port = tty->driver_data;
	tty = port->port.tty;
	if (!tty) 
		return;

	gs_shutdown_port (port);
	spin_lock_irqsave(&port->port.lock, flags);
	port->port.flags &= ~(ASYNC_NORMAL_ACTIVE|GS_ACTIVE);
	port->port.tty = NULL;
	port->port.count = 0;
	spin_unlock_irqrestore(&port->port.lock, flags);

	wake_up_interruptible(&port->port.open_wait);
	func_exit ();
}