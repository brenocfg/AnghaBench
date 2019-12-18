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
typedef  int u32 ;
struct wiphy {TYPE_1__** bands; } ;
struct ieee80211_sta_vht_cap {int cap; int /*<<< orphan*/  vht_supported; } ;
struct ieee80211_sta_ht_cap {int cap; int /*<<< orphan*/  ht_supported; } ;
struct cfg80211_chan_def {int width; int center_freq1; int center_freq2; TYPE_2__* chan; } ;
struct TYPE_4__ {size_t band; int center_freq; int flags; } ;
struct TYPE_3__ {struct ieee80211_sta_vht_cap vht_cap; struct ieee80211_sta_ht_cap ht_cap; } ;

/* Variables and functions */
 int IEEE80211_CHAN_NO_160MHZ ; 
 int IEEE80211_CHAN_NO_80MHZ ; 
 int IEEE80211_CHAN_NO_HT40MINUS ; 
 int IEEE80211_CHAN_NO_HT40PLUS ; 
 int IEEE80211_CHAN_NO_OFDM ; 
 int IEEE80211_HT_CAP_40MHZ_INTOLERANT ; 
 int IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 int IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ ; 
 int IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ ; 
#define  NL80211_CHAN_WIDTH_160 133 
#define  NL80211_CHAN_WIDTH_20 132 
#define  NL80211_CHAN_WIDTH_20_NOHT 131 
#define  NL80211_CHAN_WIDTH_40 130 
#define  NL80211_CHAN_WIDTH_80 129 
#define  NL80211_CHAN_WIDTH_80P80 128 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cfg80211_chandef_valid (struct cfg80211_chan_def const*) ; 
 int cfg80211_secondary_chans_ok (struct wiphy*,int,int,int) ; 

bool cfg80211_chandef_usable(struct wiphy *wiphy,
			     const struct cfg80211_chan_def *chandef,
			     u32 prohibited_flags)
{
	struct ieee80211_sta_ht_cap *ht_cap;
	struct ieee80211_sta_vht_cap *vht_cap;
	u32 width, control_freq;

	if (WARN_ON(!cfg80211_chandef_valid(chandef)))
		return false;

	ht_cap = &wiphy->bands[chandef->chan->band]->ht_cap;
	vht_cap = &wiphy->bands[chandef->chan->band]->vht_cap;

	control_freq = chandef->chan->center_freq;

	switch (chandef->width) {
	case NL80211_CHAN_WIDTH_20:
		if (!ht_cap->ht_supported)
			return false;
	case NL80211_CHAN_WIDTH_20_NOHT:
		width = 20;
		break;
	case NL80211_CHAN_WIDTH_40:
		width = 40;
		if (!ht_cap->ht_supported)
			return false;
		if (!(ht_cap->cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40) ||
		    ht_cap->cap & IEEE80211_HT_CAP_40MHZ_INTOLERANT)
			return false;
		if (chandef->center_freq1 < control_freq &&
		    chandef->chan->flags & IEEE80211_CHAN_NO_HT40MINUS)
			return false;
		if (chandef->center_freq1 > control_freq &&
		    chandef->chan->flags & IEEE80211_CHAN_NO_HT40PLUS)
			return false;
		break;
	case NL80211_CHAN_WIDTH_80P80:
		if (!(vht_cap->cap & IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ))
			return false;
	case NL80211_CHAN_WIDTH_80:
		if (!vht_cap->vht_supported)
			return false;
		prohibited_flags |= IEEE80211_CHAN_NO_80MHZ;
		width = 80;
		break;
	case NL80211_CHAN_WIDTH_160:
		if (!vht_cap->vht_supported)
			return false;
		if (!(vht_cap->cap & IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ))
			return false;
		prohibited_flags |= IEEE80211_CHAN_NO_160MHZ;
		width = 160;
		break;
	default:
		WARN_ON_ONCE(1);
		return false;
	}

	/*
	 * TODO: What if there are only certain 80/160/80+80 MHz channels
	 *	 allowed by the driver, or only certain combinations?
	 *	 For 40 MHz the driver can set the NO_HT40 flags, but for
	 *	 80/160 MHz and in particular 80+80 MHz this isn't really
	 *	 feasible and we only have NO_80MHZ/NO_160MHZ so far but
	 *	 no way to cover 80+80 MHz or more complex restrictions.
	 *	 Note that such restrictions also need to be advertised to
	 *	 userspace, for example for P2P channel selection.
	 */

	if (width > 20)
		prohibited_flags |= IEEE80211_CHAN_NO_OFDM;

	if (!cfg80211_secondary_chans_ok(wiphy, chandef->center_freq1,
					 width, prohibited_flags))
		return false;

	if (!chandef->center_freq2)
		return true;
	return cfg80211_secondary_chans_ok(wiphy, chandef->center_freq2,
					   width, prohibited_flags);
}