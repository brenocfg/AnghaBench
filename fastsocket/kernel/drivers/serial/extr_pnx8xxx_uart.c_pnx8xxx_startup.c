#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  irq; } ;
struct pnx8xxx_port {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNX8XXX_ICLR ; 
 int /*<<< orphan*/  PNX8XXX_IEN ; 
 int PNX8XXX_UART_INT_ALLRX ; 
 int PNX8XXX_UART_INT_ALLTX ; 
 int /*<<< orphan*/  pnx8xxx_enable_ms (TYPE_1__*) ; 
 int /*<<< orphan*/  pnx8xxx_int ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct pnx8xxx_port*) ; 
 int serial_in (struct pnx8xxx_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct pnx8xxx_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pnx8xxx_startup(struct uart_port *port)
{
	struct pnx8xxx_port *sport = (struct pnx8xxx_port *)port;
	int retval;

	/*
	 * Allocate the IRQ
	 */
	retval = request_irq(sport->port.irq, pnx8xxx_int, 0,
			     "pnx8xxx-uart", sport);
	if (retval)
		return retval;

	/*
	 * Finally, clear and enable interrupts
	 */

	serial_out(sport, PNX8XXX_ICLR, PNX8XXX_UART_INT_ALLRX |
			     PNX8XXX_UART_INT_ALLTX);

	serial_out(sport, PNX8XXX_IEN, serial_in(sport, PNX8XXX_IEN) |
			    PNX8XXX_UART_INT_ALLRX |
			    PNX8XXX_UART_INT_ALLTX);

	/*
	 * Enable modem status interrupts
	 */
	spin_lock_irq(&sport->port.lock);
	pnx8xxx_enable_ms(&sport->port);
	spin_unlock_irq(&sport->port.lock);

	return 0;
}