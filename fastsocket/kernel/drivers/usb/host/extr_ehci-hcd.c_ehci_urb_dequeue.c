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
struct urb {scalar_t__ hcpriv; int /*<<< orphan*/  pipe; } ;
struct ehci_qh {int /*<<< orphan*/  qh_state; } ;
struct ehci_hcd {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
#define  PIPE_INTERRUPT 134 
#define  PIPE_ISOCHRONOUS 133 
#define  QH_STATE_COMPLETING 132 
#define  QH_STATE_IDLE 131 
#define  QH_STATE_LINKED 130 
#define  QH_STATE_UNLINK 129 
#define  QH_STATE_UNLINK_WAIT 128 
 int /*<<< orphan*/  ehci_dbg (struct ehci_hcd*,char*,struct ehci_qh*,int /*<<< orphan*/ ) ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 
 int /*<<< orphan*/  intr_deschedule (struct ehci_hcd*,struct ehci_qh*) ; 
 int /*<<< orphan*/  qh_completions (struct ehci_hcd*,struct ehci_qh*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  unlink_async (struct ehci_hcd*,struct ehci_qh*) ; 
 int usb_hcd_check_unlink_urb (struct usb_hcd*,struct urb*,int) ; 
 int usb_pipetype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ehci_urb_dequeue(struct usb_hcd *hcd, struct urb *urb, int status)
{
	struct ehci_hcd		*ehci = hcd_to_ehci (hcd);
	struct ehci_qh		*qh;
	unsigned long		flags;
	int			rc;

	spin_lock_irqsave (&ehci->lock, flags);
	rc = usb_hcd_check_unlink_urb(hcd, urb, status);
	if (rc)
		goto done;

	switch (usb_pipetype (urb->pipe)) {
	// case PIPE_CONTROL:
	// case PIPE_BULK:
	default:
		qh = (struct ehci_qh *) urb->hcpriv;
		if (!qh)
			break;
		switch (qh->qh_state) {
		case QH_STATE_LINKED:
		case QH_STATE_COMPLETING:
			unlink_async(ehci, qh);
			break;
		case QH_STATE_UNLINK:
		case QH_STATE_UNLINK_WAIT:
			/* already started */
			break;
		case QH_STATE_IDLE:
			/* QH might be waiting for a Clear-TT-Buffer */
			qh_completions(ehci, qh);
			break;
		}
		break;

	case PIPE_INTERRUPT:
		qh = (struct ehci_qh *) urb->hcpriv;
		if (!qh)
			break;
		switch (qh->qh_state) {
		case QH_STATE_LINKED:
		case QH_STATE_COMPLETING:
			intr_deschedule (ehci, qh);
			break;
		case QH_STATE_IDLE:
			qh_completions (ehci, qh);
			break;
		default:
			ehci_dbg (ehci, "bogus qh %p state %d\n",
					qh, qh->qh_state);
			goto done;
		}
		break;

	case PIPE_ISOCHRONOUS:
		// itd or sitd ...

		// wait till next completion, do it then.
		// completion irqs can wait up to 1024 msec,
		break;
	}
done:
	spin_unlock_irqrestore (&ehci->lock, flags);
	return rc;
}