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
struct uart_port {int /*<<< orphan*/  lock; scalar_t__ membase; } ;

/* Variables and functions */
 unsigned int LINE_CR_BRK ; 
 scalar_t__ UART_LINE_CR ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void netx_break_ctl(struct uart_port *port, int break_state)
{
	unsigned int line_cr;
	spin_lock_irq(&port->lock);

	line_cr = readl(port->membase + UART_LINE_CR);
	if (break_state != 0)
		line_cr |= LINE_CR_BRK;
	else
		line_cr &= ~LINE_CR_BRK;
	writel(line_cr, port->membase + UART_LINE_CR);

	spin_unlock_irq(&port->lock);
}