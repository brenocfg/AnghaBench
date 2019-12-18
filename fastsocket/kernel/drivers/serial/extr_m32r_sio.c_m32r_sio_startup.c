#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long data; } ;
struct TYPE_3__ {unsigned int timeout; int /*<<< orphan*/  irq; } ;
struct uart_sio_port {int ier; TYPE_2__ timer; TYPE_1__ port; } ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIOTRCR ; 
 int UART_IER_MSI ; 
 int UART_IER_RDI ; 
 int UART_IER_RLSI ; 
 int /*<<< orphan*/  is_real_interrupt (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (TYPE_2__*,scalar_t__) ; 
 int serial_link_irq_chain (struct uart_sio_port*) ; 
 int /*<<< orphan*/  sio_init () ; 
 int /*<<< orphan*/  sio_out (struct uart_sio_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sio_reset () ; 

__attribute__((used)) static int m32r_sio_startup(struct uart_port *port)
{
	struct uart_sio_port *up = (struct uart_sio_port *)port;
	int retval;

	sio_init();

	/*
	 * If the "interrupt" for this port doesn't correspond with any
	 * hardware interrupt, we use a timer-based system.  The original
	 * driver used to do this with IRQ0.
	 */
	if (!is_real_interrupt(up->port.irq)) {
		unsigned int timeout = up->port.timeout;

		timeout = timeout > 6 ? (timeout / 2 - 2) : 1;

		up->timer.data = (unsigned long)up;
		mod_timer(&up->timer, jiffies + timeout);
	} else {
		retval = serial_link_irq_chain(up);
		if (retval)
			return retval;
	}

	/*
	 * Finally, enable interrupts.  Note: Modem status interrupts
	 * are set via set_termios(), which will be occurring imminently
	 * anyway, so we don't enable them here.
	 * - M32R_SIO: 0x0c
	 * - M32R_PLDSIO: 0x04
	 */
	up->ier = UART_IER_MSI | UART_IER_RLSI | UART_IER_RDI;
	sio_out(up, SIOTRCR, up->ier);

	/*
	 * And clear the interrupt registers again for luck.
	 */
	sio_reset();

	return 0;
}