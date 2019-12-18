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
struct TYPE_2__ {int regshift; int iotype; unsigned long mapbase; int /*<<< orphan*/  iobase; } ;
struct uart_sio_port {TYPE_1__ port; } ;
struct resource {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
#define  UPIO_MEM 129 
#define  UPIO_PORT 128 
 struct resource* request_mem_region (unsigned long,unsigned int,char*) ; 
 struct resource* request_region (int /*<<< orphan*/ ,unsigned int,char*) ; 

__attribute__((used)) static int
m32r_sio_request_std_resource(struct uart_sio_port *up, struct resource **res)
{
	unsigned int size = 8 << up->port.regshift;
#ifndef CONFIG_SERIAL_M32R_PLDSIO
	unsigned long start;
#endif
	int ret = 0;

	switch (up->port.iotype) {
	case UPIO_MEM:
		if (up->port.mapbase) {
#ifdef CONFIG_SERIAL_M32R_PLDSIO
			*res = request_mem_region(up->port.mapbase, size, "serial");
#else
			start = up->port.mapbase;
			*res = request_mem_region(start, size, "serial");
#endif
			if (!*res)
				ret = -EBUSY;
		}
		break;

	case UPIO_PORT:
		*res = request_region(up->port.iobase, size, "serial");
		if (!*res)
			ret = -EBUSY;
		break;
	}
	return ret;
}