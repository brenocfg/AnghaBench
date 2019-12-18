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
typedef  scalar_t__ u32 ;
struct bnx2x_eth_stats {int /*<<< orphan*/  brb_truncate_lo; int /*<<< orphan*/  brb_drop_lo; } ;
struct TYPE_2__ {scalar_t__ pmf; } ;
struct bnx2x {int /*<<< orphan*/  stats_sema; int /*<<< orphan*/  dev; struct bnx2x_eth_stats eth_stats; int /*<<< orphan*/  stats_pending; TYPE_1__ port; int /*<<< orphan*/  stats_started; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 scalar_t__ DMAE_COMP_VAL ; 
 scalar_t__ IS_PF (struct bnx2x*) ; 
 scalar_t__ IS_VF (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_drv_stats_update (struct bnx2x*) ; 
 scalar_t__ bnx2x_edebug_stats_stopped (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_hw_stats_post (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_hw_stats_update (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_net_stats_update (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_panic () ; 
 scalar_t__* bnx2x_sp (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_storm_stats_post (struct bnx2x*) ; 
 scalar_t__ bnx2x_storm_stats_update (struct bnx2x*) ; 
 scalar_t__ down_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_msg_timer (struct bnx2x*) ; 
 scalar_t__* stats_comp ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnx2x_stats_update(struct bnx2x *bp)
{
	u32 *stats_comp = bnx2x_sp(bp, stats_comp);

	/* we run update from timer context, so give up
	 * if somebody is in the middle of transition
	 */
	if (down_trylock(&bp->stats_sema))
		return;

	if (bnx2x_edebug_stats_stopped(bp) || !bp->stats_started)
		goto out;

	if (IS_PF(bp)) {
		if (*stats_comp != DMAE_COMP_VAL)
			goto out;

		if (bp->port.pmf)
			bnx2x_hw_stats_update(bp);

		if (bnx2x_storm_stats_update(bp)) {
			if (bp->stats_pending++ == 3) {
				BNX2X_ERR("storm stats were not updated for 3 times\n");
				bnx2x_panic();
			}
			goto out;
		}
	} else {
		/* vf doesn't collect HW statistics, and doesn't get completions
		 * perform only update
		 */
		bnx2x_storm_stats_update(bp);
	}

	bnx2x_net_stats_update(bp);
	bnx2x_drv_stats_update(bp);

	/* vf is done */
	if (IS_VF(bp))
		goto out;

	if (netif_msg_timer(bp)) {
		struct bnx2x_eth_stats *estats = &bp->eth_stats;

		netdev_dbg(bp->dev, "brb drops %u  brb truncate %u\n",
		       estats->brb_drop_lo, estats->brb_truncate_lo);
	}

	bnx2x_hw_stats_post(bp);
	bnx2x_storm_stats_post(bp);

out:
	up(&bp->stats_sema);
}