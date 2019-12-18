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
struct sa1100_port {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_PUT_UTCR3 (struct sa1100_port*,int) ; 
 int /*<<< orphan*/  UART_PUT_UTSR0 (struct sa1100_port*,int) ; 
 int UTCR3_RIE ; 
 int UTCR3_RXE ; 
 int UTCR3_TXE ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct sa1100_port*) ; 
 int /*<<< orphan*/  sa1100_enable_ms (TYPE_1__*) ; 
 int /*<<< orphan*/  sa1100_int ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sa1100_startup(struct uart_port *port)
{
	struct sa1100_port *sport = (struct sa1100_port *)port;
	int retval;

	/*
	 * Allocate the IRQ
	 */
	retval = request_irq(sport->port.irq, sa1100_int, 0,
			     "sa11x0-uart", sport);
	if (retval)
		return retval;

	/*
	 * Finally, clear and enable interrupts
	 */
	UART_PUT_UTSR0(sport, -1);
	UART_PUT_UTCR3(sport, UTCR3_RXE | UTCR3_TXE | UTCR3_RIE);

	/*
	 * Enable modem status interrupts
	 */
	spin_lock_irq(&sport->port.lock);
	sa1100_enable_ms(&sport->port);
	spin_unlock_irq(&sport->port.lock);

	return 0;
}