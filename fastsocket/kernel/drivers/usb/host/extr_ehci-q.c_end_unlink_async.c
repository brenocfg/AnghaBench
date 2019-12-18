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
struct TYPE_5__ {int /*<<< orphan*/ * qh; } ;
struct ehci_qh {int /*<<< orphan*/  qtd_list; struct ehci_qh* reclaim; TYPE_1__ qh_next; int /*<<< orphan*/  qh_state; } ;
struct ehci_hcd {struct ehci_qh* reclaim; TYPE_3__* async; } ;
struct TYPE_8__ {int /*<<< orphan*/  state; } ;
struct TYPE_6__ {int /*<<< orphan*/ * qh; } ;
struct TYPE_7__ {TYPE_2__ qh_next; } ;

/* Variables and functions */
 scalar_t__ HC_IS_RUNNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QH_STATE_IDLE ; 
 int /*<<< orphan*/  TIMER_ASYNC_OFF ; 
 TYPE_4__* ehci_to_hcd (struct ehci_hcd*) ; 
 int /*<<< orphan*/  iaa_watchdog_done (struct ehci_hcd*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qh_completions (struct ehci_hcd*,struct ehci_qh*) ; 
 int /*<<< orphan*/  qh_link_async (struct ehci_hcd*,struct ehci_qh*) ; 
 int /*<<< orphan*/  qh_put (struct ehci_qh*) ; 
 int /*<<< orphan*/  start_unlink_async (struct ehci_hcd*,struct ehci_qh*) ; 
 int /*<<< orphan*/  timer_action (struct ehci_hcd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void end_unlink_async (struct ehci_hcd *ehci)
{
	struct ehci_qh		*qh = ehci->reclaim;
	struct ehci_qh		*next;

	iaa_watchdog_done(ehci);

	// qh->hw_next = cpu_to_hc32(qh->qh_dma);
	qh->qh_state = QH_STATE_IDLE;
	qh->qh_next.qh = NULL;
	qh_put (qh);			// refcount from reclaim

	/* other unlink(s) may be pending (in QH_STATE_UNLINK_WAIT) */
	next = qh->reclaim;
	ehci->reclaim = next;
	qh->reclaim = NULL;

	qh_completions (ehci, qh);

	if (!list_empty (&qh->qtd_list)
			&& HC_IS_RUNNING (ehci_to_hcd(ehci)->state))
		qh_link_async (ehci, qh);
	else {
		/* it's not free to turn the async schedule on/off; leave it
		 * active but idle for a while once it empties.
		 */
		if (HC_IS_RUNNING (ehci_to_hcd(ehci)->state)
				&& ehci->async->qh_next.qh == NULL)
			timer_action (ehci, TIMER_ASYNC_OFF);
	}
	qh_put(qh);			/* refcount from async list */

	if (next) {
		ehci->reclaim = NULL;
		start_unlink_async (ehci, next);
	}
}