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
struct net {int dummy; } ;
struct genl_info {int /*<<< orphan*/  attrs; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct cfg80211_registered_device*) ; 
 struct cfg80211_registered_device* __cfg80211_rdev_from_attrs (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct cfg80211_registered_device *
cfg80211_get_dev_from_info(struct net *netns, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev;

	mutex_lock(&cfg80211_mutex);
	rdev = __cfg80211_rdev_from_attrs(netns, info->attrs);

	/* if it is not an error we grab the lock on
	 * it to assure it won't be going away while
	 * we operate on it */
	if (!IS_ERR(rdev))
		mutex_lock(&rdev->mtx);

	mutex_unlock(&cfg80211_mutex);

	return rdev;
}