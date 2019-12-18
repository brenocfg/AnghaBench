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
struct uart_port {scalar_t__ mapbase; } ;

/* Variables and functions */
 void* GPCR ; 
 void* GPIO_H3600_COM_RTS ; 
 void* GPSR ; 
 int TIOCM_RTS ; 
 scalar_t__ _Ser3UTCR0 ; 

__attribute__((used)) static void h3600_uart_set_mctrl(struct uart_port *port, u_int mctrl)
{
	if (port->mapbase == _Ser3UTCR0) {
		if (mctrl & TIOCM_RTS)
			GPCR = GPIO_H3600_COM_RTS;
		else
			GPSR = GPIO_H3600_COM_RTS;
	}
}