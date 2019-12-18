#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ buf; } ;
struct uart_state {TYPE_2__ xmit; struct uart_port* uart_port; } ;
struct uart_port {TYPE_1__* ops; } ;
struct tty_struct {int /*<<< orphan*/  hw_stopped; int /*<<< orphan*/  stopped; struct uart_state* driver_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* start_tx ) (struct uart_port*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct uart_port*) ; 
 int /*<<< orphan*/  uart_circ_empty (TYPE_2__*) ; 

__attribute__((used)) static void __uart_start(struct tty_struct *tty)
{
	struct uart_state *state = tty->driver_data;
	struct uart_port *port = state->uart_port;

	if (!uart_circ_empty(&state->xmit) && state->xmit.buf &&
	    !tty->stopped && !tty->hw_stopped)
		port->ops->start_tx(port);
}