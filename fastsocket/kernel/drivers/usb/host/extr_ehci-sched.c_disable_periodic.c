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
struct ehci_hcd {int broken_periodic; int next_uframe; TYPE_1__* regs; int /*<<< orphan*/  last_periodic_enable; scalar_t__ periodic_sched; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_2__ {int /*<<< orphan*/  command; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int CMD_PSE ; 
 int /*<<< orphan*/  STS_PSS ; 
 int ehci_readl (struct ehci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehci_to_hcd (struct ehci_hcd*) ; 
 int /*<<< orphan*/  ehci_writel (struct ehci_hcd*,int,int /*<<< orphan*/ *) ; 
 int handshake_on_error_set_halt (struct ehci_hcd*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_add_us (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 scalar_t__ ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_hc_died (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int disable_periodic (struct ehci_hcd *ehci)
{
	u32	cmd;
	int	status;

	if (--ehci->periodic_sched)
		return 0;

	if (unlikely(ehci->broken_periodic)) {
		/* delay experimentally determined */
		ktime_t safe = ktime_add_us(ehci->last_periodic_enable, 1000);
		ktime_t now = ktime_get_real();
		s64 delay = ktime_us_delta(safe, now);

		if (unlikely(delay > 0))
			udelay(delay);
	}

	/* did setting PSE not take effect yet?
	 * takes effect only at frame boundaries...
	 */
	status = handshake_on_error_set_halt(ehci, &ehci->regs->status,
					     STS_PSS, STS_PSS, 9 * 125);
	if (status) {
		usb_hc_died(ehci_to_hcd(ehci));
		return status;
	}

	cmd = ehci_readl(ehci, &ehci->regs->command) & ~CMD_PSE;
	ehci_writel(ehci, cmd, &ehci->regs->command);
	/* posted write ... */

	ehci->next_uframe = -1;
	return 0;
}