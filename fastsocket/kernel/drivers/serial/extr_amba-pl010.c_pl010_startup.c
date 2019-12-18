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
struct TYPE_2__ {scalar_t__ membase; int /*<<< orphan*/  irq; int /*<<< orphan*/  uartclk; } ;
struct uart_amba_port {int old_status; int /*<<< orphan*/  clk; TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ UART010_CR ; 
 int UART010_CR_RIE ; 
 int UART010_CR_RTIE ; 
 int UART01x_CR_UARTEN ; 
 scalar_t__ UART01x_FR ; 
 int UART01x_FR_MODEM_ANY ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pl010_int ; 
 int readb (scalar_t__) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct uart_amba_port*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int pl010_startup(struct uart_port *port)
{
	struct uart_amba_port *uap = (struct uart_amba_port *)port;
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
	retval = request_irq(uap->port.irq, pl010_int, 0, "uart-pl010", uap);
	if (retval)
		goto clk_dis;

	/*
	 * initialise the old status of the modem signals
	 */
	uap->old_status = readb(uap->port.membase + UART01x_FR) & UART01x_FR_MODEM_ANY;

	/*
	 * Finally, enable interrupts
	 */
	writel(UART01x_CR_UARTEN | UART010_CR_RIE | UART010_CR_RTIE,
	       uap->port.membase + UART010_CR);

	return 0;

 clk_dis:
	clk_disable(uap->clk);
 out:
	return retval;
}