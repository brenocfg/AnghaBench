#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wireless_dev {scalar_t__ sme_state; TYPE_2__* conn; int /*<<< orphan*/  netdev; int /*<<< orphan*/  wiphy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  conn_work; int /*<<< orphan*/  wiphy; } ;
struct cfg80211_bss {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_4__ {scalar_t__ state; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 scalar_t__ CFG80211_CONN_SCANNING ; 
 scalar_t__ CFG80211_CONN_SCAN_AGAIN ; 
 scalar_t__ CFG80211_SME_CONNECTING ; 
 int /*<<< orphan*/  WLAN_STATUS_UNSPECIFIED_FAILURE ; 
 int /*<<< orphan*/  __cfg80211_connect_result (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct cfg80211_bss* cfg80211_get_conn_bss (struct wireless_dev*) ; 
 int /*<<< orphan*/  cfg80211_put_bss (int /*<<< orphan*/ *,struct cfg80211_bss*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct cfg80211_registered_device* wiphy_to_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __cfg80211_sme_scan_done(struct net_device *dev)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_registered_device *rdev = wiphy_to_dev(wdev->wiphy);
	struct cfg80211_bss *bss;

	ASSERT_WDEV_LOCK(wdev);

	if (wdev->sme_state != CFG80211_SME_CONNECTING)
		return;

	if (!wdev->conn)
		return;

	if (wdev->conn->state != CFG80211_CONN_SCANNING &&
	    wdev->conn->state != CFG80211_CONN_SCAN_AGAIN)
		return;

	bss = cfg80211_get_conn_bss(wdev);
	if (bss) {
		cfg80211_put_bss(&rdev->wiphy, bss);
	} else {
		/* not found */
		if (wdev->conn->state == CFG80211_CONN_SCAN_AGAIN)
			schedule_work(&rdev->conn_work);
		else
			__cfg80211_connect_result(
					wdev->netdev,
					wdev->conn->params.bssid,
					NULL, 0, NULL, 0,
					WLAN_STATUS_UNSPECIFIED_FAILURE,
					false, NULL);
	}
}