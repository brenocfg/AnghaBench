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
struct wireless_dev {int /*<<< orphan*/  netdev; TYPE_2__* conn; int /*<<< orphan*/  wiphy; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
struct cfg80211_connect_params {int /*<<< orphan*/  bssid; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  channel; int /*<<< orphan*/  vht_capa_mask; int /*<<< orphan*/  vht_capa; int /*<<< orphan*/  ht_capa_mask; int /*<<< orphan*/  ht_capa; int /*<<< orphan*/  flags; int /*<<< orphan*/  crypto; int /*<<< orphan*/  mfp; int /*<<< orphan*/  ie_len; int /*<<< orphan*/  ie; int /*<<< orphan*/  key_idx; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  auth_type; } ;
struct cfg80211_assoc_request {int use_mfp; int /*<<< orphan*/  vht_capa_mask; int /*<<< orphan*/  vht_capa; int /*<<< orphan*/  ht_capa_mask; int /*<<< orphan*/  ht_capa; int /*<<< orphan*/  flags; int /*<<< orphan*/  crypto; int /*<<< orphan*/  ie_len; int /*<<< orphan*/  ie; int /*<<< orphan*/  prev_bssid; } ;
struct TYPE_4__ {int state; int /*<<< orphan*/  prev_bssid; int /*<<< orphan*/  prev_bssid_valid; struct cfg80211_connect_params params; } ;
struct TYPE_3__ {int /*<<< orphan*/  assoc; int /*<<< orphan*/  auth; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  CFG80211_CONN_ASSOCIATE_NEXT 131 
 int CFG80211_CONN_ASSOCIATING ; 
#define  CFG80211_CONN_AUTHENTICATE_NEXT 130 
 int CFG80211_CONN_AUTHENTICATING ; 
#define  CFG80211_CONN_DEAUTH_ASSOC_FAIL 129 
#define  CFG80211_CONN_SCAN_AGAIN 128 
 int EINVAL ; 
 int /*<<< orphan*/  NL80211_MFP_NO ; 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 int __cfg80211_mlme_assoc (struct cfg80211_registered_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cfg80211_assoc_request*) ; 
 int __cfg80211_mlme_auth (struct cfg80211_registered_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cfg80211_mlme_deauth (struct cfg80211_registered_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int cfg80211_conn_scan (struct wireless_dev*) ; 
 struct cfg80211_registered_device* wiphy_to_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cfg80211_conn_do_work(struct wireless_dev *wdev)
{
	struct cfg80211_registered_device *rdev = wiphy_to_dev(wdev->wiphy);
	struct cfg80211_connect_params *params;
	struct cfg80211_assoc_request req = {};
	int err;

	ASSERT_WDEV_LOCK(wdev);

	if (!wdev->conn)
		return 0;

	params = &wdev->conn->params;

	switch (wdev->conn->state) {
	case CFG80211_CONN_SCAN_AGAIN:
		return cfg80211_conn_scan(wdev);
	case CFG80211_CONN_AUTHENTICATE_NEXT:
		BUG_ON(!rdev->ops->auth);
		wdev->conn->state = CFG80211_CONN_AUTHENTICATING;
		return __cfg80211_mlme_auth(rdev, wdev->netdev,
					    params->channel, params->auth_type,
					    params->bssid,
					    params->ssid, params->ssid_len,
					    NULL, 0,
					    params->key, params->key_len,
					    params->key_idx, NULL, 0);
	case CFG80211_CONN_ASSOCIATE_NEXT:
		BUG_ON(!rdev->ops->assoc);
		wdev->conn->state = CFG80211_CONN_ASSOCIATING;
		if (wdev->conn->prev_bssid_valid)
			req.prev_bssid = wdev->conn->prev_bssid;
		req.ie = params->ie;
		req.ie_len = params->ie_len;
		req.use_mfp = params->mfp != NL80211_MFP_NO;
		req.crypto = params->crypto;
		req.flags = params->flags;
		req.ht_capa = params->ht_capa;
		req.ht_capa_mask = params->ht_capa_mask;
		req.vht_capa = params->vht_capa;
		req.vht_capa_mask = params->vht_capa_mask;

		err = __cfg80211_mlme_assoc(rdev, wdev->netdev, params->channel,
					    params->bssid, params->ssid,
					    params->ssid_len, &req);
		if (err)
			__cfg80211_mlme_deauth(rdev, wdev->netdev, params->bssid,
					       NULL, 0,
					       WLAN_REASON_DEAUTH_LEAVING,
					       false);
		return err;
	case CFG80211_CONN_DEAUTH_ASSOC_FAIL:
		__cfg80211_mlme_deauth(rdev, wdev->netdev, params->bssid,
				       NULL, 0,
				       WLAN_REASON_DEAUTH_LEAVING, false);
		/* return an error so that we call __cfg80211_connect_result() */
		return -EINVAL;
	default:
		return 0;
	}
}