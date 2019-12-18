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
struct TYPE_2__ {int iotype; int flags; int /*<<< orphan*/  iobase; int /*<<< orphan*/  mapbase; int /*<<< orphan*/ * membase; } ;
struct uart_8250_port {TYPE_1__ port; } ;

/* Variables and functions */
 int UPF_IOREMAP ; 
#define  UPIO_AU 134 
#define  UPIO_DWAPB 133 
#define  UPIO_HUB6 132 
#define  UPIO_MEM 131 
#define  UPIO_MEM32 130 
#define  UPIO_PORT 129 
#define  UPIO_TSI 128 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int serial8250_port_size (struct uart_8250_port*) ; 

__attribute__((used)) static void serial8250_release_std_resource(struct uart_8250_port *up)
{
	unsigned int size = serial8250_port_size(up);

	switch (up->port.iotype) {
	case UPIO_AU:
	case UPIO_TSI:
	case UPIO_MEM32:
	case UPIO_MEM:
	case UPIO_DWAPB:
		if (!up->port.mapbase)
			break;

		if (up->port.flags & UPF_IOREMAP) {
			iounmap(up->port.membase);
			up->port.membase = NULL;
		}

		release_mem_region(up->port.mapbase, size);
		break;

	case UPIO_HUB6:
	case UPIO_PORT:
		release_region(up->port.iobase, size);
		break;
	}
}