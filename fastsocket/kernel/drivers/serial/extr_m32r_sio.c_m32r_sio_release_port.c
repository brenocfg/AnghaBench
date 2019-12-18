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
struct TYPE_2__ {unsigned long regshift; int iotype; unsigned long mapbase; unsigned long iobase; int /*<<< orphan*/ * membase; } ;
struct uart_sio_port {TYPE_1__ port; } ;
struct uart_port {int dummy; } ;

/* Variables and functions */
#define  UPIO_MEM 129 
#define  UPIO_PORT 128 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (unsigned long,int) ; 
 int /*<<< orphan*/  release_region (unsigned long,int) ; 

__attribute__((used)) static void m32r_sio_release_port(struct uart_port *port)
{
	struct uart_sio_port *up = (struct uart_sio_port *)port;
	unsigned long start, offset = 0, size = 0;

	size <<= up->port.regshift;

	switch (up->port.iotype) {
	case UPIO_MEM:
		if (up->port.mapbase) {
			/*
			 * Unmap the area.
			 */
			iounmap(up->port.membase);
			up->port.membase = NULL;

			start = up->port.mapbase;

			if (size)
				release_mem_region(start + offset, size);
			release_mem_region(start, 8 << up->port.regshift);
		}
		break;

	case UPIO_PORT:
		start = up->port.iobase;

		if (size)
			release_region(start + offset, size);
		release_region(start + offset, 8 << up->port.regshift);
		break;

	default:
		break;
	}
}