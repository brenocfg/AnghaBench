#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  reset_duration; } ;
struct TYPE_4__ {int /*<<< orphan*/  smps; } ;
struct il_priv {int /*<<< orphan*/ * ieee_rates; TYPE_3__* ops; TYPE_2__ force_reset; int /*<<< orphan*/  missed_beacon_threshold; TYPE_1__ current_ht_config; int /*<<< orphan*/  iw_mode; int /*<<< orphan*/  band; int /*<<< orphan*/ * ieee_channels; int /*<<< orphan*/  mutex; int /*<<< orphan*/  free_frames; int /*<<< orphan*/  hcmd_lock; int /*<<< orphan*/  sta_lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_rxon_chain ) (struct il_priv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_BAND_2GHZ ; 
 int /*<<< orphan*/  IEEE80211_SMPS_STATIC ; 
 int /*<<< orphan*/  IL_DELAY_NEXT_FORCE_FW_RELOAD ; 
 int /*<<< orphan*/  IL_ERR (char*,int) ; 
 int /*<<< orphan*/  IL_MISSED_BEACON_THRESHOLD_DEF ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  il4965_init_hw_rates (struct il_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  il_free_channel_map (struct il_priv*) ; 
 int il_init_channel_map (struct il_priv*) ; 
 int il_init_geos (struct il_priv*) ; 
 int /*<<< orphan*/  il_init_scan_params (struct il_priv*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct il_priv*) ; 

__attribute__((used)) static int
il4965_init_drv(struct il_priv *il)
{
	int ret;

	spin_lock_init(&il->sta_lock);
	spin_lock_init(&il->hcmd_lock);

	INIT_LIST_HEAD(&il->free_frames);

	mutex_init(&il->mutex);

	il->ieee_channels = NULL;
	il->ieee_rates = NULL;
	il->band = IEEE80211_BAND_2GHZ;

	il->iw_mode = NL80211_IFTYPE_STATION;
	il->current_ht_config.smps = IEEE80211_SMPS_STATIC;
	il->missed_beacon_threshold = IL_MISSED_BEACON_THRESHOLD_DEF;

	/* initialize force reset */
	il->force_reset.reset_duration = IL_DELAY_NEXT_FORCE_FW_RELOAD;

	/* Choose which receivers/antennas to use */
	if (il->ops->set_rxon_chain)
		il->ops->set_rxon_chain(il);

	il_init_scan_params(il);

	ret = il_init_channel_map(il);
	if (ret) {
		IL_ERR("initializing regulatory failed: %d\n", ret);
		goto err;
	}

	ret = il_init_geos(il);
	if (ret) {
		IL_ERR("initializing geos failed: %d\n", ret);
		goto err_free_channel_map;
	}
	il4965_init_hw_rates(il, il->ieee_rates);

	return 0;

err_free_channel_map:
	il_free_channel_map(il);
err:
	return ret;
}