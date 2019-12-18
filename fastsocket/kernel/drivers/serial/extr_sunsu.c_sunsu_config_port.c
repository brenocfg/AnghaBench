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
struct uart_sunsu_port {int /*<<< orphan*/  type_probed; } ;
struct uart_port {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int UART_CONFIG_TYPE ; 

__attribute__((used)) static void sunsu_config_port(struct uart_port *port, int flags)
{
	struct uart_sunsu_port *up = (struct uart_sunsu_port *) port;

	if (flags & UART_CONFIG_TYPE) {
		/*
		 * We are supposed to call autoconfig here, but this requires
		 * splitting all the OBP probing crap from the UART probing.
		 * We'll do it when we kill sunsu.c altogether.
		 */
		port->type = up->type_probed;	/* XXX */
	}
}