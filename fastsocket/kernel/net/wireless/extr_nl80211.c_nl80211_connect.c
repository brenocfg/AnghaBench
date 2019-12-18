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
struct wiphy {int flags; } ;
struct sk_buff {int dummy; } ;
struct net_device {struct wiphy wiphy; TYPE_1__* ieee80211_ptr; } ;
struct genl_info {scalar_t__* attrs; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {struct wiphy wiphy; TYPE_1__* ieee80211_ptr; } ;
struct cfg80211_connect_params {int bg_scan_period; scalar_t__ mfp; int /*<<< orphan*/  vht_capa; int /*<<< orphan*/  vht_capa_mask; int /*<<< orphan*/  flags; int /*<<< orphan*/  ht_capa; int /*<<< orphan*/  ht_capa_mask; scalar_t__ privacy; TYPE_2__* channel; void* ie_len; void* ie; void* ssid_len; void* ssid; void* bssid; int /*<<< orphan*/  crypto; void* auth_type; } ;
struct cfg80211_cached_keys {int dummy; } ;
typedef  int /*<<< orphan*/  connect ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {scalar_t__ iftype; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSOC_REQ_DISABLE_HT ; 
 int /*<<< orphan*/  ASSOC_REQ_DISABLE_VHT ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int IEEE80211_CHAN_DISABLED ; 
 scalar_t__ IS_ERR (struct cfg80211_cached_keys*) ; 
 size_t NL80211_ATTR_AUTH_TYPE ; 
 size_t NL80211_ATTR_BG_SCAN_PERIOD ; 
 size_t NL80211_ATTR_DISABLE_HT ; 
 size_t NL80211_ATTR_DISABLE_VHT ; 
 size_t NL80211_ATTR_HT_CAPABILITY ; 
 size_t NL80211_ATTR_HT_CAPABILITY_MASK ; 
 size_t NL80211_ATTR_IE ; 
 size_t NL80211_ATTR_KEYS ; 
 size_t NL80211_ATTR_MAC ; 
 size_t NL80211_ATTR_PRIVACY ; 
 size_t NL80211_ATTR_SSID ; 
 size_t NL80211_ATTR_USE_MFP ; 
 size_t NL80211_ATTR_VHT_CAPABILITY ; 
 size_t NL80211_ATTR_VHT_CAPABILITY_MASK ; 
 size_t NL80211_ATTR_WIPHY_FREQ ; 
 void* NL80211_AUTHTYPE_AUTOMATIC ; 
 int /*<<< orphan*/  NL80211_CMD_CONNECT ; 
 scalar_t__ NL80211_IFTYPE_P2P_CLIENT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  NL80211_MAX_NR_CIPHER_SUITES ; 
 scalar_t__ NL80211_MFP_NO ; 
 scalar_t__ NL80211_MFP_REQUIRED ; 
 int PTR_ERR (struct cfg80211_cached_keys*) ; 
 int WIPHY_FLAG_SUPPORTS_FW_ROAM ; 
 int cfg80211_connect (struct net_device*,struct net_device*,struct cfg80211_connect_params*,struct cfg80211_cached_keys*) ; 
 TYPE_2__* ieee80211_get_channel (struct wiphy*,void*) ; 
 int /*<<< orphan*/  is_valid_ie_attr (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct cfg80211_cached_keys*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  memset (struct cfg80211_connect_params*,int /*<<< orphan*/ ,int) ; 
 int nl80211_crypto_settings (struct net_device*,struct genl_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct cfg80211_cached_keys* nl80211_parse_connkeys (struct net_device*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl80211_valid_auth_type (struct net_device*,void*,int /*<<< orphan*/ ) ; 
 void* nla_data (scalar_t__) ; 
 scalar_t__ nla_get_flag (scalar_t__) ; 
 int nla_get_u16 (scalar_t__) ; 
 void* nla_get_u32 (scalar_t__) ; 
 void* nla_len (scalar_t__) ; 

__attribute__((used)) static int nl80211_connect(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct cfg80211_connect_params connect;
	struct wiphy *wiphy;
	struct cfg80211_cached_keys *connkeys = NULL;
	int err;

	memset(&connect, 0, sizeof(connect));

	if (!is_valid_ie_attr(info->attrs[NL80211_ATTR_IE]))
		return -EINVAL;

	if (!info->attrs[NL80211_ATTR_SSID] ||
	    !nla_len(info->attrs[NL80211_ATTR_SSID]))
		return -EINVAL;

	if (info->attrs[NL80211_ATTR_AUTH_TYPE]) {
		connect.auth_type =
			nla_get_u32(info->attrs[NL80211_ATTR_AUTH_TYPE]);
		if (!nl80211_valid_auth_type(rdev, connect.auth_type,
					     NL80211_CMD_CONNECT))
			return -EINVAL;
	} else
		connect.auth_type = NL80211_AUTHTYPE_AUTOMATIC;

	connect.privacy = info->attrs[NL80211_ATTR_PRIVACY];

	err = nl80211_crypto_settings(rdev, info, &connect.crypto,
				      NL80211_MAX_NR_CIPHER_SUITES);
	if (err)
		return err;

	if (dev->ieee80211_ptr->iftype != NL80211_IFTYPE_STATION &&
	    dev->ieee80211_ptr->iftype != NL80211_IFTYPE_P2P_CLIENT)
		return -EOPNOTSUPP;

	wiphy = &rdev->wiphy;

	connect.bg_scan_period = -1;
	if (info->attrs[NL80211_ATTR_BG_SCAN_PERIOD] &&
		(wiphy->flags & WIPHY_FLAG_SUPPORTS_FW_ROAM)) {
		connect.bg_scan_period =
			nla_get_u16(info->attrs[NL80211_ATTR_BG_SCAN_PERIOD]);
	}

	if (info->attrs[NL80211_ATTR_MAC])
		connect.bssid = nla_data(info->attrs[NL80211_ATTR_MAC]);
	connect.ssid = nla_data(info->attrs[NL80211_ATTR_SSID]);
	connect.ssid_len = nla_len(info->attrs[NL80211_ATTR_SSID]);

	if (info->attrs[NL80211_ATTR_IE]) {
		connect.ie = nla_data(info->attrs[NL80211_ATTR_IE]);
		connect.ie_len = nla_len(info->attrs[NL80211_ATTR_IE]);
	}

	if (info->attrs[NL80211_ATTR_USE_MFP]) {
		connect.mfp = nla_get_u32(info->attrs[NL80211_ATTR_USE_MFP]);
		if (connect.mfp != NL80211_MFP_REQUIRED &&
		    connect.mfp != NL80211_MFP_NO)
			return -EINVAL;
	} else {
		connect.mfp = NL80211_MFP_NO;
	}

	if (info->attrs[NL80211_ATTR_WIPHY_FREQ]) {
		connect.channel =
			ieee80211_get_channel(wiphy,
			    nla_get_u32(info->attrs[NL80211_ATTR_WIPHY_FREQ]));
		if (!connect.channel ||
		    connect.channel->flags & IEEE80211_CHAN_DISABLED)
			return -EINVAL;
	}

	if (connect.privacy && info->attrs[NL80211_ATTR_KEYS]) {
		connkeys = nl80211_parse_connkeys(rdev,
					  info->attrs[NL80211_ATTR_KEYS], NULL);
		if (IS_ERR(connkeys))
			return PTR_ERR(connkeys);
	}

	if (nla_get_flag(info->attrs[NL80211_ATTR_DISABLE_HT]))
		connect.flags |= ASSOC_REQ_DISABLE_HT;

	if (info->attrs[NL80211_ATTR_HT_CAPABILITY_MASK])
		memcpy(&connect.ht_capa_mask,
		       nla_data(info->attrs[NL80211_ATTR_HT_CAPABILITY_MASK]),
		       sizeof(connect.ht_capa_mask));

	if (info->attrs[NL80211_ATTR_HT_CAPABILITY]) {
		if (!info->attrs[NL80211_ATTR_HT_CAPABILITY_MASK]) {
			kfree(connkeys);
			return -EINVAL;
		}
		memcpy(&connect.ht_capa,
		       nla_data(info->attrs[NL80211_ATTR_HT_CAPABILITY]),
		       sizeof(connect.ht_capa));
	}

	if (nla_get_flag(info->attrs[NL80211_ATTR_DISABLE_VHT]))
		connect.flags |= ASSOC_REQ_DISABLE_VHT;

	if (info->attrs[NL80211_ATTR_VHT_CAPABILITY_MASK])
		memcpy(&connect.vht_capa_mask,
		       nla_data(info->attrs[NL80211_ATTR_VHT_CAPABILITY_MASK]),
		       sizeof(connect.vht_capa_mask));

	if (info->attrs[NL80211_ATTR_VHT_CAPABILITY]) {
		if (!info->attrs[NL80211_ATTR_VHT_CAPABILITY_MASK]) {
			kfree(connkeys);
			return -EINVAL;
		}
		memcpy(&connect.vht_capa,
		       nla_data(info->attrs[NL80211_ATTR_VHT_CAPABILITY]),
		       sizeof(connect.vht_capa));
	}

	err = cfg80211_connect(rdev, dev, &connect, connkeys);
	if (err)
		kfree(connkeys);
	return err;
}