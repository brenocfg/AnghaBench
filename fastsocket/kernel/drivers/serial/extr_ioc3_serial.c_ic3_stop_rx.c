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
struct ioc3_port {int /*<<< orphan*/  ip_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  INPUT_ENABLE ; 
 struct ioc3_port* get_ioc3_port (struct uart_port*) ; 

__attribute__((used)) static void ic3_stop_rx(struct uart_port *the_port)
{
	struct ioc3_port *port = get_ioc3_port(the_port);

	if (port)
		port->ip_flags &= ~INPUT_ENABLE;
}