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
struct usb_hcd {int dummy; } ;
struct dummy {int port_status; scalar_t__ rh_state; int /*<<< orphan*/  lock; int /*<<< orphan*/  re_timeout; scalar_t__ resuming; } ;

/* Variables and functions */
 scalar_t__ DUMMY_RH_SUSPENDED ; 
 int /*<<< orphan*/  HCD_HW_ACCESSIBLE (struct usb_hcd*) ; 
 int PORT_C_MASK ; 
 int USB_PORT_STAT_C_SUSPEND ; 
 int USB_PORT_STAT_SUSPEND ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dummy_dev (struct dummy*) ; 
 struct dummy* hcd_to_dummy (struct usb_hcd*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  set_link_state (struct dummy*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_hcd_resume_root_hub (struct usb_hcd*) ; 

__attribute__((used)) static int dummy_hub_status (struct usb_hcd *hcd, char *buf)
{
	struct dummy		*dum;
	unsigned long		flags;
	int			retval = 0;

	dum = hcd_to_dummy (hcd);

	spin_lock_irqsave (&dum->lock, flags);
	if (!HCD_HW_ACCESSIBLE(hcd))
		goto done;

	if (dum->resuming && time_after_eq (jiffies, dum->re_timeout)) {
		dum->port_status |= (USB_PORT_STAT_C_SUSPEND << 16);
		dum->port_status &= ~USB_PORT_STAT_SUSPEND;
		set_link_state (dum);
	}

	if ((dum->port_status & PORT_C_MASK) != 0) {
		*buf = (1 << 1);
		dev_dbg (dummy_dev(dum), "port status 0x%08x has changes\n",
				dum->port_status);
		retval = 1;
		if (dum->rh_state == DUMMY_RH_SUSPENDED)
			usb_hcd_resume_root_hub (hcd);
	}
done:
	spin_unlock_irqrestore (&dum->lock, flags);
	return retval;
}