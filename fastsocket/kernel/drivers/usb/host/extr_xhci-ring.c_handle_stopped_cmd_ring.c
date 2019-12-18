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
struct xhci_hcd {TYPE_1__* cmd_ring; int /*<<< orphan*/  cmd_ring_state; } ;
struct TYPE_2__ {scalar_t__ dequeue; scalar_t__ enqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RING_STATE_RUNNING ; 
 int /*<<< orphan*/  CMD_RING_STATE_STOPPED ; 
 int COMP_CMD_ABORT ; 
 int COMP_CMD_STOP ; 
 int /*<<< orphan*/  xhci_cancel_cmd_in_cd_list (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_ring_cmd_db (struct xhci_hcd*) ; 
 int xhci_search_cmd_trb_in_cd_list (struct xhci_hcd*,scalar_t__) ; 

__attribute__((used)) static int handle_stopped_cmd_ring(struct xhci_hcd *xhci,
		int cmd_trb_comp_code)
{
	int cur_trb_is_good = 0;

	/* Searching the cmd trb pointed by the command ring dequeue
	 * pointer in command descriptor list. If it is found, free it.
	 */
	cur_trb_is_good = xhci_search_cmd_trb_in_cd_list(xhci,
			xhci->cmd_ring->dequeue);

	if (cmd_trb_comp_code == COMP_CMD_ABORT)
		xhci->cmd_ring_state = CMD_RING_STATE_STOPPED;
	else if (cmd_trb_comp_code == COMP_CMD_STOP) {
		/* traversing the cancel_cmd_list and canceling
		 * the command according to command descriptor
		 */
		xhci_cancel_cmd_in_cd_list(xhci);

		xhci->cmd_ring_state = CMD_RING_STATE_RUNNING;
		/*
		 * ring command ring doorbell again to restart the
		 * command ring
		 */
		if (xhci->cmd_ring->dequeue != xhci->cmd_ring->enqueue)
			xhci_ring_cmd_db(xhci);
	}
	return cur_trb_is_good;
}