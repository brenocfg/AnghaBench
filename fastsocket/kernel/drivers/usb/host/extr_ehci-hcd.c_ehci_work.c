#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ehci_hcd {int scanning; int next_uframe; scalar_t__ periodic_sched; TYPE_2__* async; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_5__ {TYPE_1__ qh_next; } ;

/* Variables and functions */
 scalar_t__ HC_IS_RUNNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMER_IO_WATCHDOG ; 
 TYPE_3__* ehci_to_hcd (struct ehci_hcd*) ; 
 int /*<<< orphan*/  scan_async (struct ehci_hcd*) ; 
 int /*<<< orphan*/  scan_periodic (struct ehci_hcd*) ; 
 int /*<<< orphan*/  timer_action (struct ehci_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_action_done (struct ehci_hcd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ehci_work (struct ehci_hcd *ehci)
{
	timer_action_done (ehci, TIMER_IO_WATCHDOG);

	/* another CPU may drop ehci->lock during a schedule scan while
	 * it reports urb completions.  this flag guards against bogus
	 * attempts at re-entrant schedule scanning.
	 */
	if (ehci->scanning)
		return;
	ehci->scanning = 1;
	scan_async (ehci);
	if (ehci->next_uframe != -1)
		scan_periodic (ehci);
	ehci->scanning = 0;

	/* the IO watchdog guards against hardware or driver bugs that
	 * misplace IRQs, and should let us run completely without IRQs.
	 * such lossage has been observed on both VT6202 and VT8235.
	 */
	if (HC_IS_RUNNING (ehci_to_hcd(ehci)->state) &&
			(ehci->async->qh_next.ptr != NULL ||
			 ehci->periodic_sched != 0))
		timer_action (ehci, TIMER_IO_WATCHDOG);
}