#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  ieee80211_ptr; TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  key; } ;
struct key_parse {int type; TYPE_2__ p; int /*<<< orphan*/  idx; } ;
struct genl_info {scalar_t__* attrs; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  ieee80211_ptr; TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  add_key; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 size_t NL80211_ATTR_MAC ; 
 int NL80211_KEYTYPE_GROUP ; 
 int NL80211_KEYTYPE_PAIRWISE ; 
 scalar_t__ cfg80211_validate_key_settings (struct net_device*,TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ; 
 int nl80211_key_allowed (int /*<<< orphan*/ ) ; 
 int nl80211_parse_key (struct genl_info*,struct key_parse*) ; 
 int /*<<< orphan*/ * nla_data (scalar_t__) ; 
 int rdev_add_key (struct net_device*,struct net_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,TYPE_2__*) ; 
 int /*<<< orphan*/  wdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdev_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nl80211_new_key(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	int err;
	struct net_device *dev = info->user_ptr[1];
	struct key_parse key;
	const u8 *mac_addr = NULL;

	err = nl80211_parse_key(info, &key);
	if (err)
		return err;

	if (!key.p.key)
		return -EINVAL;

	if (info->attrs[NL80211_ATTR_MAC])
		mac_addr = nla_data(info->attrs[NL80211_ATTR_MAC]);

	if (key.type == -1) {
		if (mac_addr)
			key.type = NL80211_KEYTYPE_PAIRWISE;
		else
			key.type = NL80211_KEYTYPE_GROUP;
	}

	/* for now */
	if (key.type != NL80211_KEYTYPE_PAIRWISE &&
	    key.type != NL80211_KEYTYPE_GROUP)
		return -EINVAL;

	if (!rdev->ops->add_key)
		return -EOPNOTSUPP;

	if (cfg80211_validate_key_settings(rdev, &key.p, key.idx,
					   key.type == NL80211_KEYTYPE_PAIRWISE,
					   mac_addr))
		return -EINVAL;

	wdev_lock(dev->ieee80211_ptr);
	err = nl80211_key_allowed(dev->ieee80211_ptr);
	if (!err)
		err = rdev_add_key(rdev, dev, key.idx,
				   key.type == NL80211_KEYTYPE_PAIRWISE,
				    mac_addr, &key.p);
	wdev_unlock(dev->ieee80211_ptr);

	return err;
}