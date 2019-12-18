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
struct uart_port {int flags; int /*<<< orphan*/  mapbase; int /*<<< orphan*/ * membase; } ;
struct mpc52xx_psc {int dummy; } ;

/* Variables and functions */
 int UPF_IOREMAP ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mpc52xx_uart_release_port(struct uart_port *port)
{
	/* remapped by us ? */
	if (port->flags & UPF_IOREMAP) {
		iounmap(port->membase);
		port->membase = NULL;
	}

	release_mem_region(port->mapbase, sizeof(struct mpc52xx_psc));
}