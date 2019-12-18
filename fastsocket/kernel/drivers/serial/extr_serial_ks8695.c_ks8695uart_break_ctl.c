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

/* Variables and functions */
 unsigned int UART_GET_LCR (struct uart_port*) ; 
 int /*<<< orphan*/  UART_PUT_LCR (struct uart_port*,unsigned int) ; 
 unsigned int URLC_URSBC ; 

__attribute__((used)) static void ks8695uart_break_ctl(struct uart_port *port, int break_state)
{
	unsigned int lcr;

	lcr = UART_GET_LCR(port);

	if (break_state == -1)
		lcr |= URLC_URSBC;
	else
		lcr &= ~URLC_URSBC;

	UART_PUT_LCR(port, lcr);
}