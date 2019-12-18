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
struct uart_port {scalar_t__ membase; } ;

/* Variables and functions */
 scalar_t__ ULITE_STATUS ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int /*<<< orphan*/  ulite_transmit (struct uart_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ulite_start_tx(struct uart_port *port)
{
	ulite_transmit(port, readb(port->membase + ULITE_STATUS));
}