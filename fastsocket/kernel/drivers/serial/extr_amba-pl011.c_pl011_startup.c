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
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ membase; int /*<<< orphan*/  irq; int /*<<< orphan*/  uartclk; } ;
struct uart_amba_port {unsigned int ifls; int old_status; int im; int /*<<< orphan*/  clk; TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ UART011_CR ; 
 unsigned int UART011_CR_LBE ; 
 unsigned int UART011_CR_RXE ; 
 unsigned int UART011_CR_TXE ; 
 scalar_t__ UART011_FBRD ; 
 scalar_t__ UART011_IBRD ; 
 scalar_t__ UART011_IFLS ; 
 scalar_t__ UART011_IMSC ; 
 scalar_t__ UART011_LCRH ; 
 int UART011_RTIM ; 
 int UART011_RXIM ; 
 unsigned int UART01x_CR_UARTEN ; 
 scalar_t__ UART01x_DR ; 
 scalar_t__ UART01x_FR ; 
 int UART01x_FR_BUSY ; 
 int UART01x_FR_MODEM_ANY ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pl011_int ; 
 int readw (scalar_t__) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct uart_amba_port*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writew (unsigned int,scalar_t__) ; 

__attribute__((used)) static int pl011_startup(struct uart_port *port)
{
	struct uart_amba_port *uap = (struct uart_amba_port *)port;
	unsigned int cr;
	int retval;

	/*
	 * Try to enable the clock producer.
	 */
	retval = clk_enable(uap->clk);
	if (retval)
		goto out;

	uap->port.uartclk = clk_get_rate(uap->clk);

	/*
	 * Allocate the IRQ
	 */
	retval = request_irq(uap->port.irq, pl011_int, 0, "uart-pl011", uap);
	if (retval)
		goto clk_dis;

	writew(uap->ifls, uap->port.membase + UART011_IFLS);

	/*
	 * Provoke TX FIFO interrupt into asserting.
	 */
	cr = UART01x_CR_UARTEN | UART011_CR_TXE | UART011_CR_LBE;
	writew(cr, uap->port.membase + UART011_CR);
	writew(0, uap->port.membase + UART011_FBRD);
	writew(1, uap->port.membase + UART011_IBRD);
	writew(0, uap->port.membase + UART011_LCRH);
	writew(0, uap->port.membase + UART01x_DR);
	while (readw(uap->port.membase + UART01x_FR) & UART01x_FR_BUSY)
		barrier();

	cr = UART01x_CR_UARTEN | UART011_CR_RXE | UART011_CR_TXE;
	writew(cr, uap->port.membase + UART011_CR);

	/*
	 * initialise the old status of the modem signals
	 */
	uap->old_status = readw(uap->port.membase + UART01x_FR) & UART01x_FR_MODEM_ANY;

	/*
	 * Finally, enable interrupts
	 */
	spin_lock_irq(&uap->port.lock);
	uap->im = UART011_RXIM | UART011_RTIM;
	writew(uap->im, uap->port.membase + UART011_IMSC);
	spin_unlock_irq(&uap->port.lock);

	return 0;

 clk_dis:
	clk_disable(uap->clk);
 out:
	return retval;
}