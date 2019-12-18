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
struct uart_port {int dummy; } ;
struct uart_8250_port {int bugs; int /*<<< orphan*/  ier; } ;

/* Variables and functions */
 int UART_BUG_NOMSR ; 
 int /*<<< orphan*/  UART_IER ; 
 int /*<<< orphan*/  UART_IER_MSI ; 
 int /*<<< orphan*/  serial_out (struct uart_8250_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void serial8250_enable_ms(struct uart_port *port)
{
	struct uart_8250_port *up = (struct uart_8250_port *)port;

	/* no MSR capabilities */
	if (up->bugs & UART_BUG_NOMSR)
		return;

	up->ier |= UART_IER_MSI;
	serial_out(up, UART_IER, up->ier);
}