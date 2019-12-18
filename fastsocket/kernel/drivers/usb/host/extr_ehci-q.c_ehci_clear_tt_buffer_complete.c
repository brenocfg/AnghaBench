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
struct usb_host_endpoint {struct ehci_qh* hcpriv; } ;
struct usb_hcd {int /*<<< orphan*/  state; } ;
struct ehci_qh {scalar_t__ qh_state; int /*<<< orphan*/  qtd_list; scalar_t__ clearing_tt; } ;
struct ehci_hcd {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ HC_IS_RUNNING (int /*<<< orphan*/ ) ; 
 scalar_t__ QH_STATE_IDLE ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qh_link_async (struct ehci_hcd*,struct ehci_qh*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ehci_clear_tt_buffer_complete(struct usb_hcd *hcd,
		struct usb_host_endpoint *ep)
{
	struct ehci_hcd		*ehci = hcd_to_ehci(hcd);
	struct ehci_qh		*qh = ep->hcpriv;
	unsigned long		flags;

	spin_lock_irqsave(&ehci->lock, flags);
	qh->clearing_tt = 0;
	if (qh->qh_state == QH_STATE_IDLE && !list_empty(&qh->qtd_list)
			&& HC_IS_RUNNING(hcd->state))
		qh_link_async(ehci, qh);
	spin_unlock_irqrestore(&ehci->lock, flags);
}