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
struct oxu_hcd {int /*<<< orphan*/  hcs_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPortFeature ; 
 unsigned int HCS_N_PORTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCS_PPC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPortFeature ; 
 int /*<<< orphan*/  USB_PORT_FEAT_POWER ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  oxu_dbg (struct oxu_hcd*,char*,char*) ; 
 int /*<<< orphan*/  oxu_hub_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxu_to_hcd (struct oxu_hcd*) ; 

__attribute__((used)) static void ehci_port_power(struct oxu_hcd *oxu, int is_on)
{
	unsigned port;

	if (!HCS_PPC(oxu->hcs_params))
		return;

	oxu_dbg(oxu, "...power%s ports...\n", is_on ? "up" : "down");
	for (port = HCS_N_PORTS(oxu->hcs_params); port > 0; )
		(void) oxu_hub_control(oxu_to_hcd(oxu),
				is_on ? SetPortFeature : ClearPortFeature,
				USB_PORT_FEAT_POWER,
				port--, NULL, 0);
	msleep(20);
}