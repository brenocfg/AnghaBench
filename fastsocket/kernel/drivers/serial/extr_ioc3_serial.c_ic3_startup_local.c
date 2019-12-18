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
struct uart_port {int /*<<< orphan*/  line; } ;
struct ioc3_port {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_RS232 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOT_PROGRESS () ; 
 int /*<<< orphan*/  PROTO_RS232 ; 
 int /*<<< orphan*/  PROTO_RS422 ; 
 struct ioc3_port* get_ioc3_port (struct uart_port*) ; 
 int /*<<< orphan*/  ioc3_set_proto (struct ioc3_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_open (struct ioc3_port*) ; 

__attribute__((used)) static inline int ic3_startup_local(struct uart_port *the_port)
{
	struct ioc3_port *port;

	if (!the_port) {
		NOT_PROGRESS();
		return -1;
	}

	port = get_ioc3_port(the_port);
	if (!port) {
		NOT_PROGRESS();
		return -1;
	}

	local_open(port);

	/* set the protocol */
	ioc3_set_proto(port, IS_RS232(the_port->line) ? PROTO_RS232 :
							PROTO_RS422);
	return 0;
}