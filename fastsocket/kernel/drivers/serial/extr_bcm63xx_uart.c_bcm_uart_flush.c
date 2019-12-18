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
 int /*<<< orphan*/  UART_CTL_REG ; 
 unsigned int UART_CTL_RSTRXFIFO_MASK ; 
 unsigned int UART_CTL_RSTTXFIFO_MASK ; 
 int /*<<< orphan*/  UART_FIFO_REG ; 
 unsigned int bcm_uart_readl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_uart_writel (struct uart_port*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_uart_flush(struct uart_port *port)
{
	unsigned int val;

	/* empty rx and tx fifo */
	val = bcm_uart_readl(port, UART_CTL_REG);
	val |= UART_CTL_RSTRXFIFO_MASK | UART_CTL_RSTTXFIFO_MASK;
	bcm_uart_writel(port, val, UART_CTL_REG);

	/* read any pending char to make sure all irq status are
	 * cleared */
	(void)bcm_uart_readl(port, UART_FIFO_REG);
}