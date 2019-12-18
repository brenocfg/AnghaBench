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
struct dz_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_DZ ; 
 int UART_CONFIG_TYPE ; 
 scalar_t__ dz_request_port (struct uart_port*) ; 
 int /*<<< orphan*/  dz_reset (struct dz_port*) ; 
 struct dz_port* to_dport (struct uart_port*) ; 

__attribute__((used)) static void dz_config_port(struct uart_port *uport, int flags)
{
	struct dz_port *dport = to_dport(uport);

	if (flags & UART_CONFIG_TYPE) {
		if (dz_request_port(uport))
			return;

		uport->type = PORT_DZ;

		dz_reset(dport);
	}
}