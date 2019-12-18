#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  auth_type; } ;
struct TYPE_13__ {int default_key; int default_mgmt_key; int /*<<< orphan*/  keys; TYPE_4__ connect; } ;
struct wireless_dev {scalar_t__ iftype; int ps; int ps_timeout; TYPE_7__* wiphy; int /*<<< orphan*/  list; TYPE_5__ wext; int /*<<< orphan*/  mesh_id_up_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  cleanup_work; int /*<<< orphan*/  use_4addr; int /*<<< orphan*/  sme_state; struct net_device* netdev; int /*<<< orphan*/  identifier; int /*<<< orphan*/  mgmt_registrations_lock; int /*<<< orphan*/  mgmt_registrations; int /*<<< orphan*/  event_lock; int /*<<< orphan*/  event_list; int /*<<< orphan*/  mtx; } ;
struct notifier_block {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  kobj; } ;
struct net_device {TYPE_1__ dev; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/  features; struct wireless_dev* ieee80211_ptr; } ;
struct mesh_setup {int /*<<< orphan*/  mesh_id_len; int /*<<< orphan*/  mesh_id; } ;
struct TYPE_10__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_11__ {TYPE_2__ dev; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  devlist_mtx; int /*<<< orphan*/  rfkill; int /*<<< orphan*/  devlist_generation; TYPE_6__* ops; int /*<<< orphan*/  opencount; int /*<<< orphan*/  sched_scan_mtx; TYPE_3__ wiphy; int /*<<< orphan*/  wdev_list; int /*<<< orphan*/  wdev_id; } ;
typedef  int /*<<< orphan*/  setup ;
struct TYPE_16__ {int /*<<< orphan*/  ext_priv_flags; } ;
struct TYPE_15__ {int flags; int interface_modes; } ;
struct TYPE_14__ {int /*<<< orphan*/  set_power_mgmt; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  CFG80211_SME_IDLE ; 
 int EOPNOTSUPP ; 
 int ERFKILL ; 
 int /*<<< orphan*/  IFF_DONT_BRIDGE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  NETDEV_DOWN 137 
#define  NETDEV_GOING_DOWN 136 
#define  NETDEV_POST_INIT 135 
#define  NETDEV_PRE_UP 134 
#define  NETDEV_REGISTER 133 
#define  NETDEV_UNREGISTER 132 
#define  NETDEV_UP 131 
 int /*<<< orphan*/  NETIF_F_NETNS_LOCAL ; 
 int /*<<< orphan*/  NL80211_AUTHTYPE_AUTOMATIC ; 
#define  NL80211_IFTYPE_ADHOC 130 
#define  NL80211_IFTYPE_MESH_POINT 129 
 int NL80211_IFTYPE_P2P_CLIENT ; 
#define  NL80211_IFTYPE_STATION 128 
 scalar_t__ NL80211_IFTYPE_UNSPECIFIED ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  SET_NETDEV_DEVTYPE (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int WIPHY_FLAG_PS_ON_BY_DEFAULT ; 
 int /*<<< orphan*/  __cfg80211_join_mesh (struct cfg80211_registered_device*,struct net_device*,struct mesh_setup*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int cfg80211_can_add_interface (struct cfg80211_registered_device*,int) ; 
 int /*<<< orphan*/  cfg80211_ethtool_ops ; 
 int /*<<< orphan*/  cfg80211_ibss_wext_join (struct cfg80211_registered_device*,struct wireless_dev*) ; 
 int /*<<< orphan*/  cfg80211_leave (struct cfg80211_registered_device*,struct wireless_dev*) ; 
 int /*<<< orphan*/  cfg80211_lock_rdev (struct cfg80211_registered_device*) ; 
 int /*<<< orphan*/  cfg80211_mgd_wext_connect (struct cfg80211_registered_device*,struct wireless_dev*) ; 
 int /*<<< orphan*/  cfg80211_mlme_purge_registrations (struct wireless_dev*) ; 
 int /*<<< orphan*/  cfg80211_process_wdev_events (struct wireless_dev*) ; 
 int /*<<< orphan*/  cfg80211_unlock_rdev (struct cfg80211_registered_device*) ; 
 int /*<<< orphan*/  cfg80211_update_iface_num (struct cfg80211_registered_device*,int,int) ; 
 int /*<<< orphan*/  cfg80211_wq ; 
 int /*<<< orphan*/  default_mesh_config ; 
 int /*<<< orphan*/  default_mesh_setup ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct mesh_setup*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_8__* netdev_extended (struct net_device*) ; 
 int /*<<< orphan*/  netdev_set_default_ethtool_ops (struct net_device*,int /*<<< orphan*/ *) ; 
 int notifier_from_errno (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdev_set_power_mgmt (struct cfg80211_registered_device*,struct net_device*,int,int) ; 
 int /*<<< orphan*/  rfkill_blocked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wdev_cleanup_work ; 
 int /*<<< orphan*/  wdev_lock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_unlock (struct wireless_dev*) ; 
 struct cfg80211_registered_device* wiphy_to_dev (TYPE_7__*) ; 
 int /*<<< orphan*/  wiphy_type ; 

__attribute__((used)) static int cfg80211_netdev_notifier_call(struct notifier_block *nb,
					 unsigned long state,
					 void *ndev)
{
	struct net_device *dev = ndev;
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_registered_device *rdev;
	int ret;

	if (!wdev)
		return NOTIFY_DONE;

	rdev = wiphy_to_dev(wdev->wiphy);

	WARN_ON(wdev->iftype == NL80211_IFTYPE_UNSPECIFIED);

	switch (state) {
	case NETDEV_POST_INIT:
		SET_NETDEV_DEVTYPE(dev, &wiphy_type);
		break;
	case NETDEV_REGISTER:
		/*
		 * NB: cannot take rdev->mtx here because this may be
		 * called within code protected by it when interfaces
		 * are added with nl80211.
		 */
		mutex_init(&wdev->mtx);
		INIT_WORK(&wdev->cleanup_work, wdev_cleanup_work);
		INIT_LIST_HEAD(&wdev->event_list);
		spin_lock_init(&wdev->event_lock);
		INIT_LIST_HEAD(&wdev->mgmt_registrations);
		spin_lock_init(&wdev->mgmt_registrations_lock);

		mutex_lock(&rdev->devlist_mtx);
		wdev->identifier = ++rdev->wdev_id;
		list_add_rcu(&wdev->list, &rdev->wdev_list);
		rdev->devlist_generation++;
		/* can only change netns with wiphy */
		dev->features |= NETIF_F_NETNS_LOCAL;

		if (sysfs_create_link(&dev->dev.kobj, &rdev->wiphy.dev.kobj,
				      "phy80211")) {
			pr_err("failed to add phy80211 symlink to netdev!\n");
		}
		wdev->netdev = dev;
		wdev->sme_state = CFG80211_SME_IDLE;
		mutex_unlock(&rdev->devlist_mtx);
#ifdef CONFIG_CFG80211_WEXT
		wdev->wext.default_key = -1;
		wdev->wext.default_mgmt_key = -1;
		wdev->wext.connect.auth_type = NL80211_AUTHTYPE_AUTOMATIC;
#endif

		if (wdev->wiphy->flags & WIPHY_FLAG_PS_ON_BY_DEFAULT)
			wdev->ps = true;
		else
			wdev->ps = false;
		/* allow mac80211 to determine the timeout */
		wdev->ps_timeout = -1;

#if 0 /* Not in RHEL */
		netdev_set_default_ethtool_ops(dev, &cfg80211_ethtool_ops);
#else
		if (!dev->ethtool_ops)
			dev->ethtool_ops = &cfg80211_ethtool_ops;
#endif

		if ((wdev->iftype == NL80211_IFTYPE_STATION ||
		     wdev->iftype == NL80211_IFTYPE_P2P_CLIENT ||
		     wdev->iftype == NL80211_IFTYPE_ADHOC) && !wdev->use_4addr)
			netdev_extended(dev)->ext_priv_flags |= IFF_DONT_BRIDGE;
		break;
	case NETDEV_GOING_DOWN:
		cfg80211_leave(rdev, wdev);
		break;
	case NETDEV_DOWN:
		cfg80211_update_iface_num(rdev, wdev->iftype, -1);
		dev_hold(dev);
		queue_work(cfg80211_wq, &wdev->cleanup_work);
		break;
	case NETDEV_UP:
		/*
		 * If we have a really quick DOWN/UP succession we may
		 * have this work still pending ... cancel it and see
		 * if it was pending, in which case we need to account
		 * for some of the work it would have done.
		 */
		if (cancel_work_sync(&wdev->cleanup_work)) {
			mutex_lock(&rdev->devlist_mtx);
			rdev->opencount--;
			mutex_unlock(&rdev->devlist_mtx);
			dev_put(dev);
		}
		cfg80211_update_iface_num(rdev, wdev->iftype, 1);
		cfg80211_lock_rdev(rdev);
		mutex_lock(&rdev->devlist_mtx);
		mutex_lock(&rdev->sched_scan_mtx);
		wdev_lock(wdev);
		switch (wdev->iftype) {
#ifdef CONFIG_CFG80211_WEXT
		case NL80211_IFTYPE_ADHOC:
			cfg80211_ibss_wext_join(rdev, wdev);
			break;
		case NL80211_IFTYPE_STATION:
			cfg80211_mgd_wext_connect(rdev, wdev);
			break;
#endif
#ifdef CONFIG_MAC80211_MESH
		case NL80211_IFTYPE_MESH_POINT:
			{
				/* backward compat code... */
				struct mesh_setup setup;
				memcpy(&setup, &default_mesh_setup,
						sizeof(setup));
				 /* back compat only needed for mesh_id */
				setup.mesh_id = wdev->ssid;
				setup.mesh_id_len = wdev->mesh_id_up_len;
				if (wdev->mesh_id_up_len)
					__cfg80211_join_mesh(rdev, dev,
							&setup,
							&default_mesh_config);
				break;
			}
#endif
		default:
			break;
		}
		wdev_unlock(wdev);
		mutex_unlock(&rdev->sched_scan_mtx);
		rdev->opencount++;
		mutex_unlock(&rdev->devlist_mtx);
		cfg80211_unlock_rdev(rdev);

		/*
		 * Configure power management to the driver here so that its
		 * correctly set also after interface type changes etc.
		 */
		if ((wdev->iftype == NL80211_IFTYPE_STATION ||
		     wdev->iftype == NL80211_IFTYPE_P2P_CLIENT) &&
		    rdev->ops->set_power_mgmt)
			if (rdev_set_power_mgmt(rdev, dev, wdev->ps,
						wdev->ps_timeout)) {
				/* assume this means it's off */
				wdev->ps = false;
			}
		break;
	case NETDEV_UNREGISTER:
		/*
		 * NB: cannot take rdev->mtx here because this may be
		 * called within code protected by it when interfaces
		 * are removed with nl80211.
		 */
		mutex_lock(&rdev->devlist_mtx);
		/*
		 * It is possible to get NETDEV_UNREGISTER
		 * multiple times. To detect that, check
		 * that the interface is still on the list
		 * of registered interfaces, and only then
		 * remove and clean it up.
		 */
		if (!list_empty(&wdev->list)) {
			sysfs_remove_link(&dev->dev.kobj, "phy80211");
			list_del_rcu(&wdev->list);
			rdev->devlist_generation++;
			cfg80211_mlme_purge_registrations(wdev);
#ifdef CONFIG_CFG80211_WEXT
			kfree(wdev->wext.keys);
#endif
		}
		mutex_unlock(&rdev->devlist_mtx);
		/*
		 * synchronise (so that we won't find this netdev
		 * from other code any more) and then clear the list
		 * head so that the above code can safely check for
		 * !list_empty() to avoid double-cleanup.
		 */
		synchronize_rcu();
		INIT_LIST_HEAD(&wdev->list);
		/*
		 * Ensure that all events have been processed and
		 * freed.
		 */
		cfg80211_process_wdev_events(wdev);
		break;
	case NETDEV_PRE_UP:
		if (!(wdev->wiphy->interface_modes & BIT(wdev->iftype)))
			return notifier_from_errno(-EOPNOTSUPP);
		if (rfkill_blocked(rdev->rfkill))
			return notifier_from_errno(-ERFKILL);
		mutex_lock(&rdev->devlist_mtx);
		ret = cfg80211_can_add_interface(rdev, wdev->iftype);
		mutex_unlock(&rdev->devlist_mtx);
		if (ret)
			return notifier_from_errno(ret);
		break;
	}

	return NOTIFY_DONE;
}