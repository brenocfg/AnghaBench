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
 int GPIO_H3600_COM_CTS ; 
 int GPIO_H3600_COM_DCD ; 
 int GPLR ; 
 int TIOCM_CD ; 
 int TIOCM_CTS ; 
 int TIOCM_DSR ; 
 scalar_t__ _Ser3UTCR0 ; 

__attribute__((used)) static u_int h3600_uart_get_mctrl(struct uart_port *port)
{
	u_int ret = TIOCM_CD | TIOCM_CTS | TIOCM_DSR;

	if (port->mapbase == _Ser3UTCR0) {
		int gplr = GPLR;
		/* DCD and CTS bits are inverted in GPLR by RS232 transceiver */
		if (gplr & GPIO_H3600_COM_DCD)
			ret &= ~TIOCM_CD;
		if (gplr & GPIO_H3600_COM_CTS)
			ret &= ~TIOCM_CTS;
	}

	return ret;
}