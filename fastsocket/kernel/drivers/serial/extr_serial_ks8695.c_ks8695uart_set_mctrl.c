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
typedef  int u_int ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int TIOCM_DTR ; 
 int TIOCM_RTS ; 
 unsigned int UART_GET_MCR (struct uart_port*) ; 
 int /*<<< orphan*/  UART_PUT_MCR (struct uart_port*,unsigned int) ; 
 unsigned int URMC_URDTR ; 
 unsigned int URMC_URRTS ; 

__attribute__((used)) static void ks8695uart_set_mctrl(struct uart_port *port, u_int mctrl)
{
	unsigned int mcr;

	mcr = UART_GET_MCR(port);
	if (mctrl & TIOCM_RTS)
		mcr |= URMC_URRTS;
	else
		mcr &= ~URMC_URRTS;

	if (mctrl & TIOCM_DTR)
		mcr |= URMC_URDTR;
	else
		mcr &= ~URMC_URDTR;

	UART_PUT_MCR(port, mcr);
}