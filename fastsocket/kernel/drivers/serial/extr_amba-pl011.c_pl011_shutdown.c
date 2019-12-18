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
struct TYPE_2__ {scalar_t__ membase; int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; } ;
struct uart_amba_port {unsigned long im; int /*<<< orphan*/  clk; TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ UART011_CR ; 
 unsigned long UART011_CR_TXE ; 
 scalar_t__ UART011_ICR ; 
 scalar_t__ UART011_IMSC ; 
 scalar_t__ UART011_LCRH ; 
 unsigned long UART01x_CR_UARTEN ; 
 unsigned long UART01x_LCRH_BRK ; 
 unsigned long UART01x_LCRH_FEN ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_amba_port*) ; 
 unsigned long readw (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writew (unsigned long,scalar_t__) ; 

__attribute__((used)) static void pl011_shutdown(struct uart_port *port)
{
	struct uart_amba_port *uap = (struct uart_amba_port *)port;
	unsigned long val;

	/*
	 * disable all interrupts
	 */
	spin_lock_irq(&uap->port.lock);
	uap->im = 0;
	writew(uap->im, uap->port.membase + UART011_IMSC);
	writew(0xffff, uap->port.membase + UART011_ICR);
	spin_unlock_irq(&uap->port.lock);

	/*
	 * Free the interrupt
	 */
	free_irq(uap->port.irq, uap);

	/*
	 * disable the port
	 */
	writew(UART01x_CR_UARTEN | UART011_CR_TXE, uap->port.membase + UART011_CR);

	/*
	 * disable break condition and fifos
	 */
	val = readw(uap->port.membase + UART011_LCRH);
	val &= ~(UART01x_LCRH_BRK | UART01x_LCRH_FEN);
	writew(val, uap->port.membase + UART011_LCRH);

	/*
	 * Shut down the clock producer
	 */
	clk_disable(uap->clk);
}