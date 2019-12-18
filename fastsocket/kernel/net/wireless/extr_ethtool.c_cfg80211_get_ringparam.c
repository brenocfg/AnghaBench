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
struct wireless_dev {int /*<<< orphan*/  wiphy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct ethtool_ringparam {int /*<<< orphan*/  rx_max_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  tx_pending; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
struct TYPE_2__ {scalar_t__ get_ringparam; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct ethtool_ringparam*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdev_get_ringparam (struct cfg80211_registered_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct cfg80211_registered_device* wiphy_to_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cfg80211_get_ringparam(struct net_device *dev,
				   struct ethtool_ringparam *rp)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_registered_device *rdev = wiphy_to_dev(wdev->wiphy);

	memset(rp, 0, sizeof(*rp));

	if (rdev->ops->get_ringparam)
		rdev_get_ringparam(rdev, &rp->tx_pending, &rp->tx_max_pending,
				   &rp->rx_pending, &rp->rx_max_pending);
}