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
struct il_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  bssid; int /*<<< orphan*/  iw_mode; struct ieee80211_vif* vif; } ;
struct ieee80211_vif {int /*<<< orphan*/  addr; int /*<<< orphan*/  type; } ;
struct ieee80211_hw {struct il_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_MAC80211 (char*,...) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  NL80211_IFTYPE_UNSPECIFIED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  il_teardown_interface (struct il_priv*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void
il_mac_remove_interface(struct ieee80211_hw *hw, struct ieee80211_vif *vif)
{
	struct il_priv *il = hw->priv;

	mutex_lock(&il->mutex);
	D_MAC80211("enter: type %d, addr %pM\n", vif->type, vif->addr);

	WARN_ON(il->vif != vif);
	il->vif = NULL;
	il->iw_mode = NL80211_IFTYPE_UNSPECIFIED;
	il_teardown_interface(il, vif);
	memset(il->bssid, 0, ETH_ALEN);

	D_MAC80211("leave\n");
	mutex_unlock(&il->mutex);
}