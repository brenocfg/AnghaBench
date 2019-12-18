#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ pmf; } ;
struct TYPE_3__ {int aeu_int_mask; } ;
struct bnx2x {int /*<<< orphan*/  link_params; TYPE_2__ port; TYPE_1__ link_vars; } ;

/* Variables and functions */
 int AEU_INPUTS_ATTN_BITS_SPIO5 ; 
 int /*<<< orphan*/  BNX2X_ERR (char*,...) ; 
 int BP_PORT (struct bnx2x*) ; 
 int HW_INTERRUT_ASSERT_SET_0 ; 
 int MISC_REG_AEU_ENABLE1_FUNC_0_OUT_0 ; 
 int MISC_REG_AEU_ENABLE1_FUNC_1_OUT_0 ; 
 int REG_RD (struct bnx2x*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int,int) ; 
 int /*<<< orphan*/  bnx2x_acquire_phy_lock (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_fan_failure (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_handle_module_detect_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2x_hw_reset_phy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2x_panic () ; 
 int /*<<< orphan*/  bnx2x_release_phy_lock (struct bnx2x*) ; 

__attribute__((used)) static void bnx2x_attn_int_deasserted0(struct bnx2x *bp, u32 attn)
{
	int port = BP_PORT(bp);
	int reg_offset;
	u32 val;

	reg_offset = (port ? MISC_REG_AEU_ENABLE1_FUNC_1_OUT_0 :
			     MISC_REG_AEU_ENABLE1_FUNC_0_OUT_0);

	if (attn & AEU_INPUTS_ATTN_BITS_SPIO5) {

		val = REG_RD(bp, reg_offset);
		val &= ~AEU_INPUTS_ATTN_BITS_SPIO5;
		REG_WR(bp, reg_offset, val);

		BNX2X_ERR("SPIO5 hw attention\n");

		/* Fan failure attention */
		bnx2x_hw_reset_phy(&bp->link_params);
		bnx2x_fan_failure(bp);
	}

	if ((attn & bp->link_vars.aeu_int_mask) && bp->port.pmf) {
		bnx2x_acquire_phy_lock(bp);
		bnx2x_handle_module_detect_int(&bp->link_params);
		bnx2x_release_phy_lock(bp);
	}

	if (attn & HW_INTERRUT_ASSERT_SET_0) {

		val = REG_RD(bp, reg_offset);
		val &= ~(attn & HW_INTERRUT_ASSERT_SET_0);
		REG_WR(bp, reg_offset, val);

		BNX2X_ERR("FATAL HW block attention set0 0x%x\n",
			  (u32)(attn & HW_INTERRUT_ASSERT_SET_0));
		bnx2x_panic();
	}
}