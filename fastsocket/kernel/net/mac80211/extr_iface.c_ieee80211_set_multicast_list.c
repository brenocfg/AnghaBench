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
struct net_device {int flags; int /*<<< orphan*/  mc_count; int /*<<< orphan*/  mc_list; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  mc; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct ieee80211_sub_if_data {int flags; TYPE_1__ vif; struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  reconfig_filter; int /*<<< orphan*/  hw; int /*<<< orphan*/  filter_lock; int /*<<< orphan*/  mc_count; int /*<<< orphan*/  mc_list; int /*<<< orphan*/  iff_promiscs; int /*<<< orphan*/  iff_allmultis; } ;

/* Variables and functions */
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int IEEE80211_SDATA_ALLMULTI ; 
 int IEEE80211_SDATA_PROMISC ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_AP_VLAN ; 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
 int /*<<< orphan*/  __dev_addr_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __hw_addr_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drv_set_multicast_list (struct ieee80211_local*,struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ieee80211_set_multicast_list(struct net_device *dev)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	struct ieee80211_local *local = sdata->local;
	int allmulti, promisc, sdata_allmulti, sdata_promisc;

	allmulti = !!(dev->flags & IFF_ALLMULTI);
	promisc = !!(dev->flags & IFF_PROMISC);
	sdata_allmulti = !!(sdata->flags & IEEE80211_SDATA_ALLMULTI);
	sdata_promisc = !!(sdata->flags & IEEE80211_SDATA_PROMISC);

	if (allmulti != sdata_allmulti) {
		if (dev->flags & IFF_ALLMULTI)
			atomic_inc(&local->iff_allmultis);
		else
			atomic_dec(&local->iff_allmultis);
		sdata->flags ^= IEEE80211_SDATA_ALLMULTI;
	}

	if (promisc != sdata_promisc) {
		if (dev->flags & IFF_PROMISC)
			atomic_inc(&local->iff_promiscs);
		else
			atomic_dec(&local->iff_promiscs);
		sdata->flags ^= IEEE80211_SDATA_PROMISC;
	}

	/*
	 * TODO: If somebody needs this on AP interfaces,
	 *	 it can be enabled easily but multicast
	 *	 addresses from VLANs need to be synced.
	 */
	if (sdata->vif.type != NL80211_IFTYPE_MONITOR &&
	    sdata->vif.type != NL80211_IFTYPE_AP_VLAN &&
	    sdata->vif.type != NL80211_IFTYPE_AP)
#if 0 /* Not in RHEL */
		drv_set_multicast_list(local, sdata, &dev->mc);
#else
		drv_set_multicast_list(local, sdata, dev->mc_count,
				       dev->mc_list);
#endif

	spin_lock_bh(&local->filter_lock);
#if 0 /* Not in RHEL */
	__hw_addr_sync(&local->mc_list, &dev->mc, dev->addr_len);
#else
	__dev_addr_sync(&local->mc_list, &local->mc_count,
			&dev->mc_list, &dev->mc_count);
#endif
	spin_unlock_bh(&local->filter_lock);
	ieee80211_queue_work(&local->hw, &local->reconfig_filter);
}