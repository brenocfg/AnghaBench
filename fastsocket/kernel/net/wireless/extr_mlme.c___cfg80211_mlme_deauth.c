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
typedef  int /*<<< orphan*/  u16 ;
struct wireless_dev {TYPE_1__* current_bss; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct cfg80211_registered_device {int dummy; } ;
struct cfg80211_deauth_request {int ie_len; int local_state_change; int /*<<< orphan*/  const* ie; int /*<<< orphan*/  reason_code; int /*<<< orphan*/  const* bssid; } ;
struct TYPE_4__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_3__ {TYPE_2__ pub; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int rdev_deauth (struct cfg80211_registered_device*,struct net_device*,struct cfg80211_deauth_request*) ; 

int __cfg80211_mlme_deauth(struct cfg80211_registered_device *rdev,
			   struct net_device *dev, const u8 *bssid,
			   const u8 *ie, int ie_len, u16 reason,
			   bool local_state_change)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_deauth_request req = {
		.bssid = bssid,
		.reason_code = reason,
		.ie = ie,
		.ie_len = ie_len,
		.local_state_change = local_state_change,
	};

	ASSERT_WDEV_LOCK(wdev);

	if (local_state_change && (!wdev->current_bss ||
	    !ether_addr_equal(wdev->current_bss->pub.bssid, bssid)))
		return 0;

	return rdev_deauth(rdev, dev, &req);
}