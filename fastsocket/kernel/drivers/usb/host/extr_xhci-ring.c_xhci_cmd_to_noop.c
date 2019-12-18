#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__* field; } ;
union xhci_trb {TYPE_1__ generic; } ;
typedef  int u32 ;
struct xhci_segment {int dummy; } ;
struct xhci_hcd {TYPE_2__* cmd_ring; } ;
struct xhci_cd {scalar_t__ command; union xhci_trb* cmd_trb; } ;
struct TYPE_6__ {union xhci_trb* enqueue; union xhci_trb* dequeue; int /*<<< orphan*/  deq_seg; int /*<<< orphan*/  first_seg; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_CMD_STOP ; 
 int /*<<< orphan*/  TRB_CMD_NOOP ; 
 int TRB_CYCLE ; 
 int TRB_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TRB_TYPE_LINK_LE32 (scalar_t__) ; 
 scalar_t__ cpu_to_le32 (int) ; 
 struct xhci_segment* find_trb_seg (int /*<<< orphan*/ ,union xhci_trb*,int*) ; 
 int le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  next_trb (struct xhci_hcd*,TYPE_2__*,struct xhci_segment**,union xhci_trb**) ; 
 int /*<<< orphan*/  xhci_complete_cmd_in_cmd_wait_list (struct xhci_hcd*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_dbg_ring_ptrs (struct xhci_hcd*,TYPE_2__*) ; 
 int /*<<< orphan*/  xhci_debug_ring (struct xhci_hcd*,TYPE_2__*) ; 
 scalar_t__ xhci_trb_virt_to_dma (int /*<<< orphan*/ ,union xhci_trb*) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*,union xhci_trb*,unsigned long long) ; 

__attribute__((used)) static void xhci_cmd_to_noop(struct xhci_hcd *xhci, struct xhci_cd *cur_cd)
{
	struct xhci_segment *cur_seg;
	union xhci_trb *cmd_trb;
	u32 cycle_state;

	if (xhci->cmd_ring->dequeue == xhci->cmd_ring->enqueue)
		return;

	/* find the current segment of command ring */
	cur_seg = find_trb_seg(xhci->cmd_ring->first_seg,
			xhci->cmd_ring->dequeue, &cycle_state);

	if (!cur_seg) {
		xhci_warn(xhci, "Command ring mismatch, dequeue = %p %llx (dma)\n",
				xhci->cmd_ring->dequeue,
				(unsigned long long)
				xhci_trb_virt_to_dma(xhci->cmd_ring->deq_seg,
					xhci->cmd_ring->dequeue));
		xhci_debug_ring(xhci, xhci->cmd_ring);
		xhci_dbg_ring_ptrs(xhci, xhci->cmd_ring);
		return;
	}

	/* find the command trb matched by cd from command ring */
	for (cmd_trb = xhci->cmd_ring->dequeue;
			cmd_trb != xhci->cmd_ring->enqueue;
			next_trb(xhci, xhci->cmd_ring, &cur_seg, &cmd_trb)) {
		/* If the trb is link trb, continue */
		if (TRB_TYPE_LINK_LE32(cmd_trb->generic.field[3]))
			continue;

		if (cur_cd->cmd_trb == cmd_trb) {

			/* If the command in device's command list, we should
			 * finish it and free the command structure.
			 */
			if (cur_cd->command)
				xhci_complete_cmd_in_cmd_wait_list(xhci,
					cur_cd->command, COMP_CMD_STOP);

			/* get cycle state from the origin command trb */
			cycle_state = le32_to_cpu(cmd_trb->generic.field[3])
				& TRB_CYCLE;

			/* modify the command trb to NO OP command */
			cmd_trb->generic.field[0] = 0;
			cmd_trb->generic.field[1] = 0;
			cmd_trb->generic.field[2] = 0;
			cmd_trb->generic.field[3] = cpu_to_le32(
					TRB_TYPE(TRB_CMD_NOOP) | cycle_state);
			break;
		}
	}
}