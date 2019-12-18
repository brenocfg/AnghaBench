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
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;
struct sa1100_port {TYPE_1__ port; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_PUT_UTCR3 (struct sa1100_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct sa1100_port*) ; 

__attribute__((used)) static void sa1100_shutdown(struct uart_port *port)
{
	struct sa1100_port *sport = (struct sa1100_port *)port;

	/*
	 * Stop our timer.
	 */
	del_timer_sync(&sport->timer);

	/*
	 * Free the interrupt
	 */
	free_irq(sport->port.irq, sport);

	/*
	 * Disable all interrupts, port and break condition.
	 */
	UART_PUT_UTCR3(sport, 0);
}