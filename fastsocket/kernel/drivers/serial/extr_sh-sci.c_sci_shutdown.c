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
struct uart_port {int dummy; } ;
struct sci_port {int /*<<< orphan*/  (* disable ) (struct uart_port*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  sci_free_irq (struct sci_port*) ; 
 int /*<<< orphan*/  sci_stop_rx (struct uart_port*) ; 
 int /*<<< orphan*/  sci_stop_tx (struct uart_port*) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*) ; 
 struct sci_port* to_sci_port (struct uart_port*) ; 

__attribute__((used)) static void sci_shutdown(struct uart_port *port)
{
	struct sci_port *s = to_sci_port(port);

	sci_stop_rx(port);
	sci_stop_tx(port);
	sci_free_irq(s);

	if (s->disable)
		s->disable(port);
}