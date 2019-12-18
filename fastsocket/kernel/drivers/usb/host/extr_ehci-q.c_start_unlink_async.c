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
struct TYPE_6__ {struct ehci_qh* qh; } ;
struct ehci_qh {scalar_t__ qh_state; TYPE_2__ qh_next; TYPE_1__* hw; } ;
struct ehci_hcd {TYPE_3__* regs; struct ehci_qh* qh_scan_next; struct ehci_qh* async; struct ehci_qh* reclaim; int /*<<< orphan*/  lock; } ;
struct TYPE_8__ {scalar_t__ state; } ;
struct TYPE_7__ {int /*<<< orphan*/  command; } ;
struct TYPE_5__ {int /*<<< orphan*/  hw_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int CMD_ASE ; 
 int CMD_IAAD ; 
 int /*<<< orphan*/  HC_IS_RUNNING (scalar_t__) ; 
 scalar_t__ HC_STATE_HALT ; 
 scalar_t__ QH_STATE_LINKED ; 
 scalar_t__ QH_STATE_UNLINK ; 
 scalar_t__ QH_STATE_UNLINK_WAIT ; 
 int /*<<< orphan*/  TIMER_ASYNC_OFF ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int ehci_readl (struct ehci_hcd*,int /*<<< orphan*/ *) ; 
 TYPE_4__* ehci_to_hcd (struct ehci_hcd*) ; 
 int /*<<< orphan*/  ehci_writel (struct ehci_hcd*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  end_unlink_async (struct ehci_hcd*) ; 
 int /*<<< orphan*/  iaa_watchdog_start (struct ehci_hcd*) ; 
 struct ehci_qh* qh_get (struct ehci_qh*) ; 
 int /*<<< orphan*/  timer_action_done (struct ehci_hcd*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void start_unlink_async (struct ehci_hcd *ehci, struct ehci_qh *qh)
{
	int		cmd = ehci_readl(ehci, &ehci->regs->command);
	struct ehci_qh	*prev;

#ifdef DEBUG
	assert_spin_locked(&ehci->lock);
	if (ehci->reclaim
			|| (qh->qh_state != QH_STATE_LINKED
				&& qh->qh_state != QH_STATE_UNLINK_WAIT)
			)
		BUG ();
#endif

	/* stop async schedule right now? */
	if (unlikely (qh == ehci->async)) {
		/* can't get here without STS_ASS set */
		if (ehci_to_hcd(ehci)->state != HC_STATE_HALT
				&& !ehci->reclaim) {
			/* ... and CMD_IAAD clear */
			ehci_writel(ehci, cmd & ~CMD_ASE,
				    &ehci->regs->command);
			wmb ();
			// handshake later, if we need to
			timer_action_done (ehci, TIMER_ASYNC_OFF);
		}
		return;
	}

	qh->qh_state = QH_STATE_UNLINK;
	ehci->reclaim = qh = qh_get (qh);

	prev = ehci->async;
	while (prev->qh_next.qh != qh)
		prev = prev->qh_next.qh;

	prev->hw->hw_next = qh->hw->hw_next;
	prev->qh_next = qh->qh_next;
	if (ehci->qh_scan_next == qh)
		ehci->qh_scan_next = qh->qh_next.qh;
	wmb ();

	/* If the controller isn't running, we don't have to wait for it */
	if (unlikely(!HC_IS_RUNNING(ehci_to_hcd(ehci)->state))) {
		/* if (unlikely (qh->reclaim != 0))
		 *	this will recurse, probably not much
		 */
		end_unlink_async (ehci);
		return;
	}

	cmd |= CMD_IAAD;
	ehci_writel(ehci, cmd, &ehci->regs->command);
	(void)ehci_readl(ehci, &ehci->regs->command);
	iaa_watchdog_start(ehci);
}