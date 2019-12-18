#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tx_frame_hdr {int dummy; } ;
struct ieee80211_hw {int flags; int queues; int channel_change_time; int max_listen_interval; int vif_data_size; int sta_data_size; int extra_tx_headroom; TYPE_1__* wiphy; } ;
struct htc_frame_hdr {int dummy; } ;
struct ath_common {int /*<<< orphan*/  macaddr; } ;
struct ath9k_htc_vif {int dummy; } ;
struct ath9k_htc_sta {int dummy; } ;
struct ath9k_htc_priv {TYPE_3__* sbands; TYPE_4__* ah; } ;
struct TYPE_6__ {int hw_caps; } ;
struct TYPE_8__ {TYPE_2__ caps; } ;
struct TYPE_7__ {int /*<<< orphan*/  ht_cap; } ;
struct TYPE_5__ {int interface_modes; int n_iface_combinations; int flags; TYPE_3__** bands; int /*<<< orphan*/ * iface_combinations; } ;

/* Variables and functions */
 int ATH9K_HW_CAP_2GHZ ; 
 int ATH9K_HW_CAP_5GHZ ; 
 int ATH9K_HW_CAP_HT ; 
 int BIT (int /*<<< orphan*/ ) ; 
 size_t IEEE80211_BAND_2GHZ ; 
 size_t IEEE80211_BAND_5GHZ ; 
 int IEEE80211_HW_AMPDU_AGGREGATION ; 
 int IEEE80211_HW_HAS_RATE_CONTROL ; 
 int IEEE80211_HW_HOST_BROADCAST_PS_BUFFERING ; 
 int IEEE80211_HW_PS_NULLFUNC_STACK ; 
 int IEEE80211_HW_REPORTS_TX_ACK_STATUS ; 
 int IEEE80211_HW_RX_INCLUDES_FCS ; 
 int IEEE80211_HW_SIGNAL_DBM ; 
 int IEEE80211_HW_SPECTRUM_MGMT ; 
 int IEEE80211_HW_SUPPORTS_PS ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  NL80211_IFTYPE_P2P_CLIENT ; 
 int /*<<< orphan*/  NL80211_IFTYPE_P2P_GO ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  SET_IEEE80211_PERM_ADDR (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL ; 
 int WIPHY_FLAG_IBSS_RSN ; 
 int WIPHY_FLAG_PS_ON_BY_DEFAULT ; 
 struct ath_common* ath9k_hw_common (TYPE_4__*) ; 
 int /*<<< orphan*/  if_comb ; 
 int /*<<< orphan*/  setup_ht_cap (struct ath9k_htc_priv*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_set_hw_capab(struct ath9k_htc_priv *priv,
			       struct ieee80211_hw *hw)
{
	struct ath_common *common = ath9k_hw_common(priv->ah);

	hw->flags = IEEE80211_HW_SIGNAL_DBM |
		IEEE80211_HW_AMPDU_AGGREGATION |
		IEEE80211_HW_SPECTRUM_MGMT |
		IEEE80211_HW_HAS_RATE_CONTROL |
		IEEE80211_HW_RX_INCLUDES_FCS |
		IEEE80211_HW_SUPPORTS_PS |
		IEEE80211_HW_PS_NULLFUNC_STACK |
		IEEE80211_HW_REPORTS_TX_ACK_STATUS |
		IEEE80211_HW_HOST_BROADCAST_PS_BUFFERING;

	hw->wiphy->interface_modes =
		BIT(NL80211_IFTYPE_STATION) |
		BIT(NL80211_IFTYPE_ADHOC) |
		BIT(NL80211_IFTYPE_AP) |
		BIT(NL80211_IFTYPE_P2P_GO) |
		BIT(NL80211_IFTYPE_P2P_CLIENT);

	hw->wiphy->iface_combinations = &if_comb;
	hw->wiphy->n_iface_combinations = 1;

	hw->wiphy->flags &= ~WIPHY_FLAG_PS_ON_BY_DEFAULT;

	hw->wiphy->flags |= WIPHY_FLAG_IBSS_RSN |
			    WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL;

	hw->queues = 4;
	hw->channel_change_time = 5000;
	hw->max_listen_interval = 1;

	hw->vif_data_size = sizeof(struct ath9k_htc_vif);
	hw->sta_data_size = sizeof(struct ath9k_htc_sta);

	/* tx_frame_hdr is larger than tx_mgmt_hdr anyway */
	hw->extra_tx_headroom = sizeof(struct tx_frame_hdr) +
		sizeof(struct htc_frame_hdr) + 4;

	if (priv->ah->caps.hw_caps & ATH9K_HW_CAP_2GHZ)
		hw->wiphy->bands[IEEE80211_BAND_2GHZ] =
			&priv->sbands[IEEE80211_BAND_2GHZ];
	if (priv->ah->caps.hw_caps & ATH9K_HW_CAP_5GHZ)
		hw->wiphy->bands[IEEE80211_BAND_5GHZ] =
			&priv->sbands[IEEE80211_BAND_5GHZ];

	if (priv->ah->caps.hw_caps & ATH9K_HW_CAP_HT) {
		if (priv->ah->caps.hw_caps & ATH9K_HW_CAP_2GHZ)
			setup_ht_cap(priv,
				     &priv->sbands[IEEE80211_BAND_2GHZ].ht_cap);
		if (priv->ah->caps.hw_caps & ATH9K_HW_CAP_5GHZ)
			setup_ht_cap(priv,
				     &priv->sbands[IEEE80211_BAND_5GHZ].ht_cap);
	}

	SET_IEEE80211_PERM_ADDR(hw, common->macaddr);
}