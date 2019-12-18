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
struct TYPE_6__ {int flags; TYPE_1__* tty; } ;
struct gs_port {int /*<<< orphan*/  driver_lock; TYPE_3__ port; TYPE_2__* rd; int /*<<< orphan*/ * xmit_buf; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* shutdown_port ) (struct gs_port*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ASYNC_INITIALIZED ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct gs_port*) ; 

__attribute__((used)) static void gs_shutdown_port (struct gs_port *port)
{
	unsigned long flags;

	func_enter();
	
	if (!port) return;
	
	if (!(port->port.flags & ASYNC_INITIALIZED))
		return;

	spin_lock_irqsave(&port->driver_lock, flags);

	if (port->xmit_buf) {
		free_page((unsigned long) port->xmit_buf);
		port->xmit_buf = NULL;
	}

	if (port->port.tty)
		set_bit(TTY_IO_ERROR, &port->port.tty->flags);

	port->rd->shutdown_port (port);

	port->port.flags &= ~ASYNC_INITIALIZED;
	spin_unlock_irqrestore(&port->driver_lock, flags);

	func_exit();
}