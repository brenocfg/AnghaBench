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
struct uart_port {int fifosize; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_CTL_REG ; 
 unsigned int UART_CTL_RXTMOUTCNT_MASK ; 
 int UART_CTL_RXTMOUTCNT_SHIFT ; 
 unsigned int UART_EXTINP_CTS_NOSENSE_MASK ; 
 unsigned int UART_EXTINP_DCD_NOSENSE_MASK ; 
 unsigned int UART_EXTINP_INT_MASK ; 
 int /*<<< orphan*/  UART_EXTINP_REG ; 
 int /*<<< orphan*/  UART_IR_REG ; 
 int /*<<< orphan*/  UART_MCTL_REG ; 
 unsigned int UART_MCTL_RXFIFOTHRESH_MASK ; 
 int UART_MCTL_RXFIFOTHRESH_SHIFT ; 
 unsigned int UART_MCTL_TXFIFOTHRESH_MASK ; 
 int UART_MCTL_TXFIFOTHRESH_SHIFT ; 
 unsigned int UART_RX_INT_MASK ; 
 int /*<<< orphan*/  bcm_uart_disable (struct uart_port*) ; 
 int /*<<< orphan*/  bcm_uart_enable (struct uart_port*) ; 
 int /*<<< orphan*/  bcm_uart_flush (struct uart_port*) ; 
 int /*<<< orphan*/  bcm_uart_interrupt ; 
 unsigned int bcm_uart_readl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_uart_type (struct uart_port*) ; 
 int /*<<< orphan*/  bcm_uart_writel (struct uart_port*,unsigned int,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uart_port*) ; 

__attribute__((used)) static int bcm_uart_startup(struct uart_port *port)
{
	unsigned int val;
	int ret;

	/* mask all irq and flush port */
	bcm_uart_disable(port);
	bcm_uart_writel(port, 0, UART_IR_REG);
	bcm_uart_flush(port);

	/* clear any pending external input interrupt */
	(void)bcm_uart_readl(port, UART_EXTINP_REG);

	/* set rx/tx fifo thresh to fifo half size */
	val = bcm_uart_readl(port, UART_MCTL_REG);
	val &= ~(UART_MCTL_RXFIFOTHRESH_MASK | UART_MCTL_TXFIFOTHRESH_MASK);
	val |= (port->fifosize / 2) << UART_MCTL_RXFIFOTHRESH_SHIFT;
	val |= (port->fifosize / 2) << UART_MCTL_TXFIFOTHRESH_SHIFT;
	bcm_uart_writel(port, val, UART_MCTL_REG);

	/* set rx fifo timeout to 1 char time */
	val = bcm_uart_readl(port, UART_CTL_REG);
	val &= ~UART_CTL_RXTMOUTCNT_MASK;
	val |= 1 << UART_CTL_RXTMOUTCNT_SHIFT;
	bcm_uart_writel(port, val, UART_CTL_REG);

	/* report any edge on dcd and cts */
	val = UART_EXTINP_INT_MASK;
	val |= UART_EXTINP_DCD_NOSENSE_MASK;
	val |= UART_EXTINP_CTS_NOSENSE_MASK;
	bcm_uart_writel(port, val, UART_EXTINP_REG);

	/* register irq and enable rx interrupts */
	ret = request_irq(port->irq, bcm_uart_interrupt, 0,
			  bcm_uart_type(port), port);
	if (ret)
		return ret;
	bcm_uart_writel(port, UART_RX_INT_MASK, UART_IR_REG);
	bcm_uart_enable(port);
	return 0;
}