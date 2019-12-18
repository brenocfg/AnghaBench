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
struct bnx2x {int /*<<< orphan*/  cnic_sb_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_VF_ID_INVALID ; 
 int /*<<< orphan*/  NO_FCOE (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_cnic_fw_sb_id (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_cnic_igu_sb_id (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_init_fcoe_fp (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_init_rx_rings_cnic (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_init_sb (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_init_tx_rings_cnic (struct bnx2x*) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  rmb () ; 

void bnx2x_nic_init_cnic(struct bnx2x *bp)
{
	if (!NO_FCOE(bp))
		bnx2x_init_fcoe_fp(bp);

	bnx2x_init_sb(bp, bp->cnic_sb_mapping,
		      BNX2X_VF_ID_INVALID, false,
		      bnx2x_cnic_fw_sb_id(bp), bnx2x_cnic_igu_sb_id(bp));

	/* ensure status block indices were read */
	rmb();
	bnx2x_init_rx_rings_cnic(bp);
	bnx2x_init_tx_rings_cnic(bp);

	/* flush all */
	mb();
	mmiowb();
}