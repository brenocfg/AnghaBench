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
struct TYPE_2__ {scalar_t__ membase; } ;
struct imx_port {TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ UCR1 ; 
 unsigned long UCR1_RRDYEN ; 
 unsigned long UCR1_TRDYEN ; 
 unsigned long UCR1_TXMPTYEN ; 
 scalar_t__ UCR4 ; 
 unsigned long UCR4_DREN ; 
 unsigned long UCR4_TCEN ; 
 scalar_t__ USE_IRDA (struct imx_port*) ; 
 scalar_t__ UTS ; 
 int UTS_TXEMPTY ; 
 int /*<<< orphan*/  imx_transmit_buffer (struct imx_port*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void imx_start_tx(struct uart_port *port)
{
	struct imx_port *sport = (struct imx_port *)port;
	unsigned long temp;

	if (USE_IRDA(sport)) {
		/* half duplex in IrDA mode; have to disable receive mode */
		temp = readl(sport->port.membase + UCR4);
		temp &= ~(UCR4_DREN);
		writel(temp, sport->port.membase + UCR4);

		temp = readl(sport->port.membase + UCR1);
		temp &= ~(UCR1_RRDYEN);
		writel(temp, sport->port.membase + UCR1);
	}

	temp = readl(sport->port.membase + UCR1);
	writel(temp | UCR1_TXMPTYEN, sport->port.membase + UCR1);

	if (USE_IRDA(sport)) {
		temp = readl(sport->port.membase + UCR1);
		temp |= UCR1_TRDYEN;
		writel(temp, sport->port.membase + UCR1);

		temp = readl(sport->port.membase + UCR4);
		temp |= UCR4_TCEN;
		writel(temp, sport->port.membase + UCR4);
	}

	if (readl(sport->port.membase + UTS) & UTS_TXEMPTY)
		imx_transmit_buffer(sport);
}