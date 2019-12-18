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
struct uart_port {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_CTL_REG ; 
 unsigned int UART_CTL_XMITBRK_MASK ; 
 unsigned int bcm_uart_readl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_uart_writel (struct uart_port*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void bcm_uart_break_ctl(struct uart_port *port, int ctl)
{
	unsigned long flags;
	unsigned int val;

	spin_lock_irqsave(&port->lock, flags);

	val = bcm_uart_readl(port, UART_CTL_REG);
	if (ctl)
		val |= UART_CTL_XMITBRK_MASK;
	else
		val &= ~UART_CTL_XMITBRK_MASK;
	bcm_uart_writel(port, val, UART_CTL_REG);

	spin_unlock_irqrestore(&port->lock, flags);
}