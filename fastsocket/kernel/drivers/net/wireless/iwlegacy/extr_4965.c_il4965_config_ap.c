#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int flags; int /*<<< orphan*/  filter_flags; scalar_t__ assoc_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  valid_rx_ant; } ;
struct TYPE_6__ {int /*<<< orphan*/  active_chains; } ;
struct il_priv {TYPE_5__ staging; TYPE_3__* ops; int /*<<< orphan*/  current_ht_config; TYPE_2__ hw_params; TYPE_1__ chain_noise_data; int /*<<< orphan*/  status; int /*<<< orphan*/  mutex; struct ieee80211_vif* vif; } ;
struct TYPE_9__ {scalar_t__ use_short_slot; scalar_t__ use_short_preamble; } ;
struct ieee80211_vif {TYPE_4__ bss_conf; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* set_rxon_chain ) (struct il_priv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IL_WARN (char*) ; 
 int /*<<< orphan*/  RXON_FILTER_ASSOC_MSK ; 
 int RXON_FLG_BAND_24G_MSK ; 
 int RXON_FLG_SHORT_PREAMBLE_MSK ; 
 int RXON_FLG_SHORT_SLOT_MSK ; 
 int /*<<< orphan*/  S_EXIT_PENDING ; 
 int /*<<< orphan*/  il4965_send_beacon_cmd (struct il_priv*) ; 
 int /*<<< orphan*/  il_commit_rxon (struct il_priv*) ; 
 int /*<<< orphan*/  il_is_associated (struct il_priv*) ; 
 int il_send_rxon_timing (struct il_priv*) ; 
 int /*<<< orphan*/  il_set_rxon_ht (struct il_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct il_priv*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
il4965_config_ap(struct il_priv *il)
{
	struct ieee80211_vif *vif = il->vif;
	int ret = 0;

	lockdep_assert_held(&il->mutex);

	if (test_bit(S_EXIT_PENDING, &il->status))
		return;

	/* The following should be done only at AP bring up */
	if (!il_is_associated(il)) {

		/* RXON - unassoc (to set timing command) */
		il->staging.filter_flags &= ~RXON_FILTER_ASSOC_MSK;
		il_commit_rxon(il);

		/* RXON Timing */
		ret = il_send_rxon_timing(il);
		if (ret)
			IL_WARN("RXON timing failed - "
				"Attempting to continue.\n");

		/* AP has all antennas */
		il->chain_noise_data.active_chains = il->hw_params.valid_rx_ant;
		il_set_rxon_ht(il, &il->current_ht_config);
		if (il->ops->set_rxon_chain)
			il->ops->set_rxon_chain(il);

		il->staging.assoc_id = 0;

		if (vif->bss_conf.use_short_preamble)
			il->staging.flags |= RXON_FLG_SHORT_PREAMBLE_MSK;
		else
			il->staging.flags &= ~RXON_FLG_SHORT_PREAMBLE_MSK;

		if (il->staging.flags & RXON_FLG_BAND_24G_MSK) {
			if (vif->bss_conf.use_short_slot)
				il->staging.flags |= RXON_FLG_SHORT_SLOT_MSK;
			else
				il->staging.flags &= ~RXON_FLG_SHORT_SLOT_MSK;
		}
		/* need to send beacon cmd before committing assoc RXON! */
		il4965_send_beacon_cmd(il);
		/* restore RXON assoc */
		il->staging.filter_flags |= RXON_FILTER_ASSOC_MSK;
		il_commit_rxon(il);
	}
	il4965_send_beacon_cmd(il);
}