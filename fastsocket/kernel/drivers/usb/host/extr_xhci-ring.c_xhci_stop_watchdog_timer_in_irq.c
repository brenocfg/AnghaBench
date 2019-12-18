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
struct xhci_virt_ep {int /*<<< orphan*/  stop_cmds_pending; int /*<<< orphan*/  stop_cmd_timer; int /*<<< orphan*/  ep_state; } ;
struct xhci_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP_HALT_PENDING ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xhci_stop_watchdog_timer_in_irq(struct xhci_hcd *xhci,
		struct xhci_virt_ep *ep)
{
	ep->ep_state &= ~EP_HALT_PENDING;
	/* Can't del_timer_sync in interrupt, so we attempt to cancel.  If the
	 * timer is running on another CPU, we don't decrement stop_cmds_pending
	 * (since we didn't successfully stop the watchdog timer).
	 */
	if (del_timer(&ep->stop_cmd_timer))
		ep->stop_cmds_pending--;
}