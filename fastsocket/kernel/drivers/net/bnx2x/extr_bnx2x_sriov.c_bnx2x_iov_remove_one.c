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
struct bnx2x {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IS_SRIOV (struct bnx2x*) ; 
 int /*<<< orphan*/  __bnx2x_iov_free_vfdb (struct bnx2x*) ; 
 int /*<<< orphan*/  pci_disable_sriov (int /*<<< orphan*/ ) ; 

void bnx2x_iov_remove_one(struct bnx2x *bp)
{
	/* if SRIOV is not enabled there's nothing to do */
	if (!IS_SRIOV(bp))
		return;

	DP(BNX2X_MSG_IOV, "about to call disable sriov\n");
	pci_disable_sriov(bp->pdev);
	DP(BNX2X_MSG_IOV, "sriov disabled\n");

	/* free vf database */
	__bnx2x_iov_free_vfdb(bp);
}