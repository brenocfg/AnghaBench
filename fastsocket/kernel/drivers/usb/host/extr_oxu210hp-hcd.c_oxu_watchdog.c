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
typedef  int u32 ;
struct oxu_hcd {int reclaim_ready; int /*<<< orphan*/  lock; int /*<<< orphan*/  async; int /*<<< orphan*/  actions; TYPE_1__* regs; scalar_t__ reclaim; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int STS_IAA ; 
 int /*<<< orphan*/  TIMER_ASYNC_OFF ; 
 int /*<<< orphan*/  ehci_work (struct oxu_hcd*) ; 
 int /*<<< orphan*/  oxu_vdbg (struct oxu_hcd*,char*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  start_unlink_async (struct oxu_hcd*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void oxu_watchdog(unsigned long param)
{
	struct oxu_hcd	*oxu = (struct oxu_hcd *) param;
	unsigned long flags;

	spin_lock_irqsave(&oxu->lock, flags);

	/* lost IAA irqs wedge things badly; seen with a vt8235 */
	if (oxu->reclaim) {
		u32 status = readl(&oxu->regs->status);
		if (status & STS_IAA) {
			oxu_vdbg(oxu, "lost IAA\n");
			writel(STS_IAA, &oxu->regs->status);
			oxu->reclaim_ready = 1;
		}
	}

	/* stop async processing after it's idled a bit */
	if (test_bit(TIMER_ASYNC_OFF, &oxu->actions))
		start_unlink_async(oxu, oxu->async);

	/* oxu could run by timer, without IRQs ... */
	ehci_work(oxu);

	spin_unlock_irqrestore(&oxu->lock, flags);
}