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
typedef  int /*<<< orphan*/  wstats ;
typedef  int /*<<< orphan*/  u8 ;
struct wireless_dev {scalar_t__ iftype; TYPE_3__* current_bss; int /*<<< orphan*/  wiphy; } ;
struct station_info {int filled; int signal; int /*<<< orphan*/  tx_failed; int /*<<< orphan*/  rx_dropped_misc; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct TYPE_12__ {int /*<<< orphan*/  retries; int /*<<< orphan*/  misc; } ;
struct TYPE_11__ {int level; int qual; int /*<<< orphan*/  updated; } ;
struct iw_statistics {TYPE_6__ discard; TYPE_5__ qual; } ;
struct TYPE_10__ {int signal_type; } ;
struct cfg80211_registered_device {TYPE_4__ wiphy; TYPE_1__* ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_9__ {TYPE_2__ pub; } ;
struct TYPE_7__ {int /*<<< orphan*/  get_station; } ;

/* Variables and functions */
#define  CFG80211_SIGNAL_TYPE_MBM 129 
#define  CFG80211_SIGNAL_TYPE_UNSPEC 128 
 int ETH_ALEN ; 
 int /*<<< orphan*/  IW_QUAL_DBM ; 
 int /*<<< orphan*/  IW_QUAL_LEVEL_INVALID ; 
 int /*<<< orphan*/  IW_QUAL_LEVEL_UPDATED ; 
 int /*<<< orphan*/  IW_QUAL_NOISE_INVALID ; 
 int /*<<< orphan*/  IW_QUAL_QUAL_INVALID ; 
 int /*<<< orphan*/  IW_QUAL_QUAL_UPDATED ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int STATION_INFO_RX_DROP_MISC ; 
 int STATION_INFO_SIGNAL ; 
 int STATION_INFO_TX_FAILED ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct iw_statistics*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rdev_get_station (struct cfg80211_registered_device*,struct net_device*,int /*<<< orphan*/ *,struct station_info*) ; 
 int /*<<< orphan*/  wdev_lock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_unlock (struct wireless_dev*) ; 
 struct cfg80211_registered_device* wiphy_to_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct iw_statistics *cfg80211_wireless_stats(struct net_device *dev)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_registered_device *rdev = wiphy_to_dev(wdev->wiphy);
	/* we are under RTNL - globally locked - so can use static structs */
	static struct iw_statistics wstats;
	static struct station_info sinfo;
	u8 bssid[ETH_ALEN];

	if (dev->ieee80211_ptr->iftype != NL80211_IFTYPE_STATION)
		return NULL;

	if (!rdev->ops->get_station)
		return NULL;

	/* Grab BSSID of current BSS, if any */
	wdev_lock(wdev);
	if (!wdev->current_bss) {
		wdev_unlock(wdev);
		return NULL;
	}
	memcpy(bssid, wdev->current_bss->pub.bssid, ETH_ALEN);
	wdev_unlock(wdev);

	if (rdev_get_station(rdev, dev, bssid, &sinfo))
		return NULL;

	memset(&wstats, 0, sizeof(wstats));

	switch (rdev->wiphy.signal_type) {
	case CFG80211_SIGNAL_TYPE_MBM:
		if (sinfo.filled & STATION_INFO_SIGNAL) {
			int sig = sinfo.signal;
			wstats.qual.updated |= IW_QUAL_LEVEL_UPDATED;
			wstats.qual.updated |= IW_QUAL_QUAL_UPDATED;
			wstats.qual.updated |= IW_QUAL_DBM;
			wstats.qual.level = sig;
			if (sig < -110)
				sig = -110;
			else if (sig > -40)
				sig = -40;
			wstats.qual.qual = sig + 110;
			break;
		}
	case CFG80211_SIGNAL_TYPE_UNSPEC:
		if (sinfo.filled & STATION_INFO_SIGNAL) {
			wstats.qual.updated |= IW_QUAL_LEVEL_UPDATED;
			wstats.qual.updated |= IW_QUAL_QUAL_UPDATED;
			wstats.qual.level = sinfo.signal;
			wstats.qual.qual = sinfo.signal;
			break;
		}
	default:
		wstats.qual.updated |= IW_QUAL_LEVEL_INVALID;
		wstats.qual.updated |= IW_QUAL_QUAL_INVALID;
	}

	wstats.qual.updated |= IW_QUAL_NOISE_INVALID;
	if (sinfo.filled & STATION_INFO_RX_DROP_MISC)
		wstats.discard.misc = sinfo.rx_dropped_misc;
	if (sinfo.filled & STATION_INFO_TX_FAILED)
		wstats.discard.retries = sinfo.tx_failed;

	return &wstats;
}