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
struct uart_port {int /*<<< orphan*/  line; } ;

/* Variables and functions */
 scalar_t__ IS_RS232 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *ic3_type(struct uart_port *the_port)
{
	if (IS_RS232(the_port->line))
		return "SGI IOC3 Serial [rs232]";
	else
		return "SGI IOC3 Serial [rs422]";
}