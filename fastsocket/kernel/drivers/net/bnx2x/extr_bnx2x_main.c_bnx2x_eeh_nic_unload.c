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
struct bnx2x {int /*<<< orphan*/  dev; int /*<<< orphan*/  stats_lock; int /*<<< orphan*/  stats_state; int /*<<< orphan*/  period_task; int /*<<< orphan*/  sp_task; int /*<<< orphan*/  timer; int /*<<< orphan*/  rx_mode; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_RX_MODE_NONE ; 
 int /*<<< orphan*/  BNX2X_STATE_CLOSING_WAIT4_HALT ; 
 int /*<<< orphan*/  CNIC_CTL_STOP_CMD ; 
 scalar_t__ CNIC_LOADED (struct bnx2x*) ; 
 int /*<<< orphan*/  STATS_STATE_DISABLED ; 
 int /*<<< orphan*/  bnx2x_cnic_notify (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_del_all_napi (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_del_all_napi_cnic (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_save_statistics (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_tx_disable (struct bnx2x*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_reset_tc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2x_eeh_nic_unload(struct bnx2x *bp)
{
	bp->state = BNX2X_STATE_CLOSING_WAIT4_HALT;

	bp->rx_mode = BNX2X_RX_MODE_NONE;

	if (CNIC_LOADED(bp))
		bnx2x_cnic_notify(bp, CNIC_CTL_STOP_CMD);

	/* Stop Tx */
	bnx2x_tx_disable(bp);
	/* Delete all NAPI objects */
	bnx2x_del_all_napi(bp);
	if (CNIC_LOADED(bp))
		bnx2x_del_all_napi_cnic(bp);
	netdev_reset_tc(bp->dev);

	del_timer_sync(&bp->timer);
	cancel_delayed_work(&bp->sp_task);
	cancel_delayed_work(&bp->period_task);

	spin_lock_bh(&bp->stats_lock);
	bp->stats_state = STATS_STATE_DISABLED;
	spin_unlock_bh(&bp->stats_lock);

	bnx2x_save_statistics(bp);

	netif_carrier_off(bp->dev);

	return 0;
}