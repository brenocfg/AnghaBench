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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct ieee80211_supported_band {int /*<<< orphan*/  ht_cap; } ;
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ mgd; } ;
struct ieee80211_sub_if_data {TYPE_2__ u; } ;
struct ieee80211_sta_ht_cap {int cap; } ;
struct ieee80211_ht_cap {int dummy; } ;
struct ieee80211_channel {int flags; } ;
typedef  int /*<<< orphan*/  ht_cap ;
typedef  enum ieee80211_smps_mode { ____Placeholder_ieee80211_smps_mode } ieee80211_smps_mode ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int IEEE80211_CHAN_NO_HT40MINUS ; 
 int IEEE80211_CHAN_NO_HT40PLUS ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
 int IEEE80211_HT_CAP_SM_PS ; 
 int IEEE80211_HT_CAP_SM_PS_SHIFT ; 
 int IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
#define  IEEE80211_HT_PARAM_CHA_SEC_ABOVE 134 
#define  IEEE80211_HT_PARAM_CHA_SEC_BELOW 133 
 int IEEE80211_HT_PARAM_CHA_SEC_OFFSET ; 
#define  IEEE80211_SMPS_AUTOMATIC 132 
#define  IEEE80211_SMPS_DYNAMIC 131 
#define  IEEE80211_SMPS_NUM_MODES 130 
#define  IEEE80211_SMPS_OFF 129 
#define  IEEE80211_SMPS_STATIC 128 
 int IEEE80211_STA_DISABLE_40MHZ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int WLAN_HT_CAP_SM_PS_DISABLED ; 
 int WLAN_HT_CAP_SM_PS_DYNAMIC ; 
 int WLAN_HT_CAP_SM_PS_STATIC ; 
 int /*<<< orphan*/  ieee80211_apply_htcap_overrides (struct ieee80211_sub_if_data*,struct ieee80211_sta_ht_cap*) ; 
 int /*<<< orphan*/  ieee80211_ie_build_ht_cap (int*,struct ieee80211_sta_ht_cap*,int) ; 
 int /*<<< orphan*/  memcpy (struct ieee80211_sta_ht_cap*,int /*<<< orphan*/ *,int) ; 
 int* skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void ieee80211_add_ht_ie(struct ieee80211_sub_if_data *sdata,
				struct sk_buff *skb, u8 ap_ht_param,
				struct ieee80211_supported_band *sband,
				struct ieee80211_channel *channel,
				enum ieee80211_smps_mode smps)
{
	u8 *pos;
	u32 flags = channel->flags;
	u16 cap;
	struct ieee80211_sta_ht_cap ht_cap;

	BUILD_BUG_ON(sizeof(ht_cap) != sizeof(sband->ht_cap));

	memcpy(&ht_cap, &sband->ht_cap, sizeof(ht_cap));
	ieee80211_apply_htcap_overrides(sdata, &ht_cap);

	/* determine capability flags */
	cap = ht_cap.cap;

	switch (ap_ht_param & IEEE80211_HT_PARAM_CHA_SEC_OFFSET) {
	case IEEE80211_HT_PARAM_CHA_SEC_ABOVE:
		if (flags & IEEE80211_CHAN_NO_HT40PLUS) {
			cap &= ~IEEE80211_HT_CAP_SUP_WIDTH_20_40;
			cap &= ~IEEE80211_HT_CAP_SGI_40;
		}
		break;
	case IEEE80211_HT_PARAM_CHA_SEC_BELOW:
		if (flags & IEEE80211_CHAN_NO_HT40MINUS) {
			cap &= ~IEEE80211_HT_CAP_SUP_WIDTH_20_40;
			cap &= ~IEEE80211_HT_CAP_SGI_40;
		}
		break;
	}

	/*
	 * If 40 MHz was disabled associate as though we weren't
	 * capable of 40 MHz -- some broken APs will never fall
	 * back to trying to transmit in 20 MHz.
	 */
	if (sdata->u.mgd.flags & IEEE80211_STA_DISABLE_40MHZ) {
		cap &= ~IEEE80211_HT_CAP_SUP_WIDTH_20_40;
		cap &= ~IEEE80211_HT_CAP_SGI_40;
	}

	/* set SM PS mode properly */
	cap &= ~IEEE80211_HT_CAP_SM_PS;
	switch (smps) {
	case IEEE80211_SMPS_AUTOMATIC:
	case IEEE80211_SMPS_NUM_MODES:
		WARN_ON(1);
	case IEEE80211_SMPS_OFF:
		cap |= WLAN_HT_CAP_SM_PS_DISABLED <<
			IEEE80211_HT_CAP_SM_PS_SHIFT;
		break;
	case IEEE80211_SMPS_STATIC:
		cap |= WLAN_HT_CAP_SM_PS_STATIC <<
			IEEE80211_HT_CAP_SM_PS_SHIFT;
		break;
	case IEEE80211_SMPS_DYNAMIC:
		cap |= WLAN_HT_CAP_SM_PS_DYNAMIC <<
			IEEE80211_HT_CAP_SM_PS_SHIFT;
		break;
	}

	/* reserve and fill IE */
	pos = skb_put(skb, sizeof(struct ieee80211_ht_cap) + 2);
	ieee80211_ie_build_ht_cap(pos, &ht_cap, cap);
}