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
struct pnx8xxx_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNX8XXX_MCR ; 
 unsigned int PNX8XXX_UART_MCR_CTS ; 
 unsigned int PNX8XXX_UART_MCR_DCD ; 
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned int serial_in (struct pnx8xxx_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int pnx8xxx_get_mctrl(struct uart_port *port)
{
	struct pnx8xxx_port *sport = (struct pnx8xxx_port *)port;
	unsigned int mctrl = TIOCM_DSR;
	unsigned int msr;

	/* REVISIT */

	msr = serial_in(sport, PNX8XXX_MCR);

	mctrl |= msr & PNX8XXX_UART_MCR_CTS ? TIOCM_CTS : 0;
	mctrl |= msr & PNX8XXX_UART_MCR_DCD ? TIOCM_CAR : 0;

	return mctrl;
}