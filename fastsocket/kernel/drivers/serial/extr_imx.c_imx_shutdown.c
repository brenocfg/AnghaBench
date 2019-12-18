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
struct imxuart_platform_data {int /*<<< orphan*/  (* irda_enable ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {scalar_t__ irq; scalar_t__ membase; TYPE_1__* dev; } ;
struct imx_port {scalar_t__ txirq; scalar_t__ rtsirq; scalar_t__ rxirq; TYPE_2__ port; int /*<<< orphan*/  timer; } ;
struct TYPE_3__ {struct imxuart_platform_data* platform_data; } ;

/* Variables and functions */
 scalar_t__ UCR1 ; 
 unsigned long UCR1_IREN ; 
 unsigned long UCR1_RRDYEN ; 
 unsigned long UCR1_RTSDEN ; 
 unsigned long UCR1_TXMPTYEN ; 
 unsigned long UCR1_UARTEN ; 
 scalar_t__ UCR2 ; 
 unsigned long UCR2_TXEN ; 
 scalar_t__ USE_IRDA (struct imx_port*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct imx_port*) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void imx_shutdown(struct uart_port *port)
{
	struct imx_port *sport = (struct imx_port *)port;
	unsigned long temp;

	temp = readl(sport->port.membase + UCR2);
	temp &= ~(UCR2_TXEN);
	writel(temp, sport->port.membase + UCR2);

	if (USE_IRDA(sport)) {
		struct imxuart_platform_data *pdata;
		pdata = sport->port.dev->platform_data;
		if (pdata->irda_enable)
			pdata->irda_enable(0);
	}

	/*
	 * Stop our timer.
	 */
	del_timer_sync(&sport->timer);

	/*
	 * Free the interrupts
	 */
	if (sport->txirq > 0) {
		if (!USE_IRDA(sport))
			free_irq(sport->rtsirq, sport);
		free_irq(sport->txirq, sport);
		free_irq(sport->rxirq, sport);
	} else
		free_irq(sport->port.irq, sport);

	/*
	 * Disable all interrupts, port and break condition.
	 */

	temp = readl(sport->port.membase + UCR1);
	temp &= ~(UCR1_TXMPTYEN | UCR1_RRDYEN | UCR1_RTSDEN | UCR1_UARTEN);
	if (USE_IRDA(sport))
		temp &= ~(UCR1_IREN);

	writel(temp, sport->port.membase + UCR1);
}