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
 int /*<<< orphan*/  PNX8XXX_FIFO ; 
 int PNX8XXX_UART_FIFO_TXFIFO_STA ; 
 unsigned int TIOCSER_TEMT ; 
 int serial_in (struct pnx8xxx_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int pnx8xxx_tx_empty(struct uart_port *port)
{
	struct pnx8xxx_port *sport = (struct pnx8xxx_port *)port;

	return serial_in(sport, PNX8XXX_FIFO) & PNX8XXX_UART_FIFO_TXFIFO_STA ? 0 : TIOCSER_TEMT;
}