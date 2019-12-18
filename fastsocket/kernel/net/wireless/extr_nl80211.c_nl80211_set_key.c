#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct net_device {TYPE_3__* ieee80211_ptr; TYPE_1__* ops; } ;
struct key_parse {scalar_t__ idx; int /*<<< orphan*/  def_multi; scalar_t__ def_uni; scalar_t__ def; int /*<<< orphan*/  defmgmt; } ;
struct genl_info {struct net_device** user_ptr; } ;
struct cfg80211_registered_device {TYPE_3__* ieee80211_ptr; TYPE_1__* ops; } ;
struct TYPE_7__ {scalar_t__ default_key; scalar_t__ default_mgmt_key; } ;
struct TYPE_8__ {TYPE_2__ wext; } ;
struct TYPE_6__ {int /*<<< orphan*/  set_default_mgmt_key; int /*<<< orphan*/  set_default_key; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int nl80211_key_allowed (TYPE_3__*) ; 
 int nl80211_parse_key (struct genl_info*,struct key_parse*) ; 
 int rdev_set_default_key (struct net_device*,struct net_device*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int rdev_set_default_mgmt_key (struct net_device*,struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  wdev_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  wdev_unlock (TYPE_3__*) ; 

__attribute__((used)) static int nl80211_set_key(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct key_parse key;
	int err;
	struct net_device *dev = info->user_ptr[1];

	err = nl80211_parse_key(info, &key);
	if (err)
		return err;

	if (key.idx < 0)
		return -EINVAL;

	/* only support setting default key */
	if (!key.def && !key.defmgmt)
		return -EINVAL;

	wdev_lock(dev->ieee80211_ptr);

	if (key.def) {
		if (!rdev->ops->set_default_key) {
			err = -EOPNOTSUPP;
			goto out;
		}

		err = nl80211_key_allowed(dev->ieee80211_ptr);
		if (err)
			goto out;

		err = rdev_set_default_key(rdev, dev, key.idx,
						 key.def_uni, key.def_multi);

		if (err)
			goto out;

#ifdef CONFIG_CFG80211_WEXT
		dev->ieee80211_ptr->wext.default_key = key.idx;
#endif
	} else {
		if (key.def_uni || !key.def_multi) {
			err = -EINVAL;
			goto out;
		}

		if (!rdev->ops->set_default_mgmt_key) {
			err = -EOPNOTSUPP;
			goto out;
		}

		err = nl80211_key_allowed(dev->ieee80211_ptr);
		if (err)
			goto out;

		err = rdev_set_default_mgmt_key(rdev, dev, key.idx);
		if (err)
			goto out;

#ifdef CONFIG_CFG80211_WEXT
		dev->ieee80211_ptr->wext.default_mgmt_key = key.idx;
#endif
	}

 out:
	wdev_unlock(dev->ieee80211_ptr);

	return err;
}