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
typedef  int u16 ;
struct bnx2x {int mrrs; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  NETIF_MSG_HW ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL ; 
 int PCI_EXP_DEVCTL_PAYLOAD ; 
 int PCI_EXP_DEVCTL_READRQ ; 
 int /*<<< orphan*/  bnx2x_init_pxp_arb (struct bnx2x*,int,int) ; 
 int /*<<< orphan*/  pcie_capability_read_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void bnx2x_init_pxp(struct bnx2x *bp)
{
	u16 devctl;
	int r_order, w_order;

	pcie_capability_read_word(bp->pdev, PCI_EXP_DEVCTL, &devctl);
	DP(NETIF_MSG_HW, "read 0x%x from devctl\n", devctl);
	w_order = ((devctl & PCI_EXP_DEVCTL_PAYLOAD) >> 5);
	if (bp->mrrs == -1)
		r_order = ((devctl & PCI_EXP_DEVCTL_READRQ) >> 12);
	else {
		DP(NETIF_MSG_HW, "force read order to %d\n", bp->mrrs);
		r_order = bp->mrrs;
	}

	bnx2x_init_pxp_arb(bp, r_order, w_order);
}