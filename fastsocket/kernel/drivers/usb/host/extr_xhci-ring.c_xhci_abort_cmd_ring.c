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
typedef  int u64 ;
struct xhci_hcd {int cmd_ring_state; int /*<<< orphan*/  xhc_state; TYPE_1__* op_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_ring; } ;

/* Variables and functions */
 int CMD_RING_ABORT ; 
 int CMD_RING_RUNNING ; 
 int CMD_RING_STATE_ABORTED ; 
 int CMD_RING_STATE_RUNNING ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  XHCI_STATE_DYING ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*) ; 
 int /*<<< orphan*/  xhci_err (struct xhci_hcd*,char*) ; 
 int /*<<< orphan*/  xhci_halt (struct xhci_hcd*) ; 
 int xhci_handshake (struct xhci_hcd*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xhci_quiesce (struct xhci_hcd*) ; 
 int xhci_read_64 (struct xhci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhci_write_64 (struct xhci_hcd*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xhci_abort_cmd_ring(struct xhci_hcd *xhci)
{
	u64 temp_64;
	int ret;

	xhci_dbg(xhci, "Abort command ring\n");

	if (!(xhci->cmd_ring_state & CMD_RING_STATE_RUNNING)) {
		xhci_dbg(xhci, "The command ring isn't running, "
				"Have the command ring been stopped?\n");
		return 0;
	}

	temp_64 = xhci_read_64(xhci, &xhci->op_regs->cmd_ring);
	if (!(temp_64 & CMD_RING_RUNNING)) {
		xhci_dbg(xhci, "Command ring had been stopped\n");
		return 0;
	}
	xhci->cmd_ring_state = CMD_RING_STATE_ABORTED;
	xhci_write_64(xhci, temp_64 | CMD_RING_ABORT,
			&xhci->op_regs->cmd_ring);

	/* Section 4.6.1.2 of xHCI 1.0 spec says software should
	 * time the completion od all xHCI commands, including
	 * the Command Abort operation. If software doesn't see
	 * CRR negated in a timely manner (e.g. longer than 5
	 * seconds), then it should assume that the there are
	 * larger problems with the xHC and assert HCRST.
	 */
	ret = xhci_handshake(xhci, &xhci->op_regs->cmd_ring,
			CMD_RING_RUNNING, 0, 5 * 1000 * 1000);
	if (ret < 0) {
		xhci_err(xhci, "Stopped the command ring failed, "
				"maybe the host is dead\n");
		xhci->xhc_state |= XHCI_STATE_DYING;
		xhci_quiesce(xhci);
		xhci_halt(xhci);
		return -ESHUTDOWN;
	}

	return 0;
}