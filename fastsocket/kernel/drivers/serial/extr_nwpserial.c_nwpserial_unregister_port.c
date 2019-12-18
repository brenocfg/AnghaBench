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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct nwpserial_port {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_UNKNOWN ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nwpserial_mutex ; 
 struct nwpserial_port* nwpserial_ports ; 
 int /*<<< orphan*/  nwpserial_reg ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 

void nwpserial_unregister_port(int line)
{
	struct nwpserial_port *up = &nwpserial_ports[line];
	mutex_lock(&nwpserial_mutex);
	uart_remove_one_port(&nwpserial_reg, &up->port);

	up->port.type = PORT_UNKNOWN;

	mutex_unlock(&nwpserial_mutex);
}