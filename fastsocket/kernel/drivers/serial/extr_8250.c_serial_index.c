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
struct uart_port {int line; } ;
struct TYPE_2__ {int minor; } ;

/* Variables and functions */
 TYPE_1__ serial8250_reg ; 

__attribute__((used)) static int serial_index(struct uart_port *port)
{
	return (serial8250_reg.minor - 64) + port->line;
}