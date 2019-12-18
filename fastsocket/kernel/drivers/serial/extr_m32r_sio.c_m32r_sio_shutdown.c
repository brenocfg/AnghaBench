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
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;
struct uart_sio_port {int /*<<< orphan*/  timer; TYPE_1__ port; scalar_t__ ier; } ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIOTRCR ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_real_interrupt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_unlink_irq_chain (struct uart_sio_port*) ; 
 int /*<<< orphan*/  sio_init () ; 
 int /*<<< orphan*/  sio_out (struct uart_sio_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void m32r_sio_shutdown(struct uart_port *port)
{
	struct uart_sio_port *up = (struct uart_sio_port *)port;

	/*
	 * Disable interrupts from this port
	 */
	up->ier = 0;
	sio_out(up, SIOTRCR, 0);

	/*
	 * Disable break condition and FIFOs
	 */

	sio_init();

	if (!is_real_interrupt(up->port.irq))
		del_timer_sync(&up->timer);
	else
		serial_unlink_irq_chain(up);
}