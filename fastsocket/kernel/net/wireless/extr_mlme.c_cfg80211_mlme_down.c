#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wireless_dev {TYPE_2__* current_bss; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct cfg80211_deauth_request {int /*<<< orphan*/ * bssid; scalar_t__ ie_len; int /*<<< orphan*/ * ie; int /*<<< orphan*/  reason_code; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_6__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_5__ {TYPE_3__ pub; } ;
struct TYPE_4__ {int /*<<< orphan*/  deauth; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 int /*<<< orphan*/  cfg80211_put_bss (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  cfg80211_unhold_bss (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct cfg80211_deauth_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdev_deauth (struct cfg80211_registered_device*,struct net_device*,struct cfg80211_deauth_request*) ; 

void cfg80211_mlme_down(struct cfg80211_registered_device *rdev,
			struct net_device *dev)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_deauth_request req;
	u8 bssid[ETH_ALEN];

	ASSERT_WDEV_LOCK(wdev);

	if (!rdev->ops->deauth)
		return;

	memset(&req, 0, sizeof(req));
	req.reason_code = WLAN_REASON_DEAUTH_LEAVING;
	req.ie = NULL;
	req.ie_len = 0;

	if (!wdev->current_bss)
		return;

	memcpy(bssid, wdev->current_bss->pub.bssid, ETH_ALEN);
	req.bssid = bssid;
	rdev_deauth(rdev, dev, &req);

	if (wdev->current_bss) {
		cfg80211_unhold_bss(wdev->current_bss);
		cfg80211_put_bss(&rdev->wiphy, &wdev->current_bss->pub);
		wdev->current_bss = NULL;
	}
}