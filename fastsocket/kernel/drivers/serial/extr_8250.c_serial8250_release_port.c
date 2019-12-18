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
struct uart_port {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct uart_8250_port {TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ PORT_RSA ; 
 int /*<<< orphan*/  serial8250_release_rsa_resource (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial8250_release_std_resource (struct uart_8250_port*) ; 

__attribute__((used)) static void serial8250_release_port(struct uart_port *port)
{
	struct uart_8250_port *up = (struct uart_8250_port *)port;

	serial8250_release_std_resource(up);
	if (up->port.type == PORT_RSA)
		serial8250_release_rsa_resource(up);
}