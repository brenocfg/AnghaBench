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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int priv_flags; } ;
struct TYPE_2__ {int flags; } ;
struct cfg80211_registered_device {TYPE_1__ wiphy; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int IFF_BRIDGE_PORT ; 
#define  NL80211_IFTYPE_AP_VLAN 129 
#define  NL80211_IFTYPE_STATION 128 
 int WIPHY_FLAG_4ADDR_AP ; 
 int WIPHY_FLAG_4ADDR_STATION ; 

__attribute__((used)) static int nl80211_valid_4addr(struct cfg80211_registered_device *rdev,
			       struct net_device *netdev, u8 use_4addr,
			       enum nl80211_iftype iftype)
{
	if (!use_4addr) {
		if (netdev && (netdev->priv_flags & IFF_BRIDGE_PORT))
			return -EBUSY;
		return 0;
	}

	switch (iftype) {
	case NL80211_IFTYPE_AP_VLAN:
		if (rdev->wiphy.flags & WIPHY_FLAG_4ADDR_AP)
			return 0;
		break;
	case NL80211_IFTYPE_STATION:
		if (rdev->wiphy.flags & WIPHY_FLAG_4ADDR_STATION)
			return 0;
		break;
	default:
		break;
	}

	return -EOPNOTSUPP;
}