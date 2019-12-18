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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  lost_iaa; } ;
struct ehci_hcd {int /*<<< orphan*/  lock; TYPE_2__* regs; TYPE_1__ stats; int /*<<< orphan*/  iaa_watchdog; scalar_t__ reclaim; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
struct TYPE_5__ {int /*<<< orphan*/  status; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int CMD_IAAD ; 
 int /*<<< orphan*/  COUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ HC_IS_RUNNING (int /*<<< orphan*/ ) ; 
 int STS_IAA ; 
 int ehci_readl (struct ehci_hcd*,int /*<<< orphan*/ *) ; 
 TYPE_3__* ehci_to_hcd (struct ehci_hcd*) ; 
 int /*<<< orphan*/  ehci_vdbg (struct ehci_hcd*,char*,int,int) ; 
 int /*<<< orphan*/  ehci_writel (struct ehci_hcd*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  end_unlink_async (struct ehci_hcd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ehci_iaa_watchdog(unsigned long param)
{
	struct ehci_hcd		*ehci = (struct ehci_hcd *) param;
	unsigned long		flags;

	spin_lock_irqsave (&ehci->lock, flags);

	/* Lost IAA irqs wedge things badly; seen first with a vt8235.
	 * So we need this watchdog, but must protect it against both
	 * (a) SMP races against real IAA firing and retriggering, and
	 * (b) clean HC shutdown, when IAA watchdog was pending.
	 */
	if (ehci->reclaim
			&& !timer_pending(&ehci->iaa_watchdog)
			&& HC_IS_RUNNING(ehci_to_hcd(ehci)->state)) {
		u32 cmd, status;

		/* If we get here, IAA is *REALLY* late.  It's barely
		 * conceivable that the system is so busy that CMD_IAAD
		 * is still legitimately set, so let's be sure it's
		 * clear before we read STS_IAA.  (The HC should clear
		 * CMD_IAAD when it sets STS_IAA.)
		 */
		cmd = ehci_readl(ehci, &ehci->regs->command);
		if (cmd & CMD_IAAD)
			ehci_writel(ehci, cmd & ~CMD_IAAD,
					&ehci->regs->command);

		/* If IAA is set here it either legitimately triggered
		 * before we cleared IAAD above (but _way_ late, so we'll
		 * still count it as lost) ... or a silicon erratum:
		 * - VIA seems to set IAA without triggering the IRQ;
		 * - IAAD potentially cleared without setting IAA.
		 */
		status = ehci_readl(ehci, &ehci->regs->status);
		if ((status & STS_IAA) || !(cmd & CMD_IAAD)) {
			COUNT (ehci->stats.lost_iaa);
			ehci_writel(ehci, STS_IAA, &ehci->regs->status);
		}

		ehci_vdbg(ehci, "IAA watchdog: status %x cmd %x\n",
				status, cmd);
		end_unlink_async(ehci);
	}

	spin_unlock_irqrestore(&ehci->lock, flags);
}