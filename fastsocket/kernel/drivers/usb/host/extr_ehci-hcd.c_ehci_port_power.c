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
struct ehci_hcd {TYPE_1__* regs; int /*<<< orphan*/  hcs_params; } ;
struct TYPE_2__ {int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPortFeature ; 
 unsigned int HCS_N_PORTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCS_PPC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPortFeature ; 
 int /*<<< orphan*/  USB_PORT_FEAT_POWER ; 
 int /*<<< orphan*/  ehci_dbg (struct ehci_hcd*,char*,char*) ; 
 int /*<<< orphan*/  ehci_hub_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehci_readl (struct ehci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehci_to_hcd (struct ehci_hcd*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void ehci_port_power (struct ehci_hcd *ehci, int is_on)
{
	unsigned port;

	if (!HCS_PPC (ehci->hcs_params))
		return;

	ehci_dbg (ehci, "...power%s ports...\n", is_on ? "up" : "down");
	for (port = HCS_N_PORTS (ehci->hcs_params); port > 0; )
		(void) ehci_hub_control(ehci_to_hcd(ehci),
				is_on ? SetPortFeature : ClearPortFeature,
				USB_PORT_FEAT_POWER,
				port--, NULL, 0);
	/* Flush those writes */
	ehci_readl(ehci, &ehci->regs->command);
	msleep(20);
}