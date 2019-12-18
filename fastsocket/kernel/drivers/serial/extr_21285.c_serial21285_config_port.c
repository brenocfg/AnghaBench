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
struct uart_port {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_21285 ; 
 int UART_CONFIG_TYPE ; 
 scalar_t__ serial21285_request_port (struct uart_port*) ; 

__attribute__((used)) static void serial21285_config_port(struct uart_port *port, int flags)
{
	if (flags & UART_CONFIG_TYPE && serial21285_request_port(port) == 0)
		port->type = PORT_21285;
}