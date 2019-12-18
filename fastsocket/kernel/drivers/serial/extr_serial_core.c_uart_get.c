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
struct tty_port {int /*<<< orphan*/  mutex; int /*<<< orphan*/  count; } ;
struct uart_state {TYPE_1__* uart_port; struct tty_port port; } ;
struct uart_driver {struct uart_state* state; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int ENXIO ; 
 int ERESTARTSYS ; 
 struct uart_state* ERR_PTR (int) ; 
 int UPF_DEAD ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct uart_state *uart_get(struct uart_driver *drv, int line)
{
	struct uart_state *state;
	struct tty_port *port;
	int ret = 0;

	state = drv->state + line;
	port = &state->port;
	if (mutex_lock_interruptible(&port->mutex)) {
		ret = -ERESTARTSYS;
		goto err;
	}

	port->count++;
	if (!state->uart_port || state->uart_port->flags & UPF_DEAD) {
		ret = -ENXIO;
		goto err_unlock;
	}
	return state;

 err_unlock:
	port->count--;
	mutex_unlock(&port->mutex);
 err:
	return ERR_PTR(ret);
}