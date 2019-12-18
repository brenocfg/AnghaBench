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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_sta_ht_cap {int cap; int /*<<< orphan*/  mcs; } ;
struct ieee80211_ht_operation {int stbc_param; int /*<<< orphan*/  basic_set; int /*<<< orphan*/  operation_mode; int /*<<< orphan*/  ht_param; int /*<<< orphan*/  primary_chan; } ;
struct cfg80211_chan_def {int width; TYPE_1__* chan; int /*<<< orphan*/  center_freq1; } ;
struct TYPE_2__ {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 int /*<<< orphan*/  IEEE80211_HT_PARAM_CHAN_WIDTH_ANY ; 
 int /*<<< orphan*/  IEEE80211_HT_PARAM_CHA_SEC_ABOVE ; 
 int /*<<< orphan*/  IEEE80211_HT_PARAM_CHA_SEC_BELOW ; 
 int /*<<< orphan*/  IEEE80211_HT_PARAM_CHA_SEC_NONE ; 
#define  NL80211_CHAN_WIDTH_160 131 
 int NL80211_CHAN_WIDTH_20 ; 
 int NL80211_CHAN_WIDTH_20_NOHT ; 
#define  NL80211_CHAN_WIDTH_40 130 
#define  NL80211_CHAN_WIDTH_80 129 
#define  NL80211_CHAN_WIDTH_80P80 128 
 int /*<<< orphan*/  WLAN_EID_HT_OPERATION ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_frequency_to_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

u8 *ieee80211_ie_build_ht_oper(u8 *pos, struct ieee80211_sta_ht_cap *ht_cap,
			       const struct cfg80211_chan_def *chandef,
			       u16 prot_mode)
{
	struct ieee80211_ht_operation *ht_oper;
	/* Build HT Information */
	*pos++ = WLAN_EID_HT_OPERATION;
	*pos++ = sizeof(struct ieee80211_ht_operation);
	ht_oper = (struct ieee80211_ht_operation *)pos;
	ht_oper->primary_chan = ieee80211_frequency_to_channel(
					chandef->chan->center_freq);
	switch (chandef->width) {
	case NL80211_CHAN_WIDTH_160:
	case NL80211_CHAN_WIDTH_80P80:
	case NL80211_CHAN_WIDTH_80:
	case NL80211_CHAN_WIDTH_40:
		if (chandef->center_freq1 > chandef->chan->center_freq)
			ht_oper->ht_param = IEEE80211_HT_PARAM_CHA_SEC_ABOVE;
		else
			ht_oper->ht_param = IEEE80211_HT_PARAM_CHA_SEC_BELOW;
		break;
	default:
		ht_oper->ht_param = IEEE80211_HT_PARAM_CHA_SEC_NONE;
		break;
	}
	if (ht_cap->cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40 &&
	    chandef->width != NL80211_CHAN_WIDTH_20_NOHT &&
	    chandef->width != NL80211_CHAN_WIDTH_20)
		ht_oper->ht_param |= IEEE80211_HT_PARAM_CHAN_WIDTH_ANY;

	ht_oper->operation_mode = cpu_to_le16(prot_mode);
	ht_oper->stbc_param = 0x0000;

	/* It seems that Basic MCS set and Supported MCS set
	   are identical for the first 10 bytes */
	memset(&ht_oper->basic_set, 0, 16);
	memcpy(&ht_oper->basic_set, &ht_cap->mcs, 10);

	return pos + sizeof(struct ieee80211_ht_operation);
}