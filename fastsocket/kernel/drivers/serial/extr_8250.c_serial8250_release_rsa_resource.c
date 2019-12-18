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
struct TYPE_2__ {unsigned long regshift; int iotype; int /*<<< orphan*/  iobase; } ;
struct uart_8250_port {TYPE_1__ port; } ;

/* Variables and functions */
 unsigned long UART_RSA_BASE ; 
#define  UPIO_HUB6 129 
#define  UPIO_PORT 128 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void serial8250_release_rsa_resource(struct uart_8250_port *up)
{
	unsigned long offset = UART_RSA_BASE << up->port.regshift;
	unsigned int size = 8 << up->port.regshift;

	switch (up->port.iotype) {
	case UPIO_HUB6:
	case UPIO_PORT:
		release_region(up->port.iobase + offset, size);
		break;
	}
}