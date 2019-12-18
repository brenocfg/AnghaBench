#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t type; int /*<<< orphan*/ * dev; int /*<<< orphan*/  flags; } ;
struct uart_8250_port {TYPE_1__ port; int /*<<< orphan*/  capabilities; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 size_t PORT_UNKNOWN ; 
 int /*<<< orphan*/  UPF_BOOT_AUTOCONF ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_4__* serial8250_isa_devs ; 
 struct uart_8250_port* serial8250_ports ; 
 int /*<<< orphan*/  serial8250_reg ; 
 int /*<<< orphan*/  serial_mutex ; 
 int /*<<< orphan*/  uart_add_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_2__* uart_config ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 

void serial8250_unregister_port(int line)
{
	struct uart_8250_port *uart = &serial8250_ports[line];

	mutex_lock(&serial_mutex);
	uart_remove_one_port(&serial8250_reg, &uart->port);
	if (serial8250_isa_devs) {
		uart->port.flags &= ~UPF_BOOT_AUTOCONF;
		uart->port.type = PORT_UNKNOWN;
		uart->port.dev = &serial8250_isa_devs->dev;
		uart->capabilities = uart_config[uart->port.type].flags;
		uart_add_one_port(&serial8250_reg, &uart->port);
	} else {
		uart->port.dev = NULL;
	}
	mutex_unlock(&serial_mutex);
}