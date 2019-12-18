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
typedef  int u32 ;
struct usb_hcd {int /*<<< orphan*/  state; } ;
struct ehci_hcd {int /*<<< orphan*/  lock; scalar_t__* reset_done; int /*<<< orphan*/  port_c_suspend; TYPE_1__* regs; scalar_t__ has_ppcd; int /*<<< orphan*/  hcs_params; } ;
struct TYPE_2__ {int /*<<< orphan*/ * port_status; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int HCS_N_PORTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HC_IS_RUNNING (int /*<<< orphan*/ ) ; 
 int PORT_CSC ; 
 int PORT_OCC ; 
 int PORT_PEC ; 
 int STS_PCD ; 
 int ehci_readl (struct ehci_hcd*,int /*<<< orphan*/ *) ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 
 int /*<<< orphan*/  ignore_oc ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after_eq (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
ehci_hub_status_data (struct usb_hcd *hcd, char *buf)
{
	struct ehci_hcd	*ehci = hcd_to_ehci (hcd);
	u32		temp, status = 0;
	u32		mask;
	int		ports, i, retval = 1;
	unsigned long	flags;
	u32		ppcd = 0;

	/* if !USB_SUSPEND, root hub timers won't get shut down ... */
	if (!HC_IS_RUNNING(hcd->state))
		return 0;

	/* init status to no-changes */
	buf [0] = 0;
	ports = HCS_N_PORTS (ehci->hcs_params);
	if (ports > 7) {
		buf [1] = 0;
		retval++;
	}

	/* Some boards (mostly VIA?) report bogus overcurrent indications,
	 * causing massive log spam unless we completely ignore them.  It
	 * may be relevant that VIA VT8235 controllers, where PORT_POWER is
	 * always set, seem to clear PORT_OCC and PORT_CSC when writing to
	 * PORT_POWER; that's surprising, but maybe within-spec.
	 */
	if (!ignore_oc)
		mask = PORT_CSC | PORT_PEC | PORT_OCC;
	else
		mask = PORT_CSC | PORT_PEC;
	// PORT_RESUME from hardware ~= PORT_STAT_C_SUSPEND

	/* no hub change reports (bit 0) for now (power, ...) */

	/* port N changes (bit N)? */
	spin_lock_irqsave (&ehci->lock, flags);

	/* get per-port change detect bits */
	if (ehci->has_ppcd)
		ppcd = ehci_readl(ehci, &ehci->regs->status) >> 16;

	for (i = 0; i < ports; i++) {
		/* leverage per-port change bits feature */
		if (ehci->has_ppcd && !(ppcd & (1 << i)))
			continue;
		temp = ehci_readl(ehci, &ehci->regs->port_status [i]);

		/*
		 * Return status information even for ports with OWNER set.
		 * Otherwise khubd wouldn't see the disconnect event when a
		 * high-speed device is switched over to the companion
		 * controller by the user.
		 */

		if ((temp & mask) != 0 || test_bit(i, &ehci->port_c_suspend)
				|| (ehci->reset_done[i] && time_after_eq(
					jiffies, ehci->reset_done[i]))) {
			if (i < 7)
			    buf [0] |= 1 << (i + 1);
			else
			    buf [1] |= 1 << (i - 7);
			status = STS_PCD;
		}
	}
	/* FIXME autosuspend idle root hubs */
	spin_unlock_irqrestore (&ehci->lock, flags);
	return status ? retval : 0;
}