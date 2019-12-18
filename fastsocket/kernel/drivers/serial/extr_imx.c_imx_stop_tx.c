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
struct imx_port {int trcv_delay; TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ UCR1 ; 
 unsigned long UCR1_RRDYEN ; 
 unsigned long UCR1_TRDYEN ; 
 unsigned long UCR1_TXMPTYEN ; 
 scalar_t__ UCR4 ; 
 unsigned long UCR4_DREN ; 
 unsigned long UCR4_TCEN ; 
 scalar_t__ URXD0 ; 
 int URXD_CHARRDY ; 
 scalar_t__ USE_IRDA (struct imx_port*) ; 
 scalar_t__ USR2 ; 
 int USR2_TXDC ; 
 int /*<<< orphan*/  barrier () ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void imx_stop_tx(struct uart_port *port)
{
	struct imx_port *sport = (struct imx_port *)port;
	unsigned long temp;

	if (USE_IRDA(sport)) {
		/* half duplex - wait for end of transmission */
		int n = 256;
		while ((--n > 0) &&
		      !(readl(sport->port.membase + USR2) & USR2_TXDC)) {
			udelay(5);
			barrier();
		}
		/*
		 * irda transceiver - wait a bit more to avoid
		 * cutoff, hardware dependent
		 */
		udelay(sport->trcv_delay);

		/*
		 * half duplex - reactivate receive mode,
		 * flush receive pipe echo crap
		 */
		if (readl(sport->port.membase + USR2) & USR2_TXDC) {
			temp = readl(sport->port.membase + UCR1);
			temp &= ~(UCR1_TXMPTYEN | UCR1_TRDYEN);
			writel(temp, sport->port.membase + UCR1);

			temp = readl(sport->port.membase + UCR4);
			temp &= ~(UCR4_TCEN);
			writel(temp, sport->port.membase + UCR4);

			while (readl(sport->port.membase + URXD0) &
			       URXD_CHARRDY)
				barrier();

			temp = readl(sport->port.membase + UCR1);
			temp |= UCR1_RRDYEN;
			writel(temp, sport->port.membase + UCR1);

			temp = readl(sport->port.membase + UCR4);
			temp |= UCR4_DREN;
			writel(temp, sport->port.membase + UCR4);
		}
		return;
	}

	temp = readl(sport->port.membase + UCR1);
	writel(temp & ~UCR1_TXMPTYEN, sport->port.membase + UCR1);
}