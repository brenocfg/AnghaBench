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
typedef  int /*<<< orphan*/  u64 ;
struct xhci_hcd {TYPE_1__* op_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_read_64 (struct xhci_hcd*,int /*<<< orphan*/ *) ; 

void xhci_dbg_cmd_ptrs(struct xhci_hcd *xhci)
{
	u64 val;

	val = xhci_read_64(xhci, &xhci->op_regs->cmd_ring);
	xhci_dbg(xhci, "// xHC command ring deq ptr low bits + flags = @%08x\n",
			lower_32_bits(val));
	xhci_dbg(xhci, "// xHC command ring deq ptr high bits = @%08x\n",
			upper_32_bits(val));
}