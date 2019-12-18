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
struct il_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  iw_mode; struct ieee80211_vif* vif; } ;
struct ieee80211_vif {int /*<<< orphan*/  type; int /*<<< orphan*/  addr; } ;
struct ieee80211_hw {struct il_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_MAC80211 (char*,int,...) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IL_WARN (char*,...) ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  il_is_ready_rf (struct il_priv*) ; 
 int il_set_mode (struct il_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int
il_mac_add_interface(struct ieee80211_hw *hw, struct ieee80211_vif *vif)
{
	struct il_priv *il = hw->priv;
	int err;
	bool reset;

	mutex_lock(&il->mutex);
	D_MAC80211("enter: type %d, addr %pM\n", vif->type, vif->addr);

	if (!il_is_ready_rf(il)) {
		IL_WARN("Try to add interface when device not ready\n");
		err = -EINVAL;
		goto out;
	}

	/*
	 * We do not support multiple virtual interfaces, but on hardware reset
	 * we have to add the same interface again.
	 */
	reset = (il->vif == vif);
	if (il->vif && !reset) {
		err = -EOPNOTSUPP;
		goto out;
	}

	il->vif = vif;
	il->iw_mode = vif->type;

	err = il_set_mode(il);
	if (err) {
		IL_WARN("Fail to set mode %d\n", vif->type);
		if (!reset) {
			il->vif = NULL;
			il->iw_mode = NL80211_IFTYPE_STATION;
		}
	}

out:
	D_MAC80211("leave err %d\n", err);
	mutex_unlock(&il->mutex);

	return err;
}