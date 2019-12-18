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
struct uart_port {int /*<<< orphan*/  mapbase; int /*<<< orphan*/  dev; int /*<<< orphan*/  membase; } ;

/* Variables and functions */
 int EBUSY ; 
 unsigned int RSET_UART_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,unsigned int,char*) ; 

__attribute__((used)) static int bcm_uart_request_port(struct uart_port *port)
{
	unsigned int size;

	size = RSET_UART_SIZE;
	if (!request_mem_region(port->mapbase, size, "bcm63xx")) {
		dev_err(port->dev, "Memory region busy\n");
		return -EBUSY;
	}

	port->membase = ioremap(port->mapbase, size);
	if (!port->membase) {
		dev_err(port->dev, "Unable to map registers\n");
		release_mem_region(port->mapbase, size);
		return -EBUSY;
	}
	return 0;
}