#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct wireless_dev {int /*<<< orphan*/  use_4addr; TYPE_8__* wiphy; int /*<<< orphan*/  address; } ;
struct vif_params {int /*<<< orphan*/  use_4addr; } ;
struct net_device {int /*<<< orphan*/  features; struct wireless_dev* ieee80211_ptr; int /*<<< orphan*/  name; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  perm_addr; int /*<<< orphan*/  needed_tailroom; scalar_t__ needed_headroom; } ;
struct TYPE_12__ {int /*<<< orphan*/  rx_mask; } ;
struct TYPE_13__ {TYPE_3__ mcs; } ;
struct ieee80211_supported_band {int n_bitrates; TYPE_4__ ht_cap; } ;
struct TYPE_14__ {int /*<<< orphan*/  use_4addr; } ;
struct TYPE_15__ {TYPE_5__ mgd; } ;
struct TYPE_10__ {int /*<<< orphan*/  addr; } ;
struct ieee80211_sub_if_data {int* rc_rateidx_mask; struct wireless_dev wdev; int /*<<< orphan*/  list; TYPE_6__ u; int /*<<< orphan*/  user_power_level; int /*<<< orphan*/  ap_power_level; int /*<<< orphan*/ * rc_rateidx_mcs_mask; int /*<<< orphan*/  dec_tailroom_needed_wk; int /*<<< orphan*/  dfs_cac_timer_work; int /*<<< orphan*/  cleanup_stations_wk; int /*<<< orphan*/  cleanup_stations; int /*<<< orphan*/  cleanup_stations_lock; int /*<<< orphan*/  key_list; TYPE_2__* fragments; struct ieee80211_local* local; struct net_device* dev; int /*<<< orphan*/  name; TYPE_1__ vif; } ;
struct TYPE_16__ {int queues; int /*<<< orphan*/  netdev_features; TYPE_8__* wiphy; scalar_t__ vif_data_size; } ;
struct ieee80211_local {int /*<<< orphan*/  iflist_mtx; int /*<<< orphan*/  interfaces; TYPE_7__ hw; int /*<<< orphan*/  user_power_level; scalar_t__ tx_headroom; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;
struct TYPE_17__ {struct ieee80211_supported_band** bands; } ;
struct TYPE_11__ {int /*<<< orphan*/  skb_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IEEE80211_ENCRYPT_HEADROOM ; 
 int /*<<< orphan*/  IEEE80211_ENCRYPT_TAILROOM ; 
 int IEEE80211_FRAGMENT_MAX ; 
 int IEEE80211_NUM_ACS ; 
 int IEEE80211_NUM_BANDS ; 
 int /*<<< orphan*/  IEEE80211_UNSET_POWER_LEVEL ; 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NL80211_IFTYPE_P2P_DEVICE ; 
 int NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ ) ; 
 struct net_device* alloc_netdev_mqs (scalar_t__,char const*,int /*<<< orphan*/ ,int,int) ; 
 int dev_alloc_name (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net_set (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  ieee80211_assign_perm_addr (struct ieee80211_local*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_cleanup_sdata_stas_wk ; 
 int /*<<< orphan*/  ieee80211_delayed_tailroom_dec ; 
 int /*<<< orphan*/  ieee80211_dfs_cac_timer_work ; 
 int /*<<< orphan*/  ieee80211_if_setup ; 
 int /*<<< orphan*/  ieee80211_set_default_queues (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_setup_sdata (struct ieee80211_sub_if_data*,int) ; 
 struct ieee80211_sub_if_data* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ieee80211_sub_if_data* netdev_priv (struct net_device*) ; 
 int register_netdevice (struct net_device*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  wiphy_dev (TYPE_8__*) ; 
 int /*<<< orphan*/  wiphy_net (TYPE_8__*) ; 

int ieee80211_if_add(struct ieee80211_local *local, const char *name,
		     struct wireless_dev **new_wdev, enum nl80211_iftype type,
		     struct vif_params *params)
{
	struct net_device *ndev = NULL;
	struct ieee80211_sub_if_data *sdata = NULL;
	int ret, i;
	int txqs = 1;

	ASSERT_RTNL();

	if (type == NL80211_IFTYPE_P2P_DEVICE) {
		struct wireless_dev *wdev;

		sdata = kzalloc(sizeof(*sdata) + local->hw.vif_data_size,
				GFP_KERNEL);
		if (!sdata)
			return -ENOMEM;
		wdev = &sdata->wdev;

		sdata->dev = NULL;
		strlcpy(sdata->name, name, IFNAMSIZ);
		ieee80211_assign_perm_addr(local, wdev->address, type);
		memcpy(sdata->vif.addr, wdev->address, ETH_ALEN);
	} else {
		if (local->hw.queues >= IEEE80211_NUM_ACS)
			txqs = IEEE80211_NUM_ACS;

		ndev = alloc_netdev_mqs(sizeof(*sdata) +
					local->hw.vif_data_size,
					name, ieee80211_if_setup, txqs, 1);
		if (!ndev)
			return -ENOMEM;
		dev_net_set(ndev, wiphy_net(local->hw.wiphy));

		ndev->needed_headroom = local->tx_headroom +
					4*6 /* four MAC addresses */
					+ 2 + 2 + 2 + 2 /* ctl, dur, seq, qos */
					+ 6 /* mesh */
					+ 8 /* rfc1042/bridge tunnel */
					- ETH_HLEN /* ethernet hard_header_len */
					+ IEEE80211_ENCRYPT_HEADROOM;
		ndev->needed_tailroom = IEEE80211_ENCRYPT_TAILROOM;

		ret = dev_alloc_name(ndev, ndev->name);
		if (ret < 0) {
			free_netdev(ndev);
			return ret;
		}

		ieee80211_assign_perm_addr(local, ndev->perm_addr, type);
		memcpy(ndev->dev_addr, ndev->perm_addr, ETH_ALEN);
		SET_NETDEV_DEV(ndev, wiphy_dev(local->hw.wiphy));

		/* don't use IEEE80211_DEV_TO_SUB_IF -- it checks too much */
		sdata = netdev_priv(ndev);
		ndev->ieee80211_ptr = &sdata->wdev;
		memcpy(sdata->vif.addr, ndev->dev_addr, ETH_ALEN);
		memcpy(sdata->name, ndev->name, IFNAMSIZ);

		sdata->dev = ndev;
	}

	/* initialise type-independent data */
	sdata->wdev.wiphy = local->hw.wiphy;
	sdata->local = local;

	for (i = 0; i < IEEE80211_FRAGMENT_MAX; i++)
		skb_queue_head_init(&sdata->fragments[i].skb_list);

	INIT_LIST_HEAD(&sdata->key_list);

	spin_lock_init(&sdata->cleanup_stations_lock);
	INIT_LIST_HEAD(&sdata->cleanup_stations);
	INIT_WORK(&sdata->cleanup_stations_wk, ieee80211_cleanup_sdata_stas_wk);
	INIT_DELAYED_WORK(&sdata->dfs_cac_timer_work,
			  ieee80211_dfs_cac_timer_work);
	INIT_DELAYED_WORK(&sdata->dec_tailroom_needed_wk,
			  ieee80211_delayed_tailroom_dec);

	for (i = 0; i < IEEE80211_NUM_BANDS; i++) {
		struct ieee80211_supported_band *sband;
		sband = local->hw.wiphy->bands[i];
		sdata->rc_rateidx_mask[i] =
			sband ? (1 << sband->n_bitrates) - 1 : 0;
		if (sband)
			memcpy(sdata->rc_rateidx_mcs_mask[i],
			       sband->ht_cap.mcs.rx_mask,
			       sizeof(sdata->rc_rateidx_mcs_mask[i]));
		else
			memset(sdata->rc_rateidx_mcs_mask[i], 0,
			       sizeof(sdata->rc_rateidx_mcs_mask[i]));
	}

	ieee80211_set_default_queues(sdata);

	sdata->ap_power_level = IEEE80211_UNSET_POWER_LEVEL;
	sdata->user_power_level = local->user_power_level;

	/* setup type-dependent data */
	ieee80211_setup_sdata(sdata, type);

	if (ndev) {
		if (params) {
			ndev->ieee80211_ptr->use_4addr = params->use_4addr;
			if (type == NL80211_IFTYPE_STATION)
				sdata->u.mgd.use_4addr = params->use_4addr;
		}

		ndev->features |= local->hw.netdev_features;

		ret = register_netdevice(ndev);
		if (ret) {
			free_netdev(ndev);
			return ret;
		}
	}

	mutex_lock(&local->iflist_mtx);
	list_add_tail_rcu(&sdata->list, &local->interfaces);
	mutex_unlock(&local->iflist_mtx);

	if (new_wdev)
		*new_wdev = &sdata->wdev;

	return 0;
}