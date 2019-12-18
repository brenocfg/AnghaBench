#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wireless_dev {scalar_t__ sme_state; TYPE_2__* current_bss; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct ieee80211_channel {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  vht_capa_mod_mask; int /*<<< orphan*/  ht_capa_mod_mask; } ;
struct cfg80211_registered_device {TYPE_3__ wiphy; } ;
struct cfg80211_assoc_request {int /*<<< orphan*/  bss; int /*<<< orphan*/  vht_capa_mask; int /*<<< orphan*/  ht_capa_mask; scalar_t__ prev_bssid; } ;
struct TYPE_5__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_6__ {TYPE_1__ pub; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 scalar_t__ CFG80211_SME_CONNECTED ; 
 scalar_t__ CFG80211_SME_CONNECTING ; 
 int /*<<< orphan*/  CHAN_MODE_SHARED ; 
 int EALREADY ; 
 int ENOENT ; 
 int /*<<< orphan*/  WLAN_CAPABILITY_ESS ; 
 int cfg80211_can_use_chan (struct cfg80211_registered_device*,struct wireless_dev*,struct ieee80211_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_get_bss (TYPE_3__*,struct ieee80211_channel*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_oper_and_ht_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_oper_and_vht_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_put_bss (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,scalar_t__) ; 
 int rdev_assoc (struct cfg80211_registered_device*,struct net_device*,struct cfg80211_assoc_request*) ; 

int __cfg80211_mlme_assoc(struct cfg80211_registered_device *rdev,
			  struct net_device *dev,
			  struct ieee80211_channel *chan,
			  const u8 *bssid,
			  const u8 *ssid, int ssid_len,
			  struct cfg80211_assoc_request *req)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	int err;
	bool was_connected = false;

	ASSERT_WDEV_LOCK(wdev);

	if (wdev->current_bss && req->prev_bssid &&
	    ether_addr_equal(wdev->current_bss->pub.bssid, req->prev_bssid)) {
		/*
		 * Trying to reassociate: Allow this to proceed and let the old
		 * association to be dropped when the new one is completed.
		 */
		if (wdev->sme_state == CFG80211_SME_CONNECTED) {
			was_connected = true;
			wdev->sme_state = CFG80211_SME_CONNECTING;
		}
	} else if (wdev->current_bss)
		return -EALREADY;

	cfg80211_oper_and_ht_capa(&req->ht_capa_mask,
				  rdev->wiphy.ht_capa_mod_mask);
	cfg80211_oper_and_vht_capa(&req->vht_capa_mask,
				   rdev->wiphy.vht_capa_mod_mask);

	req->bss = cfg80211_get_bss(&rdev->wiphy, chan, bssid, ssid, ssid_len,
				    WLAN_CAPABILITY_ESS, WLAN_CAPABILITY_ESS);
	if (!req->bss) {
		if (was_connected)
			wdev->sme_state = CFG80211_SME_CONNECTED;
		return -ENOENT;
	}

	err = cfg80211_can_use_chan(rdev, wdev, chan, CHAN_MODE_SHARED);
	if (err)
		goto out;

	err = rdev_assoc(rdev, dev, req);

out:
	if (err) {
		if (was_connected)
			wdev->sme_state = CFG80211_SME_CONNECTED;
		cfg80211_put_bss(&rdev->wiphy, req->bss);
	}

	return err;
}