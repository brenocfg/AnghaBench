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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int UART_EXTINP_CTS_MASK ; 
 unsigned int UART_EXTINP_DCD_MASK ; 
 unsigned int UART_EXTINP_IRSTAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_EXTINP_IR_CTS ; 
 int /*<<< orphan*/  UART_EXTINP_IR_DCD ; 
 int /*<<< orphan*/  UART_EXTINP_REG ; 
 int /*<<< orphan*/  UART_IR_EXTIP ; 
 unsigned int UART_IR_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_IR_REG ; 
 unsigned int UART_RX_INT_STAT ; 
 unsigned int UART_TX_INT_STAT ; 
 int /*<<< orphan*/  bcm_uart_do_rx (struct uart_port*) ; 
 int /*<<< orphan*/  bcm_uart_do_tx (struct uart_port*) ; 
 unsigned int bcm_uart_readl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_handle_cts_change (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  uart_handle_dcd_change (struct uart_port*,unsigned int) ; 

__attribute__((used)) static irqreturn_t bcm_uart_interrupt(int irq, void *dev_id)
{
	struct uart_port *port;
	unsigned int irqstat;

	port = dev_id;
	spin_lock(&port->lock);

	irqstat = bcm_uart_readl(port, UART_IR_REG);
	if (irqstat & UART_RX_INT_STAT)
		bcm_uart_do_rx(port);

	if (irqstat & UART_TX_INT_STAT)
		bcm_uart_do_tx(port);

	if (irqstat & UART_IR_MASK(UART_IR_EXTIP)) {
		unsigned int estat;

		estat = bcm_uart_readl(port, UART_EXTINP_REG);
		if (estat & UART_EXTINP_IRSTAT(UART_EXTINP_IR_CTS))
			uart_handle_cts_change(port,
					       estat & UART_EXTINP_CTS_MASK);
		if (estat & UART_EXTINP_IRSTAT(UART_EXTINP_IR_DCD))
			uart_handle_dcd_change(port,
					       estat & UART_EXTINP_DCD_MASK);
	}

	spin_unlock(&port->lock);
	return IRQ_HANDLED;
}