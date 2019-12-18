#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_8__ {int flags; } ;
struct wiphy {int interface_modes; int flags; struct ieee80211_supported_band** bands; TYPE_3__* addresses; int /*<<< orphan*/  perm_addr; scalar_t__ max_acl_mac_addrs; int /*<<< orphan*/  n_addresses; scalar_t__ ap_sme_capa; TYPE_1__ wowlan; } ;
struct regulatory_request {char* alpha2; int /*<<< orphan*/  initiator; int /*<<< orphan*/  wiphy_idx; } ;
struct TYPE_11__ {int /*<<< orphan*/  cap; scalar_t__ ht_supported; } ;
struct ieee80211_supported_band {int band; int n_channels; int n_bitrates; TYPE_5__* channels; TYPE_4__ ht_cap; } ;
struct TYPE_13__ {scalar_t__ pattern_min_len; scalar_t__ pattern_max_len; scalar_t__ n_patterns; } ;
struct TYPE_14__ {int registered; int /*<<< orphan*/ * debugfsdir; int /*<<< orphan*/  dev; TYPE_6__ wowlan; } ;
struct cfg80211_registered_device {TYPE_7__ wiphy; int /*<<< orphan*/  list; int /*<<< orphan*/  rfkill; TYPE_2__* ops; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;
struct TYPE_12__ {int band; int /*<<< orphan*/  max_power; int /*<<< orphan*/  orig_mpwr; int /*<<< orphan*/  orig_mag; int /*<<< orphan*/  flags; int /*<<< orphan*/  orig_flags; } ;
struct TYPE_10__ {int /*<<< orphan*/  addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  set_mac_acl; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int IEEE80211_BAND_2GHZ ; 
 int IEEE80211_BAND_60GHZ ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SGI_40 ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 int IEEE80211_NUM_BANDS ; 
 int /*<<< orphan*/  INT_MAX ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NL80211_REGDOM_SET_BY_DRIVER ; 
 int NUM_NL80211_IFTYPES ; 
 scalar_t__ WARN_ON (int) ; 
 int WIPHY_FLAG_CUSTOM_REGULATORY ; 
 int WIPHY_FLAG_HAVE_AP_SME ; 
 int WIPHY_WOWLAN_GTK_REKEY_FAILURE ; 
 int WIPHY_WOWLAN_SUPPORTS_GTK_REKEY ; 
 int /*<<< orphan*/  cfg80211_debugfs_rdev_add (struct cfg80211_registered_device*) ; 
 scalar_t__ cfg80211_disable_40mhz_24ghz ; 
 int /*<<< orphan*/  cfg80211_mutex ; 
 int /*<<< orphan*/  cfg80211_rdev_list ; 
 int /*<<< orphan*/  cfg80211_rdev_list_generation ; 
 int /*<<< orphan*/ * debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_wiphy_idx (struct wiphy*) ; 
 int /*<<< orphan*/  ieee80211_debugfs_dir ; 
 int /*<<< orphan*/  ieee80211_set_bitrate_flags (struct wiphy*) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl80211_send_reg_change_event (struct regulatory_request*) ; 
 int rfkill_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  wiphy_name (TYPE_7__*) ; 
 int /*<<< orphan*/  wiphy_regulatory_deregister (struct wiphy*) ; 
 int /*<<< orphan*/  wiphy_regulatory_register (struct wiphy*) ; 
 struct cfg80211_registered_device* wiphy_to_dev (struct wiphy*) ; 
 int wiphy_verify_combinations (struct wiphy*) ; 

int wiphy_register(struct wiphy *wiphy)
{
	struct cfg80211_registered_device *rdev = wiphy_to_dev(wiphy);
	int res;
	enum ieee80211_band band;
	struct ieee80211_supported_band *sband;
	bool have_band = false;
	int i;
	u16 ifmodes = wiphy->interface_modes;

#ifdef CONFIG_PM
	if (WARN_ON((wiphy->wowlan.flags & WIPHY_WOWLAN_GTK_REKEY_FAILURE) &&
		    !(wiphy->wowlan.flags & WIPHY_WOWLAN_SUPPORTS_GTK_REKEY)))
		return -EINVAL;
#endif

	if (WARN_ON(wiphy->ap_sme_capa &&
		    !(wiphy->flags & WIPHY_FLAG_HAVE_AP_SME)))
		return -EINVAL;

	if (WARN_ON(wiphy->addresses && !wiphy->n_addresses))
		return -EINVAL;

	if (WARN_ON(wiphy->addresses &&
		    !is_zero_ether_addr(wiphy->perm_addr) &&
		    memcmp(wiphy->perm_addr, wiphy->addresses[0].addr,
			   ETH_ALEN)))
		return -EINVAL;

	if (WARN_ON(wiphy->max_acl_mac_addrs &&
		    (!(wiphy->flags & WIPHY_FLAG_HAVE_AP_SME) ||
		     !rdev->ops->set_mac_acl)))
		return -EINVAL;

	if (wiphy->addresses)
		memcpy(wiphy->perm_addr, wiphy->addresses[0].addr, ETH_ALEN);

	/* sanity check ifmodes */
	WARN_ON(!ifmodes);
	ifmodes &= ((1 << NUM_NL80211_IFTYPES) - 1) & ~1;
	if (WARN_ON(ifmodes != wiphy->interface_modes))
		wiphy->interface_modes = ifmodes;

	res = wiphy_verify_combinations(wiphy);
	if (res)
		return res;

	/* sanity check supported bands/channels */
	for (band = 0; band < IEEE80211_NUM_BANDS; band++) {
		sband = wiphy->bands[band];
		if (!sband)
			continue;

		sband->band = band;
		if (WARN_ON(!sband->n_channels))
			return -EINVAL;
		/*
		 * on 60gHz band, there are no legacy rates, so
		 * n_bitrates is 0
		 */
		if (WARN_ON(band != IEEE80211_BAND_60GHZ &&
			    !sband->n_bitrates))
			return -EINVAL;

		/*
		 * Since cfg80211_disable_40mhz_24ghz is global, we can
		 * modify the sband's ht data even if the driver uses a
		 * global structure for that.
		 */
		if (cfg80211_disable_40mhz_24ghz &&
		    band == IEEE80211_BAND_2GHZ &&
		    sband->ht_cap.ht_supported) {
			sband->ht_cap.cap &= ~IEEE80211_HT_CAP_SUP_WIDTH_20_40;
			sband->ht_cap.cap &= ~IEEE80211_HT_CAP_SGI_40;
		}

		/*
		 * Since we use a u32 for rate bitmaps in
		 * ieee80211_get_response_rate, we cannot
		 * have more than 32 legacy rates.
		 */
		if (WARN_ON(sband->n_bitrates > 32))
			return -EINVAL;

		for (i = 0; i < sband->n_channels; i++) {
			sband->channels[i].orig_flags =
				sband->channels[i].flags;
			sband->channels[i].orig_mag = INT_MAX;
			sband->channels[i].orig_mpwr =
				sband->channels[i].max_power;
			sband->channels[i].band = band;
		}

		have_band = true;
	}

	if (!have_band) {
		WARN_ON(1);
		return -EINVAL;
	}

#ifdef CONFIG_PM
	if (rdev->wiphy.wowlan.n_patterns) {
		if (WARN_ON(!rdev->wiphy.wowlan.pattern_min_len ||
			    rdev->wiphy.wowlan.pattern_min_len >
			    rdev->wiphy.wowlan.pattern_max_len))
			return -EINVAL;
	}
#endif

	/* check and set up bitrates */
	ieee80211_set_bitrate_flags(wiphy);

	mutex_lock(&cfg80211_mutex);

	res = device_add(&rdev->wiphy.dev);
	if (res) {
		mutex_unlock(&cfg80211_mutex);
		return res;
	}

	/* set up regulatory info */
	wiphy_regulatory_register(wiphy);

	list_add_rcu(&rdev->list, &cfg80211_rdev_list);
	cfg80211_rdev_list_generation++;

	/* add to debugfs */
	rdev->wiphy.debugfsdir =
		debugfs_create_dir(wiphy_name(&rdev->wiphy),
				   ieee80211_debugfs_dir);
	if (IS_ERR(rdev->wiphy.debugfsdir))
		rdev->wiphy.debugfsdir = NULL;

	if (wiphy->flags & WIPHY_FLAG_CUSTOM_REGULATORY) {
		struct regulatory_request request;

		request.wiphy_idx = get_wiphy_idx(wiphy);
		request.initiator = NL80211_REGDOM_SET_BY_DRIVER;
		request.alpha2[0] = '9';
		request.alpha2[1] = '9';

		nl80211_send_reg_change_event(&request);
	}

	cfg80211_debugfs_rdev_add(rdev);
	mutex_unlock(&cfg80211_mutex);

	/*
	 * due to a locking dependency this has to be outside of the
	 * cfg80211_mutex lock
	 */
	res = rfkill_register(rdev->rfkill);
	if (res) {
		device_del(&rdev->wiphy.dev);

		mutex_lock(&cfg80211_mutex);
		debugfs_remove_recursive(rdev->wiphy.debugfsdir);
		list_del_rcu(&rdev->list);
		wiphy_regulatory_deregister(wiphy);
		mutex_unlock(&cfg80211_mutex);
		return res;
	}

	rtnl_lock();
	rdev->wiphy.registered = true;
	rtnl_unlock();
	return 0;
}