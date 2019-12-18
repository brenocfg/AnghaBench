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
struct cfg80211_registered_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfg80211_unlock_rdev (struct cfg80211_registered_device*) ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static void nl80211_finish_wdev_dump(struct cfg80211_registered_device *rdev)
{
	cfg80211_unlock_rdev(rdev);
	rtnl_unlock();
}