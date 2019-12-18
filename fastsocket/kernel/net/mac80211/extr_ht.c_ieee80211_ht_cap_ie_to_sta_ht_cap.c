#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_12__ {int bandwidth; int smps_mode; int /*<<< orphan*/  ht_cap; } ;
struct sta_info {TYPE_6__ sta; void* cur_max_bandwidth; } ;
struct TYPE_8__ {int tx_params; int* rx_mask; } ;
struct ieee80211_sta_ht_cap {int ht_supported; int cap; int ampdu_factor; int ampdu_density; TYPE_2__ mcs; } ;
struct ieee80211_supported_band {struct ieee80211_sta_ht_cap ht_cap; } ;
struct TYPE_9__ {int width; } ;
struct TYPE_10__ {TYPE_3__ chandef; } ;
struct TYPE_11__ {scalar_t__ type; TYPE_4__ bss_conf; } ;
struct ieee80211_sub_if_data {TYPE_5__ vif; } ;
struct TYPE_7__ {int tx_params; int* rx_mask; } ;
struct ieee80211_ht_cap {int ampdu_params_info; TYPE_1__ mcs; int /*<<< orphan*/  cap_info; } ;
typedef  int /*<<< orphan*/  ht_cap ;
typedef  enum ieee80211_sta_rx_bandwidth { ____Placeholder_ieee80211_sta_rx_bandwidth } ieee80211_sta_rx_bandwidth ;
typedef  enum ieee80211_smps_mode { ____Placeholder_ieee80211_smps_mode } ieee80211_smps_mode ;

/* Variables and functions */
 int IEEE80211_HT_AMPDU_PARM_DENSITY ; 
 int IEEE80211_HT_AMPDU_PARM_FACTOR ; 
 int IEEE80211_HT_CAP_DSSSCCK40 ; 
 int IEEE80211_HT_CAP_GRN_FLD ; 
 int IEEE80211_HT_CAP_LDPC_CODING ; 
 int IEEE80211_HT_CAP_RX_STBC ; 
 int IEEE80211_HT_CAP_SGI_20 ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
 int IEEE80211_HT_CAP_SM_PS ; 
 int IEEE80211_HT_CAP_SM_PS_SHIFT ; 
 int IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 int IEEE80211_HT_CAP_TX_STBC ; 
 int IEEE80211_HT_MCS_MASK_LEN ; 
 int IEEE80211_HT_MCS_TX_DEFINED ; 
 int IEEE80211_HT_MCS_TX_MAX_STREAMS ; 
 int IEEE80211_HT_MCS_TX_MAX_STREAMS_MASK ; 
 int IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT ; 
 int IEEE80211_HT_MCS_TX_RX_DIFF ; 
 int IEEE80211_HT_MCS_TX_UNEQUAL_MODULATION ; 
 int IEEE80211_HT_MCS_UNEQUAL_MODULATION_START_BYTE ; 
 int IEEE80211_SMPS_DYNAMIC ; 
 int IEEE80211_SMPS_OFF ; 
 int IEEE80211_SMPS_STATIC ; 
 void* IEEE80211_STA_RX_BW_20 ; 
 void* IEEE80211_STA_RX_BW_40 ; 
#define  NL80211_CHAN_WIDTH_160 137 
#define  NL80211_CHAN_WIDTH_20 136 
#define  NL80211_CHAN_WIDTH_20_NOHT 135 
#define  NL80211_CHAN_WIDTH_40 134 
#define  NL80211_CHAN_WIDTH_80 133 
#define  NL80211_CHAN_WIDTH_80P80 132 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
#define  WLAN_HT_CAP_SM_PS_DISABLED 131 
#define  WLAN_HT_CAP_SM_PS_DYNAMIC 130 
#define  WLAN_HT_CAP_SM_PS_INVALID 129 
#define  WLAN_HT_CAP_SM_PS_STATIC 128 
 int /*<<< orphan*/  WLAN_STA_TDLS_PEER ; 
 int /*<<< orphan*/  ieee80211_apply_htcap_overrides (struct ieee80211_sub_if_data*,struct ieee80211_sta_ht_cap*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int memcmp (int /*<<< orphan*/ *,struct ieee80211_sta_ht_cap*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ieee80211_sta_ht_cap*,int) ; 
 int /*<<< orphan*/  memset (struct ieee80211_sta_ht_cap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 

bool ieee80211_ht_cap_ie_to_sta_ht_cap(struct ieee80211_sub_if_data *sdata,
				       struct ieee80211_supported_band *sband,
				       const struct ieee80211_ht_cap *ht_cap_ie,
				       struct sta_info *sta)
{
	struct ieee80211_sta_ht_cap ht_cap, own_cap;
	u8 ampdu_info, tx_mcs_set_cap;
	int i, max_tx_streams;
	bool changed;
	enum ieee80211_sta_rx_bandwidth bw;
	enum ieee80211_smps_mode smps_mode;

	memset(&ht_cap, 0, sizeof(ht_cap));

	if (!ht_cap_ie || !sband->ht_cap.ht_supported)
		goto apply;

	ht_cap.ht_supported = true;

	own_cap = sband->ht_cap;

	/*
	 * If user has specified capability over-rides, take care
	 * of that if the station we're setting up is the AP that
	 * we advertised a restricted capability set to. Override
	 * our own capabilities and then use those below.
	 */
	if (sdata->vif.type == NL80211_IFTYPE_STATION &&
	    !test_sta_flag(sta, WLAN_STA_TDLS_PEER))
		ieee80211_apply_htcap_overrides(sdata, &own_cap);

	/*
	 * The bits listed in this expression should be
	 * the same for the peer and us, if the station
	 * advertises more then we can't use those thus
	 * we mask them out.
	 */
	ht_cap.cap = le16_to_cpu(ht_cap_ie->cap_info) &
		(own_cap.cap | ~(IEEE80211_HT_CAP_LDPC_CODING |
				 IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
				 IEEE80211_HT_CAP_GRN_FLD |
				 IEEE80211_HT_CAP_SGI_20 |
				 IEEE80211_HT_CAP_SGI_40 |
				 IEEE80211_HT_CAP_DSSSCCK40));

	/*
	 * The STBC bits are asymmetric -- if we don't have
	 * TX then mask out the peer's RX and vice versa.
	 */
	if (!(own_cap.cap & IEEE80211_HT_CAP_TX_STBC))
		ht_cap.cap &= ~IEEE80211_HT_CAP_RX_STBC;
	if (!(own_cap.cap & IEEE80211_HT_CAP_RX_STBC))
		ht_cap.cap &= ~IEEE80211_HT_CAP_TX_STBC;

	ampdu_info = ht_cap_ie->ampdu_params_info;
	ht_cap.ampdu_factor =
		ampdu_info & IEEE80211_HT_AMPDU_PARM_FACTOR;
	ht_cap.ampdu_density =
		(ampdu_info & IEEE80211_HT_AMPDU_PARM_DENSITY) >> 2;

	/* own MCS TX capabilities */
	tx_mcs_set_cap = own_cap.mcs.tx_params;

	/* Copy peer MCS TX capabilities, the driver might need them. */
	ht_cap.mcs.tx_params = ht_cap_ie->mcs.tx_params;

	/* can we TX with MCS rates? */
	if (!(tx_mcs_set_cap & IEEE80211_HT_MCS_TX_DEFINED))
		goto apply;

	/* Counting from 0, therefore +1 */
	if (tx_mcs_set_cap & IEEE80211_HT_MCS_TX_RX_DIFF)
		max_tx_streams =
			((tx_mcs_set_cap & IEEE80211_HT_MCS_TX_MAX_STREAMS_MASK)
				>> IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT) + 1;
	else
		max_tx_streams = IEEE80211_HT_MCS_TX_MAX_STREAMS;

	/*
	 * 802.11n-2009 20.3.5 / 20.6 says:
	 * - indices 0 to 7 and 32 are single spatial stream
	 * - 8 to 31 are multiple spatial streams using equal modulation
	 *   [8..15 for two streams, 16..23 for three and 24..31 for four]
	 * - remainder are multiple spatial streams using unequal modulation
	 */
	for (i = 0; i < max_tx_streams; i++)
		ht_cap.mcs.rx_mask[i] =
			own_cap.mcs.rx_mask[i] & ht_cap_ie->mcs.rx_mask[i];

	if (tx_mcs_set_cap & IEEE80211_HT_MCS_TX_UNEQUAL_MODULATION)
		for (i = IEEE80211_HT_MCS_UNEQUAL_MODULATION_START_BYTE;
		     i < IEEE80211_HT_MCS_MASK_LEN; i++)
			ht_cap.mcs.rx_mask[i] =
				own_cap.mcs.rx_mask[i] &
					ht_cap_ie->mcs.rx_mask[i];

	/* handle MCS rate 32 too */
	if (own_cap.mcs.rx_mask[32/8] & ht_cap_ie->mcs.rx_mask[32/8] & 1)
		ht_cap.mcs.rx_mask[32/8] |= 1;

 apply:
	changed = memcmp(&sta->sta.ht_cap, &ht_cap, sizeof(ht_cap));

	memcpy(&sta->sta.ht_cap, &ht_cap, sizeof(ht_cap));

	switch (sdata->vif.bss_conf.chandef.width) {
	default:
		WARN_ON_ONCE(1);
		/* fall through */
	case NL80211_CHAN_WIDTH_20_NOHT:
	case NL80211_CHAN_WIDTH_20:
		bw = IEEE80211_STA_RX_BW_20;
		break;
	case NL80211_CHAN_WIDTH_40:
	case NL80211_CHAN_WIDTH_80:
	case NL80211_CHAN_WIDTH_80P80:
	case NL80211_CHAN_WIDTH_160:
		bw = ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40 ?
				IEEE80211_STA_RX_BW_40 : IEEE80211_STA_RX_BW_20;
		break;
	}

	if (bw != sta->sta.bandwidth)
		changed = true;
	sta->sta.bandwidth = bw;

	sta->cur_max_bandwidth =
		ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40 ?
				IEEE80211_STA_RX_BW_40 : IEEE80211_STA_RX_BW_20;

	switch ((ht_cap.cap & IEEE80211_HT_CAP_SM_PS)
			>> IEEE80211_HT_CAP_SM_PS_SHIFT) {
	case WLAN_HT_CAP_SM_PS_INVALID:
	case WLAN_HT_CAP_SM_PS_STATIC:
		smps_mode = IEEE80211_SMPS_STATIC;
		break;
	case WLAN_HT_CAP_SM_PS_DYNAMIC:
		smps_mode = IEEE80211_SMPS_DYNAMIC;
		break;
	case WLAN_HT_CAP_SM_PS_DISABLED:
		smps_mode = IEEE80211_SMPS_OFF;
		break;
	}

	if (smps_mode != sta->sta.smps_mode)
		changed = true;
	sta->sta.smps_mode = smps_mode;

	return changed;
}