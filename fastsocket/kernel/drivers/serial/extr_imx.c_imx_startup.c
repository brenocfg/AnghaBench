#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int dummy; } ;
struct imxuart_platform_data {int /*<<< orphan*/  (* irda_enable ) (int) ;int /*<<< orphan*/  transceiver_delay; scalar_t__ irda_inv_tx; scalar_t__ irda_inv_rx; } ;
struct TYPE_4__ {scalar_t__ irq; TYPE_1__* dev; int /*<<< orphan*/  lock; scalar_t__ membase; } ;
struct imx_port {scalar_t__ txirq; scalar_t__ rxirq; scalar_t__ rtsirq; int /*<<< orphan*/  trcv_delay; scalar_t__ irda_inv_tx; scalar_t__ irda_inv_rx; TYPE_2__ port; } ;
struct TYPE_3__ {struct imxuart_platform_data* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ MAX_INTERNAL_IRQ ; 
 unsigned long MX2_UCR3_RXDMUXSEL ; 
 scalar_t__ UCR1 ; 
 unsigned long UCR1_IREN ; 
 unsigned long UCR1_RRDYEN ; 
 unsigned long UCR1_RTSDEN ; 
 unsigned long UCR1_UARTEN ; 
 scalar_t__ UCR2 ; 
 unsigned long UCR2_RXEN ; 
 unsigned long UCR2_SRST ; 
 unsigned long UCR2_TXEN ; 
 scalar_t__ UCR3 ; 
 unsigned long UCR3_INVT ; 
 scalar_t__ UCR4 ; 
 unsigned long UCR4_DREN ; 
 unsigned long UCR4_INVR ; 
 unsigned long UCR4_IRSC ; 
 scalar_t__ URXD0 ; 
 unsigned long URXD_CHARRDY ; 
 scalar_t__ USE_IRDA (struct imx_port*) ; 
 scalar_t__ USR1 ; 
 unsigned long USR1_RTSD ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  cpu_is_mx1 () ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct imx_port*) ; 
 int /*<<< orphan*/  imx_enable_ms (TYPE_2__*) ; 
 int /*<<< orphan*/  imx_int ; 
 int /*<<< orphan*/  imx_rtsint ; 
 int /*<<< orphan*/  imx_rxint ; 
 int /*<<< orphan*/  imx_setup_ufcr (struct imx_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_txint ; 
 unsigned long readl (scalar_t__) ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct imx_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int imx_startup(struct uart_port *port)
{
	struct imx_port *sport = (struct imx_port *)port;
	int retval;
	unsigned long flags, temp;

	imx_setup_ufcr(sport, 0);

	/* disable the DREN bit (Data Ready interrupt enable) before
	 * requesting IRQs
	 */
	temp = readl(sport->port.membase + UCR4);

	if (USE_IRDA(sport))
		temp |= UCR4_IRSC;

	writel(temp & ~UCR4_DREN, sport->port.membase + UCR4);

	if (USE_IRDA(sport)) {
		/* reset fifo's and state machines */
		int i = 100;
		temp = readl(sport->port.membase + UCR2);
		temp &= ~UCR2_SRST;
		writel(temp, sport->port.membase + UCR2);
		while (!(readl(sport->port.membase + UCR2) & UCR2_SRST) &&
		    (--i > 0)) {
			udelay(1);
		}
	}

	/*
	 * Allocate the IRQ(s) i.MX1 has three interrupts whereas later
	 * chips only have one interrupt.
	 */
	if (sport->txirq > 0) {
		retval = request_irq(sport->rxirq, imx_rxint, 0,
				DRIVER_NAME, sport);
		if (retval)
			goto error_out1;

		retval = request_irq(sport->txirq, imx_txint, 0,
				DRIVER_NAME, sport);
		if (retval)
			goto error_out2;

		/* do not use RTS IRQ on IrDA */
		if (!USE_IRDA(sport)) {
			retval = request_irq(sport->rtsirq, imx_rtsint,
				     (sport->rtsirq < MAX_INTERNAL_IRQ) ? 0 :
				       IRQF_TRIGGER_FALLING |
				       IRQF_TRIGGER_RISING,
					DRIVER_NAME, sport);
			if (retval)
				goto error_out3;
		}
	} else {
		retval = request_irq(sport->port.irq, imx_int, 0,
				DRIVER_NAME, sport);
		if (retval) {
			free_irq(sport->port.irq, sport);
			goto error_out1;
		}
	}

	/*
	 * Finally, clear and enable interrupts
	 */
	writel(USR1_RTSD, sport->port.membase + USR1);

	temp = readl(sport->port.membase + UCR1);
	temp |= UCR1_RRDYEN | UCR1_RTSDEN | UCR1_UARTEN;

	if (USE_IRDA(sport)) {
		temp |= UCR1_IREN;
		temp &= ~(UCR1_RTSDEN);
	}

	writel(temp, sport->port.membase + UCR1);

	temp = readl(sport->port.membase + UCR2);
	temp |= (UCR2_RXEN | UCR2_TXEN);
	writel(temp, sport->port.membase + UCR2);

	if (USE_IRDA(sport)) {
		/* clear RX-FIFO */
		int i = 64;
		while ((--i > 0) &&
			(readl(sport->port.membase + URXD0) & URXD_CHARRDY)) {
			barrier();
		}
	}

	if (!cpu_is_mx1()) {
		temp = readl(sport->port.membase + UCR3);
		temp |= MX2_UCR3_RXDMUXSEL;
		writel(temp, sport->port.membase + UCR3);
	}

	if (USE_IRDA(sport)) {
		temp = readl(sport->port.membase + UCR4);
		if (sport->irda_inv_rx)
			temp |= UCR4_INVR;
		else
			temp &= ~(UCR4_INVR);
		writel(temp | UCR4_DREN, sport->port.membase + UCR4);

		temp = readl(sport->port.membase + UCR3);
		if (sport->irda_inv_tx)
			temp |= UCR3_INVT;
		else
			temp &= ~(UCR3_INVT);
		writel(temp, sport->port.membase + UCR3);
	}

	/*
	 * Enable modem status interrupts
	 */
	spin_lock_irqsave(&sport->port.lock,flags);
	imx_enable_ms(&sport->port);
	spin_unlock_irqrestore(&sport->port.lock,flags);

	if (USE_IRDA(sport)) {
		struct imxuart_platform_data *pdata;
		pdata = sport->port.dev->platform_data;
		sport->irda_inv_rx = pdata->irda_inv_rx;
		sport->irda_inv_tx = pdata->irda_inv_tx;
		sport->trcv_delay = pdata->transceiver_delay;
		if (pdata->irda_enable)
			pdata->irda_enable(1);
	}

	return 0;

error_out3:
	if (sport->txirq)
		free_irq(sport->txirq, sport);
error_out2:
	if (sport->rxirq)
		free_irq(sport->rxirq, sport);
error_out1:
	return retval;
}