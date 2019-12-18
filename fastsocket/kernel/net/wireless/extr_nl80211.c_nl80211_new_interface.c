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
typedef  int /*<<< orphan*/  u32 ;
struct wireless_dev {int /*<<< orphan*/  list; int /*<<< orphan*/  identifier; int /*<<< orphan*/  mgmt_registrations_lock; int /*<<< orphan*/  mgmt_registrations; int /*<<< orphan*/  event_lock; int /*<<< orphan*/  event_list; int /*<<< orphan*/  mtx; int /*<<< orphan*/  mesh_id_up_len; int /*<<< orphan*/  ssid; } ;
struct vif_params {int use_4addr; int /*<<< orphan*/  macaddr; } ;
struct sk_buff {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_pid; int /*<<< orphan*/ ** attrs; struct cfg80211_registered_device** user_ptr; } ;
struct TYPE_4__ {int interface_modes; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  devlist_mtx; int /*<<< orphan*/  devlist_generation; int /*<<< orphan*/  wdev_list; int /*<<< orphan*/  wdev_id; TYPE_2__ wiphy; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  params ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;
struct TYPE_3__ {int /*<<< orphan*/  add_virtual_intf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IEEE80211_MAX_MESH_ID_LEN ; 
 int /*<<< orphan*/  IEEE80211_MAX_SSID_LEN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct wireless_dev*) ; 
 size_t NL80211_ATTR_4ADDR ; 
 size_t NL80211_ATTR_IFNAME ; 
 size_t NL80211_ATTR_IFTYPE ; 
 size_t NL80211_ATTR_MAC ; 
 size_t NL80211_ATTR_MESH_ID ; 
 size_t NL80211_ATTR_MNTR_FLAGS ; 
 int NL80211_IFTYPE_MAX ; 
#define  NL80211_IFTYPE_MESH_POINT 129 
 int NL80211_IFTYPE_MONITOR ; 
#define  NL80211_IFTYPE_P2P_DEVICE 128 
 int NL80211_IFTYPE_UNSPECIFIED ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int PTR_ERR (struct wireless_dev*) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct vif_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nl80211_send_iface (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cfg80211_registered_device*,struct wireless_dev*) ; 
 int nl80211_valid_4addr (struct cfg80211_registered_device*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  nla_data (int /*<<< orphan*/ *) ; 
 int nla_get_u32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nla_get_u8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nla_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nla_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int parse_monitor_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct wireless_dev* rdev_add_virtual_intf (struct cfg80211_registered_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct vif_params*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdev_lock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_unlock (struct wireless_dev*) ; 

__attribute__((used)) static int nl80211_new_interface(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct vif_params params;
	struct wireless_dev *wdev;
	struct sk_buff *msg;
	int err;
	enum nl80211_iftype type = NL80211_IFTYPE_UNSPECIFIED;
	u32 flags;

	memset(&params, 0, sizeof(params));

	if (!info->attrs[NL80211_ATTR_IFNAME])
		return -EINVAL;

	if (info->attrs[NL80211_ATTR_IFTYPE]) {
		type = nla_get_u32(info->attrs[NL80211_ATTR_IFTYPE]);
		if (type > NL80211_IFTYPE_MAX)
			return -EINVAL;
	}

	if (!rdev->ops->add_virtual_intf ||
	    !(rdev->wiphy.interface_modes & (1 << type)))
		return -EOPNOTSUPP;

	if (type == NL80211_IFTYPE_P2P_DEVICE && info->attrs[NL80211_ATTR_MAC]) {
		nla_memcpy(params.macaddr, info->attrs[NL80211_ATTR_MAC],
			   ETH_ALEN);
		if (!is_valid_ether_addr(params.macaddr))
			return -EADDRNOTAVAIL;
	}

	if (info->attrs[NL80211_ATTR_4ADDR]) {
		params.use_4addr = !!nla_get_u8(info->attrs[NL80211_ATTR_4ADDR]);
		err = nl80211_valid_4addr(rdev, NULL, params.use_4addr, type);
		if (err)
			return err;
	}

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	err = parse_monitor_flags(type == NL80211_IFTYPE_MONITOR ?
				  info->attrs[NL80211_ATTR_MNTR_FLAGS] : NULL,
				  &flags);
	wdev = rdev_add_virtual_intf(rdev,
				nla_data(info->attrs[NL80211_ATTR_IFNAME]),
				type, err ? NULL : &flags, &params);
	if (IS_ERR(wdev)) {
		nlmsg_free(msg);
		return PTR_ERR(wdev);
	}

	switch (type) {
	case NL80211_IFTYPE_MESH_POINT:
		if (!info->attrs[NL80211_ATTR_MESH_ID])
			break;
		wdev_lock(wdev);
		BUILD_BUG_ON(IEEE80211_MAX_SSID_LEN !=
			     IEEE80211_MAX_MESH_ID_LEN);
		wdev->mesh_id_up_len =
			nla_len(info->attrs[NL80211_ATTR_MESH_ID]);
		memcpy(wdev->ssid, nla_data(info->attrs[NL80211_ATTR_MESH_ID]),
		       wdev->mesh_id_up_len);
		wdev_unlock(wdev);
		break;
	case NL80211_IFTYPE_P2P_DEVICE:
		/*
		 * P2P Device doesn't have a netdev, so doesn't go
		 * through the netdev notifier and must be added here
		 */
		mutex_init(&wdev->mtx);
		INIT_LIST_HEAD(&wdev->event_list);
		spin_lock_init(&wdev->event_lock);
		INIT_LIST_HEAD(&wdev->mgmt_registrations);
		spin_lock_init(&wdev->mgmt_registrations_lock);

		mutex_lock(&rdev->devlist_mtx);
		wdev->identifier = ++rdev->wdev_id;
		list_add_rcu(&wdev->list, &rdev->wdev_list);
		rdev->devlist_generation++;
		mutex_unlock(&rdev->devlist_mtx);
		break;
	default:
		break;
	}

	if (nl80211_send_iface(msg, info->snd_pid, info->snd_seq, 0,
			       rdev, wdev) < 0) {
		nlmsg_free(msg);
		return -ENOBUFS;
	}

	return genlmsg_reply(msg, info);
}