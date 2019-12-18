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
struct zs_port {int dummy; } ;
struct uart_port {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_ZS ; 
 int UART_CONFIG_TYPE ; 
 struct zs_port* to_zport (struct uart_port*) ; 
 scalar_t__ zs_request_port (struct uart_port*) ; 
 int /*<<< orphan*/  zs_reset (struct zs_port*) ; 

__attribute__((used)) static void zs_config_port(struct uart_port *uport, int flags)
{
	struct zs_port *zport = to_zport(uport);

	if (flags & UART_CONFIG_TYPE) {
		if (zs_request_port(uport))
			return;

		uport->type = PORT_ZS;

		zs_reset(zport);
	}
}