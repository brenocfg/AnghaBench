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
struct ath9k_htc_priv {TYPE_3__* sbands; TYPE_2__* ah; } ;
struct TYPE_6__ {size_t band; void* n_bitrates; void* bitrates; void* n_channels; void* channels; } ;
struct TYPE_4__ {int hw_caps; } ;
struct TYPE_5__ {TYPE_1__ caps; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int ATH9K_HW_CAP_2GHZ ; 
 int ATH9K_HW_CAP_5GHZ ; 
 size_t IEEE80211_BAND_2GHZ ; 
 size_t IEEE80211_BAND_5GHZ ; 
 void* ath9k_2ghz_channels ; 
 void* ath9k_5ghz_channels ; 
 void* ath9k_legacy_rates ; 

__attribute__((used)) static void ath9k_init_channels_rates(struct ath9k_htc_priv *priv)
{
	if (priv->ah->caps.hw_caps & ATH9K_HW_CAP_2GHZ) {
		priv->sbands[IEEE80211_BAND_2GHZ].channels =
			ath9k_2ghz_channels;
		priv->sbands[IEEE80211_BAND_2GHZ].band = IEEE80211_BAND_2GHZ;
		priv->sbands[IEEE80211_BAND_2GHZ].n_channels =
			ARRAY_SIZE(ath9k_2ghz_channels);
		priv->sbands[IEEE80211_BAND_2GHZ].bitrates = ath9k_legacy_rates;
		priv->sbands[IEEE80211_BAND_2GHZ].n_bitrates =
			ARRAY_SIZE(ath9k_legacy_rates);
	}

	if (priv->ah->caps.hw_caps & ATH9K_HW_CAP_5GHZ) {
		priv->sbands[IEEE80211_BAND_5GHZ].channels = ath9k_5ghz_channels;
		priv->sbands[IEEE80211_BAND_5GHZ].band = IEEE80211_BAND_5GHZ;
		priv->sbands[IEEE80211_BAND_5GHZ].n_channels =
			ARRAY_SIZE(ath9k_5ghz_channels);
		priv->sbands[IEEE80211_BAND_5GHZ].bitrates =
			ath9k_legacy_rates + 4;
		priv->sbands[IEEE80211_BAND_5GHZ].n_bitrates =
			ARRAY_SIZE(ath9k_legacy_rates) - 4;
	}
}