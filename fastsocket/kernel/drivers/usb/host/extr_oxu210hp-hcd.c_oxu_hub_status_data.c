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
struct oxu_hcd {int /*<<< orphan*/  lock; scalar_t__* reset_done; TYPE_1__* regs; int /*<<< orphan*/  hcs_params; } ;
struct TYPE_2__ {int /*<<< orphan*/ * port_status; } ;

/* Variables and functions */
 int HCS_N_PORTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HC_IS_RUNNING (int /*<<< orphan*/ ) ; 
 int PORT_CONNECT ; 
 int PORT_CSC ; 
 int PORT_OCC ; 
 int PORT_PEC ; 
 int PORT_RESUME ; 
 int STS_PCD ; 
 struct oxu_hcd* hcd_to_oxu (struct usb_hcd*) ; 
 int /*<<< orphan*/  ignore_oc ; 
 int /*<<< orphan*/  jiffies ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after_eq (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int oxu_hub_status_data(struct usb_hcd *hcd, char *buf)
{
	struct oxu_hcd *oxu = hcd_to_oxu(hcd);
	u32 temp, mask, status = 0;
	int ports, i, retval = 1;
	unsigned long flags;

	/* if !USB_SUSPEND, root hub timers won't get shut down ... */
	if (!HC_IS_RUNNING(hcd->state))
		return 0;

	/* init status to no-changes */
	buf[0] = 0;
	ports = HCS_N_PORTS(oxu->hcs_params);
	if (ports > 7) {
		buf[1] = 0;
		retval++;
	}

	/* Some boards (mostly VIA?) report bogus overcurrent indications,
	 * causing massive log spam unless we completely ignore them.  It
	 * may be relevant that VIA VT8235 controlers, where PORT_POWER is
	 * always set, seem to clear PORT_OCC and PORT_CSC when writing to
	 * PORT_POWER; that's surprising, but maybe within-spec.
	 */
	if (!ignore_oc)
		mask = PORT_CSC | PORT_PEC | PORT_OCC;
	else
		mask = PORT_CSC | PORT_PEC;

	/* no hub change reports (bit 0) for now (power, ...) */

	/* port N changes (bit N)? */
	spin_lock_irqsave(&oxu->lock, flags);
	for (i = 0; i < ports; i++) {
		temp = readl(&oxu->regs->port_status[i]);

		/*
		 * Return status information even for ports with OWNER set.
		 * Otherwise khubd wouldn't see the disconnect event when a
		 * high-speed device is switched over to the companion
		 * controller by the user.
		 */

		if (!(temp & PORT_CONNECT))
			oxu->reset_done[i] = 0;
		if ((temp & mask) != 0 || ((temp & PORT_RESUME) != 0 &&
				time_after_eq(jiffies, oxu->reset_done[i]))) {
			if (i < 7)
				buf[0] |= 1 << (i + 1);
			else
				buf[1] |= 1 << (i - 7);
			status = STS_PCD;
		}
	}
	/* FIXME autosuspend idle root hubs */
	spin_unlock_irqrestore(&oxu->lock, flags);
	return status ? retval : 0;
}