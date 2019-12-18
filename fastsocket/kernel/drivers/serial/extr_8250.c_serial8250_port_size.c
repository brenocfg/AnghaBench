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
struct TYPE_2__ {scalar_t__ iotype; int regshift; } ;
struct uart_8250_port {TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ UPIO_AU ; 
 scalar_t__ is_omap_port (struct uart_8250_port*) ; 

__attribute__((used)) static unsigned int serial8250_port_size(struct uart_8250_port *pt)
{
	if (pt->port.iotype == UPIO_AU)
		return 0x100000;
#ifdef CONFIG_ARCH_OMAP
	if (is_omap_port(pt))
		return 0x16 << pt->port.regshift;
#endif
	return 8 << pt->port.regshift;
}