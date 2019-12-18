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
struct il_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  scan_band; struct ieee80211_vif* scan_vif; struct cfg80211_scan_request* scan_request; int /*<<< orphan*/  status; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct il_priv* priv; } ;
struct cfg80211_scan_request {scalar_t__ n_channels; TYPE_1__** channels; } ;
struct TYPE_2__ {int /*<<< orphan*/  band; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_MAC80211 (char*,...) ; 
 int /*<<< orphan*/  D_SCAN (char*) ; 
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  IL_ERR (char*) ; 
 int /*<<< orphan*/  S_SCANNING ; 
 int il_scan_initiate (struct il_priv*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
il_mac_hw_scan(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
	       struct cfg80211_scan_request *req)
{
	struct il_priv *il = hw->priv;
	int ret;

	if (req->n_channels == 0) {
		IL_ERR("Can not scan on no channels.\n");
		return -EINVAL;
	}

	mutex_lock(&il->mutex);
	D_MAC80211("enter\n");

	if (test_bit(S_SCANNING, &il->status)) {
		D_SCAN("Scan already in progress.\n");
		ret = -EAGAIN;
		goto out_unlock;
	}

	/* mac80211 will only ask for one band at a time */
	il->scan_request = req;
	il->scan_vif = vif;
	il->scan_band = req->channels[0]->band;

	ret = il_scan_initiate(il, vif);

out_unlock:
	D_MAC80211("leave ret %d\n", ret);
	mutex_unlock(&il->mutex);

	return ret;
}