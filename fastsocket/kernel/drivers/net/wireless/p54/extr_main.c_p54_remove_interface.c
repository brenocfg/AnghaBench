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
struct p54_common {int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  bssid; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  mode; int /*<<< orphan*/  beacon_comp; int /*<<< orphan*/  beacon_req_id; int /*<<< orphan*/ * vif; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct p54_common* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MONITOR ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p54_setup_mac (struct p54_common*) ; 
 int /*<<< orphan*/  p54_tx_cancel (struct p54_common*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void p54_remove_interface(struct ieee80211_hw *dev,
				 struct ieee80211_vif *vif)
{
	struct p54_common *priv = dev->priv;

	mutex_lock(&priv->conf_mutex);
	priv->vif = NULL;

	/*
	 * LMAC API 3.2.2 states that any active beacon template must be
	 * canceled by the driver before attempting a mode transition.
	 */
	if (le32_to_cpu(priv->beacon_req_id) != 0) {
		p54_tx_cancel(priv, priv->beacon_req_id);
		wait_for_completion_interruptible_timeout(&priv->beacon_comp, HZ);
	}
	priv->mode = NL80211_IFTYPE_MONITOR;
	memset(priv->mac_addr, 0, ETH_ALEN);
	memset(priv->bssid, 0, ETH_ALEN);
	p54_setup_mac(priv);
	mutex_unlock(&priv->conf_mutex);
}