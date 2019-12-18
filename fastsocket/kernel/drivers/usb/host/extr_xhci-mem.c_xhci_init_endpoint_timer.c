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
struct TYPE_2__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct xhci_virt_ep {struct xhci_hcd* xhci; TYPE_1__ stop_cmd_timer; } ;
struct xhci_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  xhci_stop_endpoint_command_watchdog ; 

__attribute__((used)) static void xhci_init_endpoint_timer(struct xhci_hcd *xhci,
		struct xhci_virt_ep *ep)
{
	init_timer(&ep->stop_cmd_timer);
	ep->stop_cmd_timer.data = (unsigned long) ep;
	ep->stop_cmd_timer.function = xhci_stop_endpoint_command_watchdog;
	ep->xhci = xhci;
}