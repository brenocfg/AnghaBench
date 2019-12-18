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
typedef  int /*<<< orphan*/  u8 ;
struct iwl_nvm_data {struct ieee80211_supported_band* bands; } ;
struct iwl_cfg {int dummy; } ;
struct ieee80211_supported_band {size_t band; int /*<<< orphan*/  ht_cap; int /*<<< orphan*/  n_bitrates; int /*<<< orphan*/ * bitrates; } ;
struct device {int dummy; } ;

/* Variables and functions */
 size_t IEEE80211_BAND_2GHZ ; 
 size_t IEEE80211_BAND_5GHZ ; 
 int /*<<< orphan*/  IWL_ERR_DEV (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  N_RATES_24 ; 
 int /*<<< orphan*/  N_RATES_52 ; 
 size_t RATES_24_OFFS ; 
 size_t RATES_52_OFFS ; 
 int /*<<< orphan*/ * iwl_cfg80211_rates ; 
 int iwl_init_channel_map (struct device*,struct iwl_cfg const*,struct iwl_nvm_data*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  iwl_init_ht_hw_capab (struct iwl_cfg const*,struct iwl_nvm_data*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ iwl_init_sband_channels (struct iwl_nvm_data*,struct ieee80211_supported_band*,int,size_t) ; 

__attribute__((used)) static void iwl_init_sbands(struct device *dev, const struct iwl_cfg *cfg,
			    struct iwl_nvm_data *data,
			    const u8 *eeprom, size_t eeprom_size)
{
	int n_channels = iwl_init_channel_map(dev, cfg, data,
					      eeprom, eeprom_size);
	int n_used = 0;
	struct ieee80211_supported_band *sband;

	sband = &data->bands[IEEE80211_BAND_2GHZ];
	sband->band = IEEE80211_BAND_2GHZ;
	sband->bitrates = &iwl_cfg80211_rates[RATES_24_OFFS];
	sband->n_bitrates = N_RATES_24;
	n_used += iwl_init_sband_channels(data, sband, n_channels,
					  IEEE80211_BAND_2GHZ);
	iwl_init_ht_hw_capab(cfg, data, &sband->ht_cap, IEEE80211_BAND_2GHZ);

	sband = &data->bands[IEEE80211_BAND_5GHZ];
	sband->band = IEEE80211_BAND_5GHZ;
	sband->bitrates = &iwl_cfg80211_rates[RATES_52_OFFS];
	sband->n_bitrates = N_RATES_52;
	n_used += iwl_init_sband_channels(data, sband, n_channels,
					  IEEE80211_BAND_5GHZ);
	iwl_init_ht_hw_capab(cfg, data, &sband->ht_cap, IEEE80211_BAND_5GHZ);

	if (n_channels != n_used)
		IWL_ERR_DEV(dev, "EEPROM: used only %d of %d channels\n",
			    n_used, n_channels);
}