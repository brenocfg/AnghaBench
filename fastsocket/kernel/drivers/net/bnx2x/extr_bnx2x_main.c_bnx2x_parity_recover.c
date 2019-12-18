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
typedef  void* u32 ;
struct TYPE_2__ {void* unrecoverable_error; void* recoverable_error; } ;
struct bnx2x {int recovery_state; int is_leader; TYPE_1__ eth_stats; int /*<<< orphan*/  dev; int /*<<< orphan*/  sp_rtnl_task; } ;

/* Variables and functions */
 int BNX2X_RECOVERY_DONE ; 
#define  BNX2X_RECOVERY_INIT 129 
 int BNX2X_RECOVERY_NIC_LOADING ; 
#define  BNX2X_RECOVERY_WAIT 128 
 int BP_PATH (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int HZ ; 
 int /*<<< orphan*/  LOAD_NORMAL ; 
 int /*<<< orphan*/  NETIF_MSG_HW ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  UNLOAD_RECOVERY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int bnx2x_chk_parity_attn (struct bnx2x*,int*,int) ; 
 int bnx2x_get_load_status (struct bnx2x*,int) ; 
 int /*<<< orphan*/  bnx2x_leader_reset (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_nic_load (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_nic_unload (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_recovery_failed (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_reset_is_done (struct bnx2x*,int) ; 
 int bnx2x_reset_is_global (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_set_power_state (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_set_reset_global (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_set_reset_in_progress (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_trylock_leader_lock (struct bnx2x*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static void bnx2x_parity_recover(struct bnx2x *bp)
{
	bool global = false;
	u32 error_recovered, error_unrecovered;
	bool is_parity;

	DP(NETIF_MSG_HW, "Handling parity\n");
	while (1) {
		switch (bp->recovery_state) {
		case BNX2X_RECOVERY_INIT:
			DP(NETIF_MSG_HW, "State is BNX2X_RECOVERY_INIT\n");
			is_parity = bnx2x_chk_parity_attn(bp, &global, false);
			WARN_ON(!is_parity);

			/* Try to get a LEADER_LOCK HW lock */
			if (bnx2x_trylock_leader_lock(bp)) {
				bnx2x_set_reset_in_progress(bp);
				/*
				 * Check if there is a global attention and if
				 * there was a global attention, set the global
				 * reset bit.
				 */

				if (global)
					bnx2x_set_reset_global(bp);

				bp->is_leader = 1;
			}

			/* Stop the driver */
			/* If interface has been removed - break */
			if (bnx2x_nic_unload(bp, UNLOAD_RECOVERY, false))
				return;

			bp->recovery_state = BNX2X_RECOVERY_WAIT;

			/* Ensure "is_leader", MCP command sequence and
			 * "recovery_state" update values are seen on other
			 * CPUs.
			 */
			smp_mb();
			break;

		case BNX2X_RECOVERY_WAIT:
			DP(NETIF_MSG_HW, "State is BNX2X_RECOVERY_WAIT\n");
			if (bp->is_leader) {
				int other_engine = BP_PATH(bp) ? 0 : 1;
				bool other_load_status =
					bnx2x_get_load_status(bp, other_engine);
				bool load_status =
					bnx2x_get_load_status(bp, BP_PATH(bp));
				global = bnx2x_reset_is_global(bp);

				/*
				 * In case of a parity in a global block, let
				 * the first leader that performs a
				 * leader_reset() reset the global blocks in
				 * order to clear global attentions. Otherwise
				 * the gates will remain closed for that
				 * engine.
				 */
				if (load_status ||
				    (global && other_load_status)) {
					/* Wait until all other functions get
					 * down.
					 */
					schedule_delayed_work(&bp->sp_rtnl_task,
								HZ/10);
					return;
				} else {
					/* If all other functions got down -
					 * try to bring the chip back to
					 * normal. In any case it's an exit
					 * point for a leader.
					 */
					if (bnx2x_leader_reset(bp)) {
						bnx2x_recovery_failed(bp);
						return;
					}

					/* If we are here, means that the
					 * leader has succeeded and doesn't
					 * want to be a leader any more. Try
					 * to continue as a none-leader.
					 */
					break;
				}
			} else { /* non-leader */
				if (!bnx2x_reset_is_done(bp, BP_PATH(bp))) {
					/* Try to get a LEADER_LOCK HW lock as
					 * long as a former leader may have
					 * been unloaded by the user or
					 * released a leadership by another
					 * reason.
					 */
					if (bnx2x_trylock_leader_lock(bp)) {
						/* I'm a leader now! Restart a
						 * switch case.
						 */
						bp->is_leader = 1;
						break;
					}

					schedule_delayed_work(&bp->sp_rtnl_task,
								HZ/10);
					return;

				} else {
					/*
					 * If there was a global attention, wait
					 * for it to be cleared.
					 */
					if (bnx2x_reset_is_global(bp)) {
						schedule_delayed_work(
							&bp->sp_rtnl_task,
							HZ/10);
						return;
					}

					error_recovered =
					  bp->eth_stats.recoverable_error;
					error_unrecovered =
					  bp->eth_stats.unrecoverable_error;
					bp->recovery_state =
						BNX2X_RECOVERY_NIC_LOADING;
					if (bnx2x_nic_load(bp, LOAD_NORMAL)) {
						error_unrecovered++;
						netdev_err(bp->dev,
							   "Recovery failed. Power cycle needed\n");
						/* Disconnect this device */
						netif_device_detach(bp->dev);
						/* Shut down the power */
						bnx2x_set_power_state(
							bp, PCI_D3hot);
						smp_mb();
					} else {
						bp->recovery_state =
							BNX2X_RECOVERY_DONE;
						error_recovered++;
						smp_mb();
					}
					bp->eth_stats.recoverable_error =
						error_recovered;
					bp->eth_stats.unrecoverable_error =
						error_unrecovered;

					return;
				}
			}
		default:
			return;
		}
	}
}