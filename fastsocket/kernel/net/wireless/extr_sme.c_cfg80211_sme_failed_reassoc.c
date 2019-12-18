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
struct wireless_dev {TYPE_1__* conn; struct wiphy* wiphy; } ;
struct wiphy {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  conn_work; } ;
struct TYPE_2__ {int prev_bssid_valid; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG80211_CONN_ASSOCIATE_NEXT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct cfg80211_registered_device* wiphy_to_dev (struct wiphy*) ; 

bool cfg80211_sme_failed_reassoc(struct wireless_dev *wdev)
{
	struct wiphy *wiphy = wdev->wiphy;
	struct cfg80211_registered_device *rdev = wiphy_to_dev(wiphy);

	if (WARN_ON(!wdev->conn))
		return false;

	if (!wdev->conn->prev_bssid_valid)
		return false;

	/*
	 * Some stupid APs don't accept reassoc, so we
	 * need to fall back to trying regular assoc.
	 */
	wdev->conn->prev_bssid_valid = false;
	wdev->conn->state = CFG80211_CONN_ASSOCIATE_NEXT;
	schedule_work(&rdev->conn_work);

	return true;
}