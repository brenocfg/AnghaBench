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
typedef  int u32 ;
struct bnx2x {int pf_num; } ;

/* Variables and functions */
 int BNX2X_PATH0_LOAD_CNT_MASK ; 
 int BNX2X_PATH0_LOAD_CNT_SHIFT ; 
 int BNX2X_PATH1_LOAD_CNT_MASK ; 
 int BNX2X_PATH1_LOAD_CNT_SHIFT ; 
 int /*<<< orphan*/  BNX2X_RECOVERY_GLOB_REG ; 
 scalar_t__ BP_PATH (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  HW_LOCK_RESOURCE_RECOVERY_REG ; 
 int /*<<< orphan*/  NETIF_MSG_IFDOWN ; 
 int REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_acquire_hw_lock (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_release_hw_lock (struct bnx2x*,int /*<<< orphan*/ ) ; 

bool bnx2x_clear_pf_load(struct bnx2x *bp)
{
	u32 val1, val;
	u32 mask = BP_PATH(bp) ? BNX2X_PATH1_LOAD_CNT_MASK :
			     BNX2X_PATH0_LOAD_CNT_MASK;
	u32 shift = BP_PATH(bp) ? BNX2X_PATH1_LOAD_CNT_SHIFT :
			     BNX2X_PATH0_LOAD_CNT_SHIFT;

	bnx2x_acquire_hw_lock(bp, HW_LOCK_RESOURCE_RECOVERY_REG);
	val = REG_RD(bp, BNX2X_RECOVERY_GLOB_REG);
	DP(NETIF_MSG_IFDOWN, "Old GEN_REG_VAL=0x%08x\n", val);

	/* get the current counter value */
	val1 = (val & mask) >> shift;

	/* clear bit of that PF */
	val1 &= ~(1 << bp->pf_num);

	/* clear the old value */
	val &= ~mask;

	/* set the new one */
	val |= ((val1 << shift) & mask);

	REG_WR(bp, BNX2X_RECOVERY_GLOB_REG, val);
	bnx2x_release_hw_lock(bp, HW_LOCK_RESOURCE_RECOVERY_REG);
	return val1 != 0;
}