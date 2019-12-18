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
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_IRQ (struct uart_port*) ; 
 int /*<<< orphan*/  SYSCON (struct uart_port*) ; 
 unsigned int SYSCON_UARTEN ; 
 int /*<<< orphan*/  TX_IRQ (struct uart_port*) ; 
 int /*<<< orphan*/  UBRLCR (struct uart_port*) ; 
 unsigned int UBRLCR_BREAK ; 
 unsigned int UBRLCR_FIFOEN ; 
 unsigned int clps_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clps_writel (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 

__attribute__((used)) static void clps711xuart_shutdown(struct uart_port *port)
{
	unsigned int ubrlcr, syscon;

	/*
	 * Free the interrupt
	 */
	free_irq(TX_IRQ(port), port);	/* TX interrupt */
	free_irq(RX_IRQ(port), port);	/* RX interrupt */

	/*
	 * disable the port
	 */
	syscon = clps_readl(SYSCON(port));
	syscon &= ~SYSCON_UARTEN;
	clps_writel(syscon, SYSCON(port));

	/*
	 * disable break condition and fifos
	 */
	ubrlcr = clps_readl(UBRLCR(port));
	ubrlcr &= ~(UBRLCR_FIFOEN | UBRLCR_BREAK);
	clps_writel(ubrlcr, UBRLCR(port));
}