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
struct cfg80211_registered_device {int /*<<< orphan*/  rfkill; } ;

/* Variables and functions */
 int /*<<< orphan*/  rfkill_pause_polling (int /*<<< orphan*/ ) ; 
 struct cfg80211_registered_device* wiphy_to_dev (struct wiphy*) ; 

void wiphy_rfkill_stop_polling(struct wiphy *wiphy)
{
	struct cfg80211_registered_device *rdev = wiphy_to_dev(wiphy);

	rfkill_pause_polling(rdev->rfkill);
}