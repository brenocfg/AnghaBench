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
 unsigned int TIOCM_RTS ; 
 scalar_t__ UCR2 ; 
 unsigned long UCR2_CTS ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void imx_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
	struct imx_port *sport = (struct imx_port *)port;
	unsigned long temp;

	temp = readl(sport->port.membase + UCR2) & ~UCR2_CTS;

	if (mctrl & TIOCM_RTS)
		temp |= UCR2_CTS;

	writel(temp, sport->port.membase + UCR2);
}