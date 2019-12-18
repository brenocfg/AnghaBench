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
struct wiphy {int dummy; } ;
struct cfg80211_registered_device {struct wiphy wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_cfg80211_lock () ; 
 struct cfg80211_registered_device* cfg80211_rdev_by_wiphy_idx (int) ; 

struct wiphy *wiphy_idx_to_wiphy(int wiphy_idx)
{
	struct cfg80211_registered_device *rdev;

	assert_cfg80211_lock();

	rdev = cfg80211_rdev_by_wiphy_idx(wiphy_idx);
	if (!rdev)
		return NULL;
	return &rdev->wiphy;
}