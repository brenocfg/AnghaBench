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
struct uart_state {int pm_state; struct uart_port* uart_port; } ;
struct uart_port {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pm ) (struct uart_port*,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct uart_port*,int,int) ; 

__attribute__((used)) static void uart_change_pm(struct uart_state *state, int pm_state)
{
	struct uart_port *port = state->uart_port;

	if (state->pm_state != pm_state) {
		if (port->ops->pm)
			port->ops->pm(port, pm_state, state->pm_state);
		state->pm_state = pm_state;
	}
}