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
struct TYPE_2__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_host_endpoint {struct ed* hcpriv; TYPE_1__ desc; } ;
struct usb_hcd {int /*<<< orphan*/  state; } ;
struct ohci_hcd {int zf_delay; int /*<<< orphan*/  lock; struct ed* ed_to_check; int /*<<< orphan*/  eds_scheduled; } ;
struct ed {int state; scalar_t__ type; int /*<<< orphan*/  dummy; int /*<<< orphan*/  td_list; } ;

/* Variables and functions */
#define  ED_IDLE 129 
#define  ED_UNLINK 128 
 int /*<<< orphan*/  HC_IS_RUNNING (int /*<<< orphan*/ ) ; 
 scalar_t__ PIPE_INTERRUPT ; 
 int /*<<< orphan*/  ed_free (struct ohci_hcd*,struct ed*) ; 
 int /*<<< orphan*/  finish_unlinks (struct ohci_hcd*,int /*<<< orphan*/ ) ; 
 struct ohci_hcd* hcd_to_ohci (struct usb_hcd*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ohci_err (struct ohci_hcd*,char*,struct ed*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  ohci_warn (struct ohci_hcd*,char*) ; 
 scalar_t__ quirk_zfmicro (struct ohci_hcd*) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  td_free (struct ohci_hcd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ohci_endpoint_disable (struct usb_hcd *hcd, struct usb_host_endpoint *ep)
{
	struct ohci_hcd		*ohci = hcd_to_ohci (hcd);
	unsigned long		flags;
	struct ed		*ed = ep->hcpriv;
	unsigned		limit = 1000;

	/* ASSERT:  any requests/urbs are being unlinked */
	/* ASSERT:  nobody can be submitting urbs for this any more */

	if (!ed)
		return;

rescan:
	spin_lock_irqsave (&ohci->lock, flags);

	if (!HC_IS_RUNNING (hcd->state)) {
sanitize:
		ed->state = ED_IDLE;
		if (quirk_zfmicro(ohci) && ed->type == PIPE_INTERRUPT)
			ohci->eds_scheduled--;
		finish_unlinks (ohci, 0);
	}

	switch (ed->state) {
	case ED_UNLINK:		/* wait for hw to finish? */
		/* major IRQ delivery trouble loses INTR_SF too... */
		if (limit-- == 0) {
			ohci_warn(ohci, "ED unlink timeout\n");
			if (quirk_zfmicro(ohci)) {
				ohci_warn(ohci, "Attempting ZF TD recovery\n");
				ohci->ed_to_check = ed;
				ohci->zf_delay = 2;
			}
			goto sanitize;
		}
		spin_unlock_irqrestore (&ohci->lock, flags);
		schedule_timeout_uninterruptible(1);
		goto rescan;
	case ED_IDLE:		/* fully unlinked */
		if (list_empty (&ed->td_list)) {
			td_free (ohci, ed->dummy);
			ed_free (ohci, ed);
			break;
		}
		/* else FALL THROUGH */
	default:
		/* caller was supposed to have unlinked any requests;
		 * that's not our job.  can't recover; must leak ed.
		 */
		ohci_err (ohci, "leak ed %p (#%02x) state %d%s\n",
			ed, ep->desc.bEndpointAddress, ed->state,
			list_empty (&ed->td_list) ? "" : " (has tds)");
		td_free (ohci, ed->dummy);
		break;
	}
	ep->hcpriv = NULL;
	spin_unlock_irqrestore (&ohci->lock, flags);
	return;
}