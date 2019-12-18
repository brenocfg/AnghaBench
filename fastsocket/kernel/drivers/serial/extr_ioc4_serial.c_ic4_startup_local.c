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
struct TYPE_4__ {TYPE_1__* tty; } ;
struct uart_state {TYPE_2__ port; } ;
struct uart_port {int /*<<< orphan*/  mapbase; struct uart_state* state; } ;
struct ktermios {int dummy; } ;
struct ioc4_port {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  termios; } ;

/* Variables and functions */
 struct ioc4_port* get_ioc4_port (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioc4_change_speed (struct uart_port*,int /*<<< orphan*/ ,struct ktermios*) ; 
 int /*<<< orphan*/  ioc4_set_proto (struct ioc4_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_open (struct ioc4_port*) ; 

__attribute__((used)) static inline int ic4_startup_local(struct uart_port *the_port)
{
	struct ioc4_port *port;
	struct uart_state *state;

	if (!the_port)
		return -1;

	port = get_ioc4_port(the_port, 0);
	if (!port)
		return -1;

	state = the_port->state;

	local_open(port);

	/* set the protocol - mapbase has the port type */
	ioc4_set_proto(port, the_port->mapbase);

	/* set the speed of the serial port */
	ioc4_change_speed(the_port, state->port.tty->termios,
			  (struct ktermios *)0);

	return 0;
}