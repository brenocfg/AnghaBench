#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wiphy {int features; struct ieee80211_supported_band** bands; } ;
struct sk_buff {int dummy; } ;
struct net_device {struct wiphy wiphy; TYPE_2__* ieee80211_ptr; TYPE_1__* ops; } ;
struct ieee80211_supported_band {int dummy; } ;
struct genl_info {scalar_t__* attrs; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {struct wiphy wiphy; TYPE_2__* ieee80211_ptr; TYPE_1__* ops; } ;
struct TYPE_9__ {scalar_t__ width; TYPE_3__* chan; } ;
struct cfg80211_ibss_params {int beacon_interval; int channel_fixed; int privacy; int /*<<< orphan*/  control_port; TYPE_4__ chandef; int /*<<< orphan*/  mcast_rate; int /*<<< orphan*/  basic_rates; void* ie_len; void* ie; void* ssid_len; void* ssid; void* bssid; } ;
struct cfg80211_cached_keys {int dummy; } ;
typedef  int /*<<< orphan*/  ibss ;
struct TYPE_8__ {size_t band; } ;
struct TYPE_7__ {scalar_t__ iftype; } ;
struct TYPE_6__ {int /*<<< orphan*/  join_ibss; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct cfg80211_cached_keys*) ; 
 size_t NL80211_ATTR_BEACON_INTERVAL ; 
 size_t NL80211_ATTR_BSS_BASIC_RATES ; 
 size_t NL80211_ATTR_CONTROL_PORT ; 
 size_t NL80211_ATTR_FREQ_FIXED ; 
 size_t NL80211_ATTR_IE ; 
 size_t NL80211_ATTR_KEYS ; 
 size_t NL80211_ATTR_MAC ; 
 size_t NL80211_ATTR_MCAST_RATE ; 
 size_t NL80211_ATTR_PRIVACY ; 
 size_t NL80211_ATTR_SSID ; 
 scalar_t__ NL80211_CHAN_WIDTH_20_NOHT ; 
 scalar_t__ NL80211_CHAN_WIDTH_40 ; 
 int NL80211_FEATURE_HT_IBSS ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 int PTR_ERR (struct cfg80211_cached_keys*) ; 
 int cfg80211_join_ibss (struct net_device*,struct net_device*,struct cfg80211_ibss_params*,struct cfg80211_cached_keys*) ; 
 int /*<<< orphan*/  cfg80211_reg_can_beacon (struct wiphy*,TYPE_4__*) ; 
 int ieee80211_get_ratemask (struct ieee80211_supported_band*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_valid_ether_addr (void*) ; 
 int /*<<< orphan*/  is_valid_ie_attr (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct cfg80211_cached_keys*) ; 
 int /*<<< orphan*/  memset (struct cfg80211_ibss_params*,int /*<<< orphan*/ ,int) ; 
 int nl80211_parse_chandef (struct net_device*,struct genl_info*,TYPE_4__*) ; 
 struct cfg80211_cached_keys* nl80211_parse_connkeys (struct net_device*,scalar_t__,int*) ; 
 int /*<<< orphan*/  nl80211_parse_mcast_rate (struct net_device*,int /*<<< orphan*/ ,int) ; 
 void* nla_data (scalar_t__) ; 
 int /*<<< orphan*/  nla_get_flag (scalar_t__) ; 
 int nla_get_u32 (scalar_t__) ; 
 void* nla_len (scalar_t__) ; 

__attribute__((used)) static int nl80211_join_ibss(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct cfg80211_ibss_params ibss;
	struct wiphy *wiphy;
	struct cfg80211_cached_keys *connkeys = NULL;
	int err;

	memset(&ibss, 0, sizeof(ibss));

	if (!is_valid_ie_attr(info->attrs[NL80211_ATTR_IE]))
		return -EINVAL;

	if (!info->attrs[NL80211_ATTR_SSID] ||
	    !nla_len(info->attrs[NL80211_ATTR_SSID]))
		return -EINVAL;

	ibss.beacon_interval = 100;

	if (info->attrs[NL80211_ATTR_BEACON_INTERVAL]) {
		ibss.beacon_interval =
			nla_get_u32(info->attrs[NL80211_ATTR_BEACON_INTERVAL]);
		if (ibss.beacon_interval < 1 || ibss.beacon_interval > 10000)
			return -EINVAL;
	}

	if (!rdev->ops->join_ibss)
		return -EOPNOTSUPP;

	if (dev->ieee80211_ptr->iftype != NL80211_IFTYPE_ADHOC)
		return -EOPNOTSUPP;

	wiphy = &rdev->wiphy;

	if (info->attrs[NL80211_ATTR_MAC]) {
		ibss.bssid = nla_data(info->attrs[NL80211_ATTR_MAC]);

		if (!is_valid_ether_addr(ibss.bssid))
			return -EINVAL;
	}
	ibss.ssid = nla_data(info->attrs[NL80211_ATTR_SSID]);
	ibss.ssid_len = nla_len(info->attrs[NL80211_ATTR_SSID]);

	if (info->attrs[NL80211_ATTR_IE]) {
		ibss.ie = nla_data(info->attrs[NL80211_ATTR_IE]);
		ibss.ie_len = nla_len(info->attrs[NL80211_ATTR_IE]);
	}

	err = nl80211_parse_chandef(rdev, info, &ibss.chandef);
	if (err)
		return err;

	if (!cfg80211_reg_can_beacon(&rdev->wiphy, &ibss.chandef))
		return -EINVAL;

	if (ibss.chandef.width > NL80211_CHAN_WIDTH_40)
		return -EINVAL;
	if (ibss.chandef.width != NL80211_CHAN_WIDTH_20_NOHT &&
	    !(rdev->wiphy.features & NL80211_FEATURE_HT_IBSS))
		return -EINVAL;

	ibss.channel_fixed = !!info->attrs[NL80211_ATTR_FREQ_FIXED];
	ibss.privacy = !!info->attrs[NL80211_ATTR_PRIVACY];

	if (info->attrs[NL80211_ATTR_BSS_BASIC_RATES]) {
		u8 *rates =
			nla_data(info->attrs[NL80211_ATTR_BSS_BASIC_RATES]);
		int n_rates =
			nla_len(info->attrs[NL80211_ATTR_BSS_BASIC_RATES]);
		struct ieee80211_supported_band *sband =
			wiphy->bands[ibss.chandef.chan->band];

		err = ieee80211_get_ratemask(sband, rates, n_rates,
					     &ibss.basic_rates);
		if (err)
			return err;
	}

	if (info->attrs[NL80211_ATTR_MCAST_RATE] &&
	    !nl80211_parse_mcast_rate(rdev, ibss.mcast_rate,
			nla_get_u32(info->attrs[NL80211_ATTR_MCAST_RATE])))
		return -EINVAL;

	if (ibss.privacy && info->attrs[NL80211_ATTR_KEYS]) {
		bool no_ht = false;

		connkeys = nl80211_parse_connkeys(rdev,
					  info->attrs[NL80211_ATTR_KEYS],
					  &no_ht);
		if (IS_ERR(connkeys))
			return PTR_ERR(connkeys);

		if ((ibss.chandef.width != NL80211_CHAN_WIDTH_20_NOHT) &&
		    no_ht) {
			kfree(connkeys);
			return -EINVAL;
		}
	}

	ibss.control_port =
		nla_get_flag(info->attrs[NL80211_ATTR_CONTROL_PORT]);

	err = cfg80211_join_ibss(rdev, dev, &ibss, connkeys);
	if (err)
		kfree(connkeys);
	return err;
}