#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  void* u16 ;
struct wiphy {scalar_t__ signal_type; } ;
struct ieee80211_channel {int dummy; } ;
struct cfg80211_bss {int signal; int capability; int /*<<< orphan*/  ies; int /*<<< orphan*/  beacon_ies; void* beacon_interval; struct ieee80211_channel* channel; int /*<<< orphan*/  bssid; } ;
struct cfg80211_internal_bss {struct cfg80211_bss pub; } ;
struct cfg80211_bss_ies {size_t len; int /*<<< orphan*/  data; int /*<<< orphan*/  tsf; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ CFG80211_SIGNAL_TYPE_UNSPEC ; 
 size_t ETH_ALEN ; 
 scalar_t__ WARN_ON (int) ; 
 int WLAN_CAPABILITY_ESS ; 
 struct cfg80211_internal_bss* cfg80211_bss_update (int /*<<< orphan*/ ,struct cfg80211_internal_bss*) ; 
 struct ieee80211_channel* cfg80211_get_bss_channel (struct wiphy*,int /*<<< orphan*/  const*,size_t,struct ieee80211_channel*) ; 
 struct cfg80211_bss_ies* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct cfg80211_bss_ies*) ; 
 int /*<<< orphan*/  regulatory_hint_found_beacon (struct wiphy*,struct ieee80211_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_cfg80211_return_bss (struct cfg80211_bss*) ; 
 int /*<<< orphan*/  wiphy_to_dev (struct wiphy*) ; 

struct cfg80211_bss*
cfg80211_inform_bss(struct wiphy *wiphy,
		    struct ieee80211_channel *channel,
		    const u8 *bssid, u64 tsf, u16 capability,
		    u16 beacon_interval, const u8 *ie, size_t ielen,
		    s32 signal, gfp_t gfp)
{
	struct cfg80211_bss_ies *ies;
	struct cfg80211_internal_bss tmp = {}, *res;

	if (WARN_ON(!wiphy))
		return NULL;

	if (WARN_ON(wiphy->signal_type == CFG80211_SIGNAL_TYPE_UNSPEC &&
			(signal < 0 || signal > 100)))
		return NULL;

	channel = cfg80211_get_bss_channel(wiphy, ie, ielen, channel);
	if (!channel)
		return NULL;

	memcpy(tmp.pub.bssid, bssid, ETH_ALEN);
	tmp.pub.channel = channel;
	tmp.pub.signal = signal;
	tmp.pub.beacon_interval = beacon_interval;
	tmp.pub.capability = capability;
	/*
	 * Since we do not know here whether the IEs are from a Beacon or Probe
	 * Response frame, we need to pick one of the options and only use it
	 * with the driver that does not provide the full Beacon/Probe Response
	 * frame. Use Beacon frame pointer to avoid indicating that this should
	 * override the IEs pointer should we have received an earlier
	 * indication of Probe Response data.
	 */
	ies = kmalloc(sizeof(*ies) + ielen, gfp);
	if (!ies)
		return NULL;
	ies->len = ielen;
	ies->tsf = tsf;
	memcpy(ies->data, ie, ielen);

	rcu_assign_pointer(tmp.pub.beacon_ies, ies);
	rcu_assign_pointer(tmp.pub.ies, ies);

	res = cfg80211_bss_update(wiphy_to_dev(wiphy), &tmp);
	if (!res)
		return NULL;

	if (res->pub.capability & WLAN_CAPABILITY_ESS)
		regulatory_hint_found_beacon(wiphy, channel, gfp);

	trace_cfg80211_return_bss(&res->pub);
	/* cfg80211_bss_update gives us a referenced result */
	return &res->pub;
}