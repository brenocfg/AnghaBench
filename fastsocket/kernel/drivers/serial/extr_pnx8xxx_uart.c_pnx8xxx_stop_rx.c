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
typedef  int u32 ;
struct uart_port {int dummy; } ;
struct pnx8xxx_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNX8XXX_ICLR ; 
 int /*<<< orphan*/  PNX8XXX_IEN ; 
 int PNX8XXX_UART_INT_ALLRX ; 
 int serial_in (struct pnx8xxx_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct pnx8xxx_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pnx8xxx_stop_rx(struct uart_port *port)
{
	struct pnx8xxx_port *sport = (struct pnx8xxx_port *)port;
	u32 ien;

	/* Disable RX intr */
	ien = serial_in(sport, PNX8XXX_IEN);
	serial_out(sport, PNX8XXX_IEN, ien & ~PNX8XXX_UART_INT_ALLRX);

	/* Clear all pending RX intr */
	serial_out(sport, PNX8XXX_ICLR, PNX8XXX_UART_INT_ALLRX);
}