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
struct cfg80211_registered_device {int num_running_ifaces; int num_running_monitor_ifaces; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int NL80211_IFTYPE_MONITOR ; 

void cfg80211_update_iface_num(struct cfg80211_registered_device *rdev,
			       enum nl80211_iftype iftype, int num)
{
	ASSERT_RTNL();

	rdev->num_running_ifaces += num;
	if (iftype == NL80211_IFTYPE_MONITOR)
		rdev->num_running_monitor_ifaces += num;
}