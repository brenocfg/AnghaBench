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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * port_status; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOTCONN ; 
 scalar_t__ HUB_RESET_TIMEOUT ; 
 scalar_t__ HUB_ROOT_RESET_TIME ; 
 scalar_t__ PORT_CONNECT ; 
 scalar_t__ PORT_CSC ; 
 scalar_t__ PORT_PE ; 
 scalar_t__ PORT_RESET ; 
 scalar_t__ PORT_RWC_BITS ; 
 int /*<<< orphan*/  dbgp_ehci_status (char*) ; 
 int /*<<< orphan*/  dbgp_mdelay (scalar_t__) ; 
 TYPE_1__* ehci_regs ; 
 scalar_t__ readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ehci_reset_port(int port)
{
	u32 portsc;
	u32 delay_time, delay;
	int loop;

	dbgp_ehci_status("reset port");
	/* Reset the usb debug port */
	portsc = readl(&ehci_regs->port_status[port - 1]);
	portsc &= ~PORT_PE;
	portsc |= PORT_RESET;
	writel(portsc, &ehci_regs->port_status[port - 1]);

	delay = HUB_ROOT_RESET_TIME;
	for (delay_time = 0; delay_time < HUB_RESET_TIMEOUT;
	     delay_time += delay) {
		dbgp_mdelay(delay);
		portsc = readl(&ehci_regs->port_status[port - 1]);
		if (!(portsc & PORT_RESET))
			break;
	}
		if (portsc & PORT_RESET) {
			/* force reset to complete */
			loop = 100 * 1000;
			writel(portsc & ~(PORT_RWC_BITS | PORT_RESET),
				&ehci_regs->port_status[port - 1]);
			do {
				udelay(1);
				portsc = readl(&ehci_regs->port_status[port-1]);
			} while ((portsc & PORT_RESET) && (--loop > 0));
		}

		/* Device went away? */
		if (!(portsc & PORT_CONNECT))
			return -ENOTCONN;

		/* bomb out completely if something weird happend */
		if ((portsc & PORT_CSC))
			return -EINVAL;

		/* If we've finished resetting, then break out of the loop */
		if (!(portsc & PORT_RESET) && (portsc & PORT_PE))
			return 0;
	return -EBUSY;
}