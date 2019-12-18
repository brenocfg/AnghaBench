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
struct net_device {TYPE_1__* ieee80211_ptr; } ;
struct net {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  mtx; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct cfg80211_registered_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_mutex ; 
 struct net_device* dev_get_by_index (struct net*,int) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct cfg80211_registered_device* wiphy_to_dev (int /*<<< orphan*/ ) ; 

struct cfg80211_registered_device *
cfg80211_get_dev_from_ifindex(struct net *net, int ifindex)
{
	struct cfg80211_registered_device *rdev = ERR_PTR(-ENODEV);
	struct net_device *dev;

	mutex_lock(&cfg80211_mutex);
	dev = dev_get_by_index(net, ifindex);
	if (!dev)
		goto out;
	if (dev->ieee80211_ptr) {
		rdev = wiphy_to_dev(dev->ieee80211_ptr->wiphy);
		mutex_lock(&rdev->mtx);
	} else
		rdev = ERR_PTR(-ENODEV);
	dev_put(dev);
 out:
	mutex_unlock(&cfg80211_mutex);
	return rdev;
}