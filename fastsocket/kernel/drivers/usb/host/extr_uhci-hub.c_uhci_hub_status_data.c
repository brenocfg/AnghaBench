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
struct uhci_hcd {int rh_state; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_for_hp; scalar_t__ auto_stop_time; scalar_t__ dead; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCD_HW_ACCESSIBLE (struct usb_hcd*) ; 
 scalar_t__ HZ ; 
#define  UHCI_RH_AUTO_STOPPED 132 
#define  UHCI_RH_RUNNING 131 
#define  UHCI_RH_RUNNING_NODEVS 130 
#define  UHCI_RH_SUSPENDED 129 
#define  UHCI_RH_SUSPENDING 128 
 int /*<<< orphan*/  any_ports_active (struct uhci_hcd*) ; 
 int get_hub_status_data (struct uhci_hcd*,char*) ; 
 struct uhci_hcd* hcd_to_uhci (struct usb_hcd*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  suspend_rh (struct uhci_hcd*,int const) ; 
 int /*<<< orphan*/  time_after_eq (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  uhci_check_ports (struct uhci_hcd*) ; 
 int /*<<< orphan*/  uhci_scan_schedule (struct uhci_hcd*) ; 
 int /*<<< orphan*/  usb_hcd_resume_root_hub (struct usb_hcd*) ; 
 int /*<<< orphan*/  wakeup_rh (struct uhci_hcd*) ; 

__attribute__((used)) static int uhci_hub_status_data(struct usb_hcd *hcd, char *buf)
{
	struct uhci_hcd *uhci = hcd_to_uhci(hcd);
	unsigned long flags;
	int status = 0;

	spin_lock_irqsave(&uhci->lock, flags);

	uhci_scan_schedule(uhci);
	if (!HCD_HW_ACCESSIBLE(hcd) || uhci->dead)
		goto done;
	uhci_check_ports(uhci);

	status = get_hub_status_data(uhci, buf);

	switch (uhci->rh_state) {
	    case UHCI_RH_SUSPENDING:
	    case UHCI_RH_SUSPENDED:
		/* if port change, ask to be resumed */
		if (status)
			usb_hcd_resume_root_hub(hcd);
		break;

	    case UHCI_RH_AUTO_STOPPED:
		/* if port change, auto start */
		if (status)
			wakeup_rh(uhci);
		break;

	    case UHCI_RH_RUNNING:
		/* are any devices attached? */
		if (!any_ports_active(uhci)) {
			uhci->rh_state = UHCI_RH_RUNNING_NODEVS;
			uhci->auto_stop_time = jiffies + HZ;
		}
		break;

	    case UHCI_RH_RUNNING_NODEVS:
		/* auto-stop if nothing connected for 1 second */
		if (any_ports_active(uhci))
			uhci->rh_state = UHCI_RH_RUNNING;
		else if (time_after_eq(jiffies, uhci->auto_stop_time) &&
				!uhci->wait_for_hp)
			suspend_rh(uhci, UHCI_RH_AUTO_STOPPED);
		break;

	    default:
		break;
	}

done:
	spin_unlock_irqrestore(&uhci->lock, flags);
	return status;
}