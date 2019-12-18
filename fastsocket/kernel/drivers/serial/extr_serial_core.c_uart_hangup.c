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
struct tty_port {int flags; int /*<<< orphan*/  mutex; int /*<<< orphan*/  delta_msr_wait; int /*<<< orphan*/  open_wait; scalar_t__ count; } ;
struct uart_state {TYPE_1__* uart_port; struct tty_port port; } ;
struct tty_struct {struct uart_state* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  line; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNCB_NORMAL_ACTIVE ; 
 int ASYNC_NORMAL_ACTIVE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  kernel_locked () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_port_tty_set (struct tty_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  uart_shutdown (struct uart_state*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uart_hangup(struct tty_struct *tty)
{
	struct uart_state *state = tty->driver_data;
	struct tty_port *port = &state->port;

	BUG_ON(!kernel_locked());
	pr_debug("uart_hangup(%d)\n", state->uart_port->line);

	mutex_lock(&port->mutex);
	if (port->flags & ASYNC_NORMAL_ACTIVE) {
		uart_flush_buffer(tty);
		uart_shutdown(state);
		port->count = 0;
		clear_bit(ASYNCB_NORMAL_ACTIVE, &port->flags);
		tty_port_tty_set(port, NULL);
		wake_up_interruptible(&port->open_wait);
		wake_up_interruptible(&port->delta_msr_wait);
	}
	mutex_unlock(&port->mutex);
}