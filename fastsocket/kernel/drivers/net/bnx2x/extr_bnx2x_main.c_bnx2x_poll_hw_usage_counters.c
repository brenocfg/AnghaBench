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
typedef  int /*<<< orphan*/  u32 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BP_FUNC (struct bnx2x*) ; 
 int BP_PORT (struct bnx2x*) ; 
 scalar_t__ CFC_REG_NUM_LCIDS_INSIDE_PF ; 
 scalar_t__ DORQ_REG_PF_USAGE_CNT ; 
 size_t INIT_DMAE_C (struct bnx2x*) ; 
 scalar_t__ QM_REG_PF_USG_CNT_0 ; 
 scalar_t__ TM_REG_LIN0_NUM_SCANS ; 
 scalar_t__ TM_REG_LIN0_VNIC_UC ; 
 scalar_t__ bnx2x_flr_clnup_poll_hw_counter (struct bnx2x*,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 scalar_t__* dmae_reg_go_c ; 

__attribute__((used)) static int bnx2x_poll_hw_usage_counters(struct bnx2x *bp, u32 poll_cnt)
{
	/* wait for CFC PF usage-counter to zero (includes all the VFs) */
	if (bnx2x_flr_clnup_poll_hw_counter(bp,
			CFC_REG_NUM_LCIDS_INSIDE_PF,
			"CFC PF usage counter timed out",
			poll_cnt))
		return 1;

	/* Wait for DQ PF usage-counter to zero (until DQ cleanup) */
	if (bnx2x_flr_clnup_poll_hw_counter(bp,
			DORQ_REG_PF_USAGE_CNT,
			"DQ PF usage counter timed out",
			poll_cnt))
		return 1;

	/* Wait for QM PF usage-counter to zero (until DQ cleanup) */
	if (bnx2x_flr_clnup_poll_hw_counter(bp,
			QM_REG_PF_USG_CNT_0 + 4*BP_FUNC(bp),
			"QM PF usage counter timed out",
			poll_cnt))
		return 1;

	/* Wait for Timer PF usage-counters to zero (until DQ cleanup) */
	if (bnx2x_flr_clnup_poll_hw_counter(bp,
			TM_REG_LIN0_VNIC_UC + 4*BP_PORT(bp),
			"Timers VNIC usage counter timed out",
			poll_cnt))
		return 1;
	if (bnx2x_flr_clnup_poll_hw_counter(bp,
			TM_REG_LIN0_NUM_SCANS + 4*BP_PORT(bp),
			"Timers NUM_SCANS usage counter timed out",
			poll_cnt))
		return 1;

	/* Wait DMAE PF usage counter to zero */
	if (bnx2x_flr_clnup_poll_hw_counter(bp,
			dmae_reg_go_c[INIT_DMAE_C(bp)],
			"DMAE command register timed out",
			poll_cnt))
		return 1;

	return 0;
}