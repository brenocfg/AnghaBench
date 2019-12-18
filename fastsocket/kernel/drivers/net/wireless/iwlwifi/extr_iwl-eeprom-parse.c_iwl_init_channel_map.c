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
typedef  scalar_t__ u8 ;
struct iwl_nvm_data {int max_tx_pwr_half_dbm; struct ieee80211_channel* channels; } ;
struct iwl_eeprom_channel {int flags; int max_power_avg; } ;
struct iwl_cfg {TYPE_1__* eeprom_params; } ;
struct ieee80211_channel {int max_power; scalar_t__ hw_value; int /*<<< orphan*/  flags; void* band; int /*<<< orphan*/  center_freq; } ;
struct device {int dummy; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;
struct TYPE_2__ {scalar_t__* regulatory_bands; scalar_t__ enhanced_txpower; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIVE ; 
 int /*<<< orphan*/  CHECK_AND_PRINT_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DFS ; 
 int EEPROM_CHANNEL_ACTIVE ; 
 int EEPROM_CHANNEL_IBSS ; 
 int EEPROM_CHANNEL_RADAR ; 
 int EEPROM_CHANNEL_VALID ; 
 scalar_t__ EEPROM_REGULATORY_BAND_NO_HT40 ; 
 int /*<<< orphan*/  IBSS ; 
 void* IEEE80211_BAND_2GHZ ; 
 void* IEEE80211_BAND_5GHZ ; 
 int /*<<< orphan*/  IEEE80211_CHAN_NO_HT40 ; 
 int /*<<< orphan*/  IEEE80211_CHAN_NO_HT40MINUS ; 
 int /*<<< orphan*/  IEEE80211_CHAN_NO_HT40PLUS ; 
 int /*<<< orphan*/  IEEE80211_CHAN_NO_IBSS ; 
 int /*<<< orphan*/  IEEE80211_CHAN_PASSIVE_SCAN ; 
 int /*<<< orphan*/  IEEE80211_CHAN_RADAR ; 
 int /*<<< orphan*/  IWL_DEBUG_EEPROM (struct device*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  RADAR ; 
 int /*<<< orphan*/  VALID ; 
 int /*<<< orphan*/  WIDE ; 
 int /*<<< orphan*/  ieee80211_channel_to_frequency (scalar_t__,void*) ; 
 int /*<<< orphan*/  iwl_eeprom_enhanced_txpower (struct device*,struct iwl_nvm_data*,scalar_t__ const*,size_t,int) ; 
 int /*<<< orphan*/  iwl_init_band_reference (struct iwl_cfg const*,scalar_t__ const*,size_t,int,int*,struct iwl_eeprom_channel const**,scalar_t__ const**) ; 
 int /*<<< orphan*/  iwl_mod_ht40_chan_info (struct device*,struct iwl_nvm_data*,int,int,scalar_t__ const,struct iwl_eeprom_channel const*,int /*<<< orphan*/ ) ; 
 int max_t (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  s8 ; 

__attribute__((used)) static int iwl_init_channel_map(struct device *dev, const struct iwl_cfg *cfg,
				struct iwl_nvm_data *data,
				const u8 *eeprom, size_t eeprom_size)
{
	int band, ch_idx;
	const struct iwl_eeprom_channel *eeprom_ch_info;
	const u8 *eeprom_ch_array;
	int eeprom_ch_count;
	int n_channels = 0;

	/*
	 * Loop through the 5 EEPROM bands and add them to the parse list
	 */
	for (band = 1; band <= 5; band++) {
		struct ieee80211_channel *channel;

		iwl_init_band_reference(cfg, eeprom, eeprom_size, band,
					&eeprom_ch_count, &eeprom_ch_info,
					&eeprom_ch_array);

		/* Loop through each band adding each of the channels */
		for (ch_idx = 0; ch_idx < eeprom_ch_count; ch_idx++) {
			const struct iwl_eeprom_channel *eeprom_ch;

			eeprom_ch = &eeprom_ch_info[ch_idx];

			if (!(eeprom_ch->flags & EEPROM_CHANNEL_VALID)) {
				IWL_DEBUG_EEPROM(dev,
						 "Ch. %d Flags %x [%sGHz] - No traffic\n",
						 eeprom_ch_array[ch_idx],
						 eeprom_ch_info[ch_idx].flags,
						 (band != 1) ? "5.2" : "2.4");
				continue;
			}

			channel = &data->channels[n_channels];
			n_channels++;

			channel->hw_value = eeprom_ch_array[ch_idx];
			channel->band = (band == 1) ? IEEE80211_BAND_2GHZ
						    : IEEE80211_BAND_5GHZ;
			channel->center_freq =
				ieee80211_channel_to_frequency(
					channel->hw_value, channel->band);

			/* set no-HT40, will enable as appropriate later */
			channel->flags = IEEE80211_CHAN_NO_HT40;

			if (!(eeprom_ch->flags & EEPROM_CHANNEL_IBSS))
				channel->flags |= IEEE80211_CHAN_NO_IBSS;

			if (!(eeprom_ch->flags & EEPROM_CHANNEL_ACTIVE))
				channel->flags |= IEEE80211_CHAN_PASSIVE_SCAN;

			if (eeprom_ch->flags & EEPROM_CHANNEL_RADAR)
				channel->flags |= IEEE80211_CHAN_RADAR;

			/* Initialize regulatory-based run-time data */
			channel->max_power =
				eeprom_ch_info[ch_idx].max_power_avg;
			IWL_DEBUG_EEPROM(dev,
					 "Ch. %d [%sGHz] %s%s%s%s%s%s(0x%02x %ddBm): Ad-Hoc %ssupported\n",
					 channel->hw_value,
					 (band != 1) ? "5.2" : "2.4",
					 CHECK_AND_PRINT_I(VALID),
					 CHECK_AND_PRINT_I(IBSS),
					 CHECK_AND_PRINT_I(ACTIVE),
					 CHECK_AND_PRINT_I(RADAR),
					 CHECK_AND_PRINT_I(WIDE),
					 CHECK_AND_PRINT_I(DFS),
					 eeprom_ch_info[ch_idx].flags,
					 eeprom_ch_info[ch_idx].max_power_avg,
					 ((eeprom_ch_info[ch_idx].flags &
							EEPROM_CHANNEL_IBSS) &&
					  !(eeprom_ch_info[ch_idx].flags &
							EEPROM_CHANNEL_RADAR))
						? "" : "not ");
		}
	}

	if (cfg->eeprom_params->enhanced_txpower) {
		/*
		 * for newer device (6000 series and up)
		 * EEPROM contain enhanced tx power information
		 * driver need to process addition information
		 * to determine the max channel tx power limits
		 */
		iwl_eeprom_enhanced_txpower(dev, data, eeprom, eeprom_size,
					    n_channels);
	} else {
		/* All others use data from channel map */
		int i;

		data->max_tx_pwr_half_dbm = -128;

		for (i = 0; i < n_channels; i++)
			data->max_tx_pwr_half_dbm =
				max_t(s8, data->max_tx_pwr_half_dbm,
				      data->channels[i].max_power * 2);
	}

	/* Check if we do have HT40 channels */
	if (cfg->eeprom_params->regulatory_bands[5] ==
				EEPROM_REGULATORY_BAND_NO_HT40 &&
	    cfg->eeprom_params->regulatory_bands[6] ==
				EEPROM_REGULATORY_BAND_NO_HT40)
		return n_channels;

	/* Two additional EEPROM bands for 2.4 and 5 GHz HT40 channels */
	for (band = 6; band <= 7; band++) {
		enum ieee80211_band ieeeband;

		iwl_init_band_reference(cfg, eeprom, eeprom_size, band,
					&eeprom_ch_count, &eeprom_ch_info,
					&eeprom_ch_array);

		/* EEPROM band 6 is 2.4, band 7 is 5 GHz */
		ieeeband = (band == 6) ? IEEE80211_BAND_2GHZ
				       : IEEE80211_BAND_5GHZ;

		/* Loop through each band adding each of the channels */
		for (ch_idx = 0; ch_idx < eeprom_ch_count; ch_idx++) {
			/* Set up driver's info for lower half */
			iwl_mod_ht40_chan_info(dev, data, n_channels, ieeeband,
					       eeprom_ch_array[ch_idx],
					       &eeprom_ch_info[ch_idx],
					       IEEE80211_CHAN_NO_HT40PLUS);

			/* Set up driver's info for upper half */
			iwl_mod_ht40_chan_info(dev, data, n_channels, ieeeband,
					       eeprom_ch_array[ch_idx] + 4,
					       &eeprom_ch_info[ch_idx],
					       IEEE80211_CHAN_NO_HT40MINUS);
		}
	}

	return n_channels;
}