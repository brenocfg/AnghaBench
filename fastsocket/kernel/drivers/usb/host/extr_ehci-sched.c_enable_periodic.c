#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ehci_hcd {int next_uframe; int periodic_size; int /*<<< orphan*/  last_periodic_enable; int /*<<< orphan*/  broken_periodic; TYPE_1__* regs; int /*<<< orphan*/  periodic_sched; } ;
struct TYPE_5__ {int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int /*<<< orphan*/  frame_index; int /*<<< orphan*/  command; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int CMD_PSE ; 
 int /*<<< orphan*/  HC_STATE_RUNNING ; 
 int /*<<< orphan*/  STS_PSS ; 
 int ehci_readl (struct ehci_hcd*,int /*<<< orphan*/ *) ; 
 TYPE_2__* ehci_to_hcd (struct ehci_hcd*) ; 
 int /*<<< orphan*/  ehci_writel (struct ehci_hcd*,int,int /*<<< orphan*/ *) ; 
 int handshake_on_error_set_halt (struct ehci_hcd*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_hc_died (TYPE_2__*) ; 

__attribute__((used)) static int enable_periodic (struct ehci_hcd *ehci)
{
	u32	cmd;
	int	status;

	if (ehci->periodic_sched++)
		return 0;

	/* did clearing PSE did take effect yet?
	 * takes effect only at frame boundaries...
	 */
	status = handshake_on_error_set_halt(ehci, &ehci->regs->status,
					     STS_PSS, 0, 9 * 125);
	if (status) {
		usb_hc_died(ehci_to_hcd(ehci));
		return status;
	}

	cmd = ehci_readl(ehci, &ehci->regs->command) | CMD_PSE;
	ehci_writel(ehci, cmd, &ehci->regs->command);
	/* posted write ... PSS happens later */
	ehci_to_hcd(ehci)->state = HC_STATE_RUNNING;

	/* make sure ehci_work scans these */
	ehci->next_uframe = ehci_readl(ehci, &ehci->regs->frame_index)
		% (ehci->periodic_size << 3);
	if (unlikely(ehci->broken_periodic))
		ehci->last_periodic_enable = ktime_get_real();
	return 0;
}