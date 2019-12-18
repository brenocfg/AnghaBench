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
struct ehci_hcd {int /*<<< orphan*/  lock; int /*<<< orphan*/  async; int /*<<< orphan*/  actions; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMER_ASYNC_OFF ; 
 int /*<<< orphan*/  ehci_work (struct ehci_hcd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  start_unlink_async (struct ehci_hcd*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ehci_watchdog(unsigned long param)
{
	struct ehci_hcd		*ehci = (struct ehci_hcd *) param;
	unsigned long		flags;

	spin_lock_irqsave(&ehci->lock, flags);

	/* stop async processing after it's idled a bit */
	if (test_bit (TIMER_ASYNC_OFF, &ehci->actions))
		start_unlink_async (ehci, ehci->async);

	/* ehci could run by timer, without IRQs ... */
	ehci_work (ehci);

	spin_unlock_irqrestore (&ehci->lock, flags);
}