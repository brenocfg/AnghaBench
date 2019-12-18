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
struct TYPE_2__ {scalar_t__ membase; int /*<<< orphan*/  irq; } ;
struct uart_amba_port {int /*<<< orphan*/  clk; TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ UART010_CR ; 
 scalar_t__ UART010_LCRH ; 
 int UART01x_LCRH_BRK ; 
 int UART01x_LCRH_FEN ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_amba_port*) ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void pl010_shutdown(struct uart_port *port)
{
	struct uart_amba_port *uap = (struct uart_amba_port *)port;

	/*
	 * Free the interrupt
	 */
	free_irq(uap->port.irq, uap);

	/*
	 * disable all interrupts, disable the port
	 */
	writel(0, uap->port.membase + UART010_CR);

	/* disable break condition and fifos */
	writel(readb(uap->port.membase + UART010_LCRH) &
		~(UART01x_LCRH_BRK | UART01x_LCRH_FEN),
	       uap->port.membase + UART010_LCRH);

	/*
	 * Shut down the clock producer
	 */
	clk_disable(uap->clk);
}