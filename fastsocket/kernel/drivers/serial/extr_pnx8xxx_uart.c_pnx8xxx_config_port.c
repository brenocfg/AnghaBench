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
struct uart_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct pnx8xxx_port {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_PNX8XXX ; 
 int UART_CONFIG_TYPE ; 
 scalar_t__ pnx8xxx_request_port (TYPE_1__*) ; 

__attribute__((used)) static void pnx8xxx_config_port(struct uart_port *port, int flags)
{
	struct pnx8xxx_port *sport = (struct pnx8xxx_port *)port;

	if (flags & UART_CONFIG_TYPE &&
	    pnx8xxx_request_port(&sport->port) == 0)
		sport->port.type = PORT_PNX8XXX;
}