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
typedef  int /*<<< orphan*/  u8 ;
struct wireless_dev {TYPE_1__* conn; int /*<<< orphan*/  wiphy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct cfg80211_registered_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  bssid; } ;
struct cfg80211_internal_bss {TYPE_2__ pub; } ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 scalar_t__ CFG80211_CONN_IDLE ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 int /*<<< orphan*/  __cfg80211_mlme_deauth (struct cfg80211_registered_device*,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct cfg80211_registered_device* wiphy_to_dev (int /*<<< orphan*/ ) ; 

void cfg80211_sme_disassoc(struct net_device *dev,
			   struct cfg80211_internal_bss *bss)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_registered_device *rdev = wiphy_to_dev(wdev->wiphy);
	u8 bssid[ETH_ALEN];

	ASSERT_WDEV_LOCK(wdev);

	if (!wdev->conn)
		return;

	if (wdev->conn->state == CFG80211_CONN_IDLE)
		return;

	/*
	 * Ok, so the association was made by this SME -- we don't
	 * want it any more so deauthenticate too.
	 */

	memcpy(bssid, bss->pub.bssid, ETH_ALEN);

	__cfg80211_mlme_deauth(rdev, dev, bssid, NULL, 0,
			       WLAN_REASON_DEAUTH_LEAVING, false);
}