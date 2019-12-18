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
struct wireless_dev {scalar_t__ sme_state; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  wiphy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct ieee80211_channel {int dummy; } ;
struct cfg80211_bss {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  CFG80211_DEV_WARN_ON (int) ; 
 scalar_t__ CFG80211_SME_CONNECTED ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WLAN_CAPABILITY_ESS ; 
 struct cfg80211_bss* cfg80211_get_bss (int /*<<< orphan*/ ,struct ieee80211_channel*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_roamed_bss (struct net_device*,struct cfg80211_bss*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 

void cfg80211_roamed(struct net_device *dev,
		     struct ieee80211_channel *channel,
		     const u8 *bssid,
		     const u8 *req_ie, size_t req_ie_len,
		     const u8 *resp_ie, size_t resp_ie_len, gfp_t gfp)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_bss *bss;

	CFG80211_DEV_WARN_ON(wdev->sme_state != CFG80211_SME_CONNECTED);

	bss = cfg80211_get_bss(wdev->wiphy, channel, bssid, wdev->ssid,
			       wdev->ssid_len, WLAN_CAPABILITY_ESS,
			       WLAN_CAPABILITY_ESS);
	if (WARN_ON(!bss))
		return;

	cfg80211_roamed_bss(dev, bss, req_ie, req_ie_len, resp_ie,
			    resp_ie_len, gfp);
}