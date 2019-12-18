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
struct tty_port {int /*<<< orphan*/  mutex; } ;
struct uart_state {struct tty_port port; struct uart_port* uart_port; } ;
struct uart_port {scalar_t__ type; int flags; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* config_port ) (struct uart_port*,int) ;int /*<<< orphan*/  (* release_port ) (struct uart_port*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EBUSY ; 
 int EPERM ; 
 int ERESTARTSYS ; 
 scalar_t__ PORT_UNKNOWN ; 
 int UART_CONFIG_IRQ ; 
 int UART_CONFIG_TYPE ; 
 int UPF_AUTO_IRQ ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*) ; 
 int /*<<< orphan*/  stub2 (struct uart_port*,int) ; 
 int tty_port_users (struct tty_port*) ; 
 int /*<<< orphan*/  uart_shutdown (struct uart_state*) ; 
 int uart_startup (struct uart_state*,int) ; 

__attribute__((used)) static int uart_do_autoconfig(struct uart_state *state)
{
	struct uart_port *uport = state->uart_port;
	struct tty_port *port = &state->port;
	int flags, ret;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	/*
	 * Take the per-port semaphore.  This prevents count from
	 * changing, and hence any extra opens of the port while
	 * we're auto-configuring.
	 */
	if (mutex_lock_interruptible(&port->mutex))
		return -ERESTARTSYS;

	ret = -EBUSY;
	if (tty_port_users(port) == 1) {
		uart_shutdown(state);

		/*
		 * If we already have a port type configured,
		 * we must release its resources.
		 */
		if (uport->type != PORT_UNKNOWN)
			uport->ops->release_port(uport);

		flags = UART_CONFIG_TYPE;
		if (uport->flags & UPF_AUTO_IRQ)
			flags |= UART_CONFIG_IRQ;

		/*
		 * This will claim the ports resources if
		 * a port is found.
		 */
		uport->ops->config_port(uport, flags);

		ret = uart_startup(state, 1);
	}
	mutex_unlock(&port->mutex);
	return ret;
}