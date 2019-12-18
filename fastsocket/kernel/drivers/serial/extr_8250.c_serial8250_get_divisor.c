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
struct uart_port {int flags; int uartclk; scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ PORT_16C950 ; 
 int UPF_MAGIC_MULTIPLIER ; 
 unsigned int uart_get_divisor (struct uart_port*,unsigned int) ; 

__attribute__((used)) static unsigned int serial8250_get_divisor(struct uart_port *port, unsigned int baud)
{
	unsigned int quot;

	/*
	 * Handle magic divisors for baud rates above baud_base on
	 * SMSC SuperIO chips.
	 */
	if ((port->flags & UPF_MAGIC_MULTIPLIER) &&
	    baud == (port->uartclk/4))
		quot = 0x8001;
	else if ((port->flags & UPF_MAGIC_MULTIPLIER) &&
		 baud == (port->uartclk/8))
		quot = 0x8002;
	/*
	 * For 16C950s UART_TCR is used in combination with divisor==1
	 * to achieve baud rates up to baud_base*4.
	 */
	else if ((port->type == PORT_16C950) &&
		 baud > (port->uartclk/16))
		quot = 1;

	else
		quot = uart_get_divisor(port, baud);

	return quot;
}