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
struct il_vif_priv {int dummy; } ;
struct il_priv {int mac80211_registered; struct ieee80211_hw* hw; TYPE_2__* bands; } ;
struct il3945_sta_priv {int dummy; } ;
struct ieee80211_hw {char* rate_control_algorithm; int sta_data_size; int vif_data_size; int flags; int queues; TYPE_1__* wiphy; } ;
struct TYPE_4__ {scalar_t__ n_channels; } ;
struct TYPE_3__ {int interface_modes; int flags; int max_scan_ie_len; TYPE_2__** bands; int /*<<< orphan*/  max_scan_ssids; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 size_t IEEE80211_BAND_2GHZ ; 
 size_t IEEE80211_BAND_5GHZ ; 
 int IEEE80211_HW_SIGNAL_DBM ; 
 int IEEE80211_HW_SPECTRUM_MGMT ; 
 int IEEE80211_HW_SUPPORTS_DYNAMIC_PS ; 
 int IEEE80211_HW_SUPPORTS_PS ; 
 int IL3945_MAX_PROBE_REQUEST ; 
 int /*<<< orphan*/  IL_ERR (char*,int) ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  PROBE_OPTION_MAX_3945 ; 
 int WIPHY_FLAG_CUSTOM_REGULATORY ; 
 int WIPHY_FLAG_DISABLE_BEACON_HINTS ; 
 int WIPHY_FLAG_IBSS_RSN ; 
 int WIPHY_FLAG_PS_ON_BY_DEFAULT ; 
 int ieee80211_register_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  il_leds_init (struct il_priv*) ; 

__attribute__((used)) static int
il3945_setup_mac(struct il_priv *il)
{
	int ret;
	struct ieee80211_hw *hw = il->hw;

	hw->rate_control_algorithm = "iwl-3945-rs";
	hw->sta_data_size = sizeof(struct il3945_sta_priv);
	hw->vif_data_size = sizeof(struct il_vif_priv);

	/* Tell mac80211 our characteristics */
	hw->flags = IEEE80211_HW_SIGNAL_DBM | IEEE80211_HW_SPECTRUM_MGMT |
		    IEEE80211_HW_SUPPORTS_PS | IEEE80211_HW_SUPPORTS_DYNAMIC_PS;

	hw->wiphy->interface_modes =
	    BIT(NL80211_IFTYPE_STATION) | BIT(NL80211_IFTYPE_ADHOC);

	hw->wiphy->flags |=
	    WIPHY_FLAG_CUSTOM_REGULATORY | WIPHY_FLAG_DISABLE_BEACON_HINTS |
	    WIPHY_FLAG_IBSS_RSN;

	hw->wiphy->flags &= ~WIPHY_FLAG_PS_ON_BY_DEFAULT;

	hw->wiphy->max_scan_ssids = PROBE_OPTION_MAX_3945;
	/* we create the 802.11 header and a zero-length SSID element */
	hw->wiphy->max_scan_ie_len = IL3945_MAX_PROBE_REQUEST - 24 - 2;

	/* Default value; 4 EDCA QOS priorities */
	hw->queues = 4;

	if (il->bands[IEEE80211_BAND_2GHZ].n_channels)
		il->hw->wiphy->bands[IEEE80211_BAND_2GHZ] =
		    &il->bands[IEEE80211_BAND_2GHZ];

	if (il->bands[IEEE80211_BAND_5GHZ].n_channels)
		il->hw->wiphy->bands[IEEE80211_BAND_5GHZ] =
		    &il->bands[IEEE80211_BAND_5GHZ];

	il_leds_init(il);

	ret = ieee80211_register_hw(il->hw);
	if (ret) {
		IL_ERR("Failed to register hw (error %d)\n", ret);
		return ret;
	}
	il->mac80211_registered = 1;

	return 0;
}