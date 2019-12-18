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
typedef  int u32 ;
struct bnx2x {int fw_drv_pulse_wr_seq; scalar_t__ state; scalar_t__ current_interval; int /*<<< orphan*/  timer; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  mcp_pulse_mb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int,int) ; 
 scalar_t__ BNX2X_STATE_OPEN ; 
 int BP_FW_MB_IDX (struct bnx2x*) ; 
 int /*<<< orphan*/  BP_NOMCP (struct bnx2x*) ; 
 int DRV_PULSE_SEQ_MASK ; 
 scalar_t__ IS_PF (struct bnx2x*) ; 
 scalar_t__ IS_VF (struct bnx2x*) ; 
 int MCP_PULSE_SEQ_MASK ; 
 int SHMEM_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATS_EVENT_UPDATE ; 
 int /*<<< orphan*/  bnx2x_drv_pulse (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_stats_handle (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_timer_sriov (struct bnx2x*) ; 
 TYPE_1__* func_mb ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_timer(unsigned long data)
{
	struct bnx2x *bp = (struct bnx2x *) data;

	if (!netif_running(bp->dev))
		return;

	if (IS_PF(bp) &&
	    !BP_NOMCP(bp)) {
		int mb_idx = BP_FW_MB_IDX(bp);
		u32 drv_pulse;
		u32 mcp_pulse;

		++bp->fw_drv_pulse_wr_seq;
		bp->fw_drv_pulse_wr_seq &= DRV_PULSE_SEQ_MASK;
		/* TBD - add SYSTEM_TIME */
		drv_pulse = bp->fw_drv_pulse_wr_seq;
		bnx2x_drv_pulse(bp);

		mcp_pulse = (SHMEM_RD(bp, func_mb[mb_idx].mcp_pulse_mb) &
			     MCP_PULSE_SEQ_MASK);
		/* The delta between driver pulse and mcp response
		 * should be 1 (before mcp response) or 0 (after mcp response)
		 */
		if ((drv_pulse != mcp_pulse) &&
		    (drv_pulse != ((mcp_pulse + 1) & MCP_PULSE_SEQ_MASK))) {
			/* someone lost a heartbeat... */
			BNX2X_ERR("drv_pulse (0x%x) != mcp_pulse (0x%x)\n",
				  drv_pulse, mcp_pulse);
		}
	}

	if (bp->state == BNX2X_STATE_OPEN)
		bnx2x_stats_handle(bp, STATS_EVENT_UPDATE);

	/* sample pf vf bulletin board for new posts from pf */
	if (IS_VF(bp))
		bnx2x_timer_sriov(bp);

	mod_timer(&bp->timer, jiffies + bp->current_interval);
}