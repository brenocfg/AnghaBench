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
struct xhci_hcd {int cmd_ring_state; TYPE_1__* dba; } ;
struct TYPE_2__ {int /*<<< orphan*/ * doorbell; } ;

/* Variables and functions */
 int CMD_RING_STATE_RUNNING ; 
 int /*<<< orphan*/  DB_VALUE_HOST ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*) ; 
 int /*<<< orphan*/  xhci_readl (struct xhci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhci_writel (struct xhci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void xhci_ring_cmd_db(struct xhci_hcd *xhci)
{
	if (!(xhci->cmd_ring_state & CMD_RING_STATE_RUNNING))
		return;

	xhci_dbg(xhci, "// Ding dong!\n");
	xhci_writel(xhci, DB_VALUE_HOST, &xhci->dba->doorbell[0]);
	/* Flush PCI posted writes */
	xhci_readl(xhci, &xhci->dba->doorbell[0]);
}