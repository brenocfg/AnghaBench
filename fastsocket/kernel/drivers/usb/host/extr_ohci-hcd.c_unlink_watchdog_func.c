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
struct ohci_hcd {unsigned int eds_scheduled; int zf_delay; int /*<<< orphan*/  lock; int /*<<< orphan*/  unlink_watchdog; TYPE_1__* regs; struct ed* ed_to_check; struct ed** periodic; } ;
struct ed {struct ed* ed_next; } ;
struct TYPE_2__ {int /*<<< orphan*/  control; int /*<<< orphan*/  intrenable; int /*<<< orphan*/  intrstatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ HZ ; 
 unsigned int NUM_INTS ; 
 int /*<<< orphan*/  OHCI_INTR_SF ; 
 int /*<<< orphan*/  check_ed (struct ohci_hcd*,struct ed*) ; 
 scalar_t__ jiffies ; 
 struct ed** kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ed**) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ohci_readl (struct ohci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ohci_writel (struct ohci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  round_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void unlink_watchdog_func(unsigned long _ohci)
{
	unsigned long	flags;
	unsigned	max;
	unsigned	seen_count = 0;
	unsigned	i;
	struct ed	**seen = NULL;
	struct ohci_hcd	*ohci = (struct ohci_hcd *) _ohci;

	spin_lock_irqsave(&ohci->lock, flags);
	max = ohci->eds_scheduled;
	if (!max)
		goto done;

	if (ohci->ed_to_check)
		goto out;

	seen = kcalloc(max, sizeof *seen, GFP_ATOMIC);
	if (!seen)
		goto out;

	for (i = 0; i < NUM_INTS; i++) {
		struct ed	*ed = ohci->periodic[i];

		while (ed) {
			unsigned	temp;

			/* scan this branch of the periodic schedule tree */
			for (temp = 0; temp < seen_count; temp++) {
				if (seen[temp] == ed) {
					/* we've checked it and what's after */
					ed = NULL;
					break;
				}
			}
			if (!ed)
				break;
			seen[seen_count++] = ed;
			if (!check_ed(ohci, ed)) {
				ed = ed->ed_next;
				continue;
			}

			/* HC's TD list is empty, but HCD sees at least one
			 * TD that's not been sent through the donelist.
			 */
			ohci->ed_to_check = ed;
			ohci->zf_delay = 2;

			/* The HC may wait until the next frame to report the
			 * TD as done through the donelist and INTR_WDH.  (We
			 * just *assume* it's not a multi-TD interrupt URB;
			 * those could defer the IRQ more than one frame, using
			 * DI...)  Check again after the next INTR_SF.
			 */
			ohci_writel(ohci, OHCI_INTR_SF,
					&ohci->regs->intrstatus);
			ohci_writel(ohci, OHCI_INTR_SF,
					&ohci->regs->intrenable);

			/* flush those writes */
			(void) ohci_readl(ohci, &ohci->regs->control);

			goto out;
		}
	}
out:
	kfree(seen);
	if (ohci->eds_scheduled)
		mod_timer(&ohci->unlink_watchdog, round_jiffies(jiffies + HZ));
done:
	spin_unlock_irqrestore(&ohci->lock, flags);
}