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
typedef  int /*<<< orphan*/  u16 ;
struct wireless_dev {scalar_t__ sme_state; TYPE_3__* conn; scalar_t__ ssid_len; TYPE_3__* connect_keys; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_6__ {scalar_t__ state; TYPE_2__ params; struct TYPE_6__* ie; } ;
struct TYPE_4__ {int /*<<< orphan*/  deauth; int /*<<< orphan*/  disconnect; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 scalar_t__ CFG80211_CONN_SCANNING ; 
 scalar_t__ CFG80211_CONN_SCAN_AGAIN ; 
 scalar_t__ CFG80211_SME_CONNECTED ; 
 scalar_t__ CFG80211_SME_CONNECTING ; 
 scalar_t__ CFG80211_SME_IDLE ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  WLAN_STATUS_UNSPECIFIED_FAILURE ; 
 int /*<<< orphan*/  __cfg80211_connect_result (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __cfg80211_disconnected (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int __cfg80211_mlme_deauth (struct cfg80211_registered_device*,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cfg80211_mlme_down (struct cfg80211_registered_device*,struct net_device*) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int rdev_disconnect (struct cfg80211_registered_device*,struct net_device*,int /*<<< orphan*/ ) ; 

int __cfg80211_disconnect(struct cfg80211_registered_device *rdev,
			  struct net_device *dev, u16 reason, bool wextev)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	int err;

	ASSERT_WDEV_LOCK(wdev);

	if (wdev->sme_state == CFG80211_SME_IDLE)
		return -EINVAL;

	kfree(wdev->connect_keys);
	wdev->connect_keys = NULL;

	if (!rdev->ops->disconnect) {
		if (!rdev->ops->deauth)
			return -EOPNOTSUPP;

		/* was it connected by userspace SME? */
		if (!wdev->conn) {
			cfg80211_mlme_down(rdev, dev);
			goto disconnect;
		}

		if (wdev->sme_state == CFG80211_SME_CONNECTING &&
		    (wdev->conn->state == CFG80211_CONN_SCANNING ||
		     wdev->conn->state == CFG80211_CONN_SCAN_AGAIN)) {
			wdev->sme_state = CFG80211_SME_IDLE;
			kfree(wdev->conn->ie);
			kfree(wdev->conn);
			wdev->conn = NULL;
			wdev->ssid_len = 0;
			return 0;
		}

		/* wdev->conn->params.bssid must be set if > SCANNING */
		err = __cfg80211_mlme_deauth(rdev, dev,
					     wdev->conn->params.bssid,
					     NULL, 0, reason, false);
		if (err)
			return err;
	} else {
		err = rdev_disconnect(rdev, dev, reason);
		if (err)
			return err;
	}

 disconnect:
	if (wdev->sme_state == CFG80211_SME_CONNECTED)
		__cfg80211_disconnected(dev, NULL, 0, 0, false);
	else if (wdev->sme_state == CFG80211_SME_CONNECTING)
		__cfg80211_connect_result(dev, NULL, NULL, 0, NULL, 0,
					  WLAN_STATUS_UNSPECIFIED_FAILURE,
					  wextev, NULL);

	return 0;
}