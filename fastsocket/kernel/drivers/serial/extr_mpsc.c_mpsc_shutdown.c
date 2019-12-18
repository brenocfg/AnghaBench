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
struct uart_port {int /*<<< orphan*/  line; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;
struct mpsc_port_info {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mpsc_port_info*) ; 
 int /*<<< orphan*/  mpsc_sdma_stop (struct mpsc_port_info*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mpsc_shutdown(struct uart_port *port)
{
	struct mpsc_port_info *pi = (struct mpsc_port_info *)port;

	pr_debug("mpsc_shutdown[%d]: Shutting down MPSC\n", port->line);

	mpsc_sdma_stop(pi);
	free_irq(pi->port.irq, pi);
}