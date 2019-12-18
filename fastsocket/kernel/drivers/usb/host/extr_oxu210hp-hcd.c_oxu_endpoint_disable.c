#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_host_endpoint {struct ehci_qh* hcpriv; TYPE_4__ desc; } ;
struct usb_hcd {int /*<<< orphan*/  state; } ;
struct oxu_hcd {int /*<<< orphan*/  lock; TYPE_2__* async; } ;
struct TYPE_7__ {struct ehci_qh* qh; } ;
struct ehci_qh {scalar_t__ hw_info1; int qh_state; int /*<<< orphan*/  qtd_list; TYPE_3__ qh_next; } ;
struct TYPE_5__ {struct ehci_qh* qh; } ;
struct TYPE_6__ {TYPE_1__ qh_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  HC_IS_RUNNING (int /*<<< orphan*/ ) ; 
#define  QH_STATE_IDLE 130 
#define  QH_STATE_LINKED 129 
#define  QH_STATE_UNLINK 128 
 struct oxu_hcd* hcd_to_oxu (struct usb_hcd*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oxu_err (struct oxu_hcd*,char*,struct ehci_qh*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  oxu_vdbg (struct oxu_hcd*,char*) ; 
 int /*<<< orphan*/  qh_put (struct ehci_qh*) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  unlink_async (struct oxu_hcd*,struct ehci_qh*) ; 

__attribute__((used)) static void oxu_endpoint_disable(struct usb_hcd *hcd,
					struct usb_host_endpoint *ep)
{
	struct oxu_hcd *oxu = hcd_to_oxu(hcd);
	unsigned long		flags;
	struct ehci_qh		*qh, *tmp;

	/* ASSERT:  any requests/urbs are being unlinked */
	/* ASSERT:  nobody can be submitting urbs for this any more */

rescan:
	spin_lock_irqsave(&oxu->lock, flags);
	qh = ep->hcpriv;
	if (!qh)
		goto done;

	/* endpoints can be iso streams.  for now, we don't
	 * accelerate iso completions ... so spin a while.
	 */
	if (qh->hw_info1 == 0) {
		oxu_vdbg(oxu, "iso delay\n");
		goto idle_timeout;
	}

	if (!HC_IS_RUNNING(hcd->state))
		qh->qh_state = QH_STATE_IDLE;
	switch (qh->qh_state) {
	case QH_STATE_LINKED:
		for (tmp = oxu->async->qh_next.qh;
				tmp && tmp != qh;
				tmp = tmp->qh_next.qh)
			continue;
		/* periodic qh self-unlinks on empty */
		if (!tmp)
			goto nogood;
		unlink_async(oxu, qh);
		/* FALL THROUGH */
	case QH_STATE_UNLINK:		/* wait for hw to finish? */
idle_timeout:
		spin_unlock_irqrestore(&oxu->lock, flags);
		schedule_timeout_uninterruptible(1);
		goto rescan;
	case QH_STATE_IDLE:		/* fully unlinked */
		if (list_empty(&qh->qtd_list)) {
			qh_put(qh);
			break;
		}
		/* else FALL THROUGH */
	default:
nogood:
		/* caller was supposed to have unlinked any requests;
		 * that's not our job.  just leak this memory.
		 */
		oxu_err(oxu, "qh %p (#%02x) state %d%s\n",
			qh, ep->desc.bEndpointAddress, qh->qh_state,
			list_empty(&qh->qtd_list) ? "" : "(has tds)");
		break;
	}
	ep->hcpriv = NULL;
done:
	spin_unlock_irqrestore(&oxu->lock, flags);
	return;
}