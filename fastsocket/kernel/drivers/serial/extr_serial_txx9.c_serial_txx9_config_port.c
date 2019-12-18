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
struct TYPE_4__ {scalar_t__ line; TYPE_1__* cons; int /*<<< orphan*/  fifosize; } ;
struct uart_txx9_port {TYPE_2__ port; } ;
struct uart_port {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {scalar_t__ index; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_TXX9 ; 
 int /*<<< orphan*/  TXX9_SIO_TX_FIFO ; 
 int /*<<< orphan*/  serial_txx9_initialize (struct uart_port*) ; 
 int serial_txx9_request_resource (struct uart_txx9_port*) ; 
 struct uart_txx9_port* to_uart_txx9_port (struct uart_port*) ; 

__attribute__((used)) static void serial_txx9_config_port(struct uart_port *port, int uflags)
{
	struct uart_txx9_port *up = to_uart_txx9_port(port);
	int ret;

	/*
	 * Find the region that we can probe for.  This in turn
	 * tells us whether we can probe for the type of port.
	 */
	ret = serial_txx9_request_resource(up);
	if (ret < 0)
		return;
	port->type = PORT_TXX9;
	up->port.fifosize = TXX9_SIO_TX_FIFO;

#ifdef CONFIG_SERIAL_TXX9_CONSOLE
	if (up->port.line == up->port.cons->index)
		return;
#endif
	serial_txx9_initialize(port);
}