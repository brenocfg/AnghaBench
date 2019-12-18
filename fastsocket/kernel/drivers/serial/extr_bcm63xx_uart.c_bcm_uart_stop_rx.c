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
 int /*<<< orphan*/  UART_IR_REG ; 
 unsigned int UART_RX_INT_MASK ; 
 unsigned int bcm_uart_readl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_uart_writel (struct uart_port*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_uart_stop_rx(struct uart_port *port)
{
	unsigned int val;

	val = bcm_uart_readl(port, UART_IR_REG);
	val &= ~UART_RX_INT_MASK;
	bcm_uart_writel(port, val, UART_IR_REG);
}