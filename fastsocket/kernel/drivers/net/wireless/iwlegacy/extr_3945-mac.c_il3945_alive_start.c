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
struct TYPE_4__ {int /*<<< orphan*/  filter_flags; } ;
struct TYPE_3__ {scalar_t__ is_valid; } ;
struct il_priv {int /*<<< orphan*/  restart; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  wait_command_queue; int /*<<< orphan*/  status; TYPE_2__ staging; int /*<<< orphan*/  active; int /*<<< orphan*/  active_rate; int /*<<< orphan*/  hw; TYPE_1__ card_alive; } ;
struct il3945_rxon_cmd {int /*<<< orphan*/  filter_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  APMG_RFKILL_REG ; 
 int /*<<< orphan*/  D_INFO (char*,...) ; 
 int /*<<< orphan*/  RATES_MASK_3945 ; 
 int /*<<< orphan*/  RXON_FILTER_ASSOC_MSK ; 
 int /*<<< orphan*/  S_ALIVE ; 
 int /*<<< orphan*/  S_READY ; 
 int /*<<< orphan*/  S_RFKILL ; 
 scalar_t__ UCODE_VALID_OK ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_wake_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il3945_commit_rxon (struct il_priv*) ; 
 scalar_t__ il3945_hw_get_temperature (struct il_priv*) ; 
 int /*<<< orphan*/  il3945_reg_txpower_periodic (struct il_priv*) ; 
 scalar_t__ il3945_verify_ucode (struct il_priv*) ; 
 int /*<<< orphan*/  il_connection_init_rx_config (struct il_priv*) ; 
 scalar_t__ il_is_associated (struct il_priv*) ; 
 scalar_t__ il_is_rfkill (struct il_priv*) ; 
 int /*<<< orphan*/  il_power_update_mode (struct il_priv*,int) ; 
 int il_rd_prph (struct il_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il_send_bt_config (struct il_priv*) ; 
 int /*<<< orphan*/  il_setup_watchdog (struct il_priv*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
il3945_alive_start(struct il_priv *il)
{
	int thermal_spin = 0;
	u32 rfkill;

	D_INFO("Runtime Alive received.\n");

	if (il->card_alive.is_valid != UCODE_VALID_OK) {
		/* We had an error bringing up the hardware, so take it
		 * all the way back down so we can try again */
		D_INFO("Alive failed.\n");
		goto restart;
	}

	/* Initialize uCode has loaded Runtime uCode ... verify inst image.
	 * This is a paranoid check, because we would not have gotten the
	 * "runtime" alive if code weren't properly loaded.  */
	if (il3945_verify_ucode(il)) {
		/* Runtime instruction load was bad;
		 * take it all the way back down so we can try again */
		D_INFO("Bad runtime uCode load.\n");
		goto restart;
	}

	rfkill = il_rd_prph(il, APMG_RFKILL_REG);
	D_INFO("RFKILL status: 0x%x\n", rfkill);

	if (rfkill & 0x1) {
		clear_bit(S_RFKILL, &il->status);
		/* if RFKILL is not on, then wait for thermal
		 * sensor in adapter to kick in */
		while (il3945_hw_get_temperature(il) == 0) {
			thermal_spin++;
			udelay(10);
		}

		if (thermal_spin)
			D_INFO("Thermal calibration took %dus\n",
			       thermal_spin * 10);
	} else
		set_bit(S_RFKILL, &il->status);

	/* After the ALIVE response, we can send commands to 3945 uCode */
	set_bit(S_ALIVE, &il->status);

	/* Enable watchdog to monitor the driver tx queues */
	il_setup_watchdog(il);

	if (il_is_rfkill(il))
		return;

	ieee80211_wake_queues(il->hw);

	il->active_rate = RATES_MASK_3945;

	il_power_update_mode(il, true);

	if (il_is_associated(il)) {
		struct il3945_rxon_cmd *active_rxon =
		    (struct il3945_rxon_cmd *)(&il->active);

		il->staging.filter_flags |= RXON_FILTER_ASSOC_MSK;
		active_rxon->filter_flags &= ~RXON_FILTER_ASSOC_MSK;
	} else {
		/* Initialize our rx_config data */
		il_connection_init_rx_config(il);
	}

	/* Configure Bluetooth device coexistence support */
	il_send_bt_config(il);

	set_bit(S_READY, &il->status);

	/* Configure the adapter for unassociated operation */
	il3945_commit_rxon(il);

	il3945_reg_txpower_periodic(il);

	D_INFO("ALIVE processing complete.\n");
	wake_up(&il->wait_command_queue);

	return;

restart:
	queue_work(il->workqueue, &il->restart);
}