#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct genl_info {scalar_t__* attrs; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; } ;
struct cfg80211_chan_def {void* center_freq2; void* center_freq1; void* width; TYPE_1__* chan; } ;
typedef  enum nl80211_channel_type { ____Placeholder_nl80211_channel_type } nl80211_channel_type ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int IEEE80211_CHAN_DISABLED ; 
 size_t NL80211_ATTR_CENTER_FREQ1 ; 
 size_t NL80211_ATTR_CENTER_FREQ2 ; 
 size_t NL80211_ATTR_CHANNEL_WIDTH ; 
 size_t NL80211_ATTR_WIPHY_CHANNEL_TYPE ; 
 size_t NL80211_ATTR_WIPHY_FREQ ; 
#define  NL80211_CHAN_HT20 131 
#define  NL80211_CHAN_HT40MINUS 130 
#define  NL80211_CHAN_HT40PLUS 129 
#define  NL80211_CHAN_NO_HT 128 
 void* NL80211_CHAN_WIDTH_20_NOHT ; 
 int /*<<< orphan*/  cfg80211_chandef_create (struct cfg80211_chan_def*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  cfg80211_chandef_usable (int /*<<< orphan*/ *,struct cfg80211_chan_def*,int) ; 
 int /*<<< orphan*/  cfg80211_chandef_valid (struct cfg80211_chan_def*) ; 
 TYPE_1__* ieee80211_get_channel (int /*<<< orphan*/ *,void*) ; 
 void* nla_get_u32 (scalar_t__) ; 

__attribute__((used)) static int nl80211_parse_chandef(struct cfg80211_registered_device *rdev,
				 struct genl_info *info,
				 struct cfg80211_chan_def *chandef)
{
	u32 control_freq;

	if (!info->attrs[NL80211_ATTR_WIPHY_FREQ])
		return -EINVAL;

	control_freq = nla_get_u32(info->attrs[NL80211_ATTR_WIPHY_FREQ]);

	chandef->chan = ieee80211_get_channel(&rdev->wiphy, control_freq);
	chandef->width = NL80211_CHAN_WIDTH_20_NOHT;
	chandef->center_freq1 = control_freq;
	chandef->center_freq2 = 0;

	/* Primary channel not allowed */
	if (!chandef->chan || chandef->chan->flags & IEEE80211_CHAN_DISABLED)
		return -EINVAL;

	if (info->attrs[NL80211_ATTR_WIPHY_CHANNEL_TYPE]) {
		enum nl80211_channel_type chantype;

		chantype = nla_get_u32(
				info->attrs[NL80211_ATTR_WIPHY_CHANNEL_TYPE]);

		switch (chantype) {
		case NL80211_CHAN_NO_HT:
		case NL80211_CHAN_HT20:
		case NL80211_CHAN_HT40PLUS:
		case NL80211_CHAN_HT40MINUS:
			cfg80211_chandef_create(chandef, chandef->chan,
						chantype);
			break;
		default:
			return -EINVAL;
		}
	} else if (info->attrs[NL80211_ATTR_CHANNEL_WIDTH]) {
		chandef->width =
			nla_get_u32(info->attrs[NL80211_ATTR_CHANNEL_WIDTH]);
		if (info->attrs[NL80211_ATTR_CENTER_FREQ1])
			chandef->center_freq1 =
				nla_get_u32(
					info->attrs[NL80211_ATTR_CENTER_FREQ1]);
		if (info->attrs[NL80211_ATTR_CENTER_FREQ2])
			chandef->center_freq2 =
				nla_get_u32(
					info->attrs[NL80211_ATTR_CENTER_FREQ2]);
	}

	if (!cfg80211_chandef_valid(chandef))
		return -EINVAL;

	if (!cfg80211_chandef_usable(&rdev->wiphy, chandef,
				     IEEE80211_CHAN_DISABLED))
		return -EINVAL;

	return 0;
}