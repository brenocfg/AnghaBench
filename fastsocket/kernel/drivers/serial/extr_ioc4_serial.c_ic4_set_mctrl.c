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
struct ioc4_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOC4_SHADOW_DTR ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_LOOP ; 
 unsigned int TIOCM_OUT1 ; 
 unsigned int TIOCM_OUT2 ; 
 unsigned int TIOCM_RTS ; 
 unsigned char UART_MCR_DTR ; 
 unsigned char UART_MCR_LOOP ; 
 unsigned char UART_MCR_OUT1 ; 
 unsigned char UART_MCR_OUT2 ; 
 unsigned char UART_MCR_RTS ; 
 struct ioc4_port* get_ioc4_port (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_is_active (struct ioc4_port*,struct uart_port*) ; 
 int /*<<< orphan*/  set_mcr (struct uart_port*,unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ic4_set_mctrl(struct uart_port *the_port, unsigned int mctrl)
{
	unsigned char mcr = 0;
	struct ioc4_port *port;

	port = get_ioc4_port(the_port, 0);
	if (!port_is_active(port, the_port))
		return;

	if (mctrl & TIOCM_RTS)
		mcr |= UART_MCR_RTS;
	if (mctrl & TIOCM_DTR)
		mcr |= UART_MCR_DTR;
	if (mctrl & TIOCM_OUT1)
		mcr |= UART_MCR_OUT1;
	if (mctrl & TIOCM_OUT2)
		mcr |= UART_MCR_OUT2;
	if (mctrl & TIOCM_LOOP)
		mcr |= UART_MCR_LOOP;

	set_mcr(the_port, mcr, IOC4_SHADOW_DTR);
}