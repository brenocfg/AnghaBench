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
struct ieee80211_vif {int /*<<< orphan*/  bss_conf; int /*<<< orphan*/  addr; int /*<<< orphan*/  type; } ;
struct ieee80211_hw {int dummy; } ;
struct b43_wldev {int dummy; } ;
struct b43_wl {int operating; int /*<<< orphan*/  mutex; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  if_type; struct ieee80211_vif* vif; struct b43_wldev* current_dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  NL80211_IFTYPE_WDS ; 
 int /*<<< orphan*/  b43_adjust_opmode (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_op_bss_info_changed (struct ieee80211_hw*,struct ieee80211_vif*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_set_pretbtt (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_set_synth_pu_delay (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_upload_card_macaddress (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43dbg (struct b43_wl*,char*,int /*<<< orphan*/ ) ; 
 struct b43_wl* hw_to_b43_wl (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int b43_op_add_interface(struct ieee80211_hw *hw,
				struct ieee80211_vif *vif)
{
	struct b43_wl *wl = hw_to_b43_wl(hw);
	struct b43_wldev *dev;
	int err = -EOPNOTSUPP;

	/* TODO: allow WDS/AP devices to coexist */

	if (vif->type != NL80211_IFTYPE_AP &&
	    vif->type != NL80211_IFTYPE_MESH_POINT &&
	    vif->type != NL80211_IFTYPE_STATION &&
	    vif->type != NL80211_IFTYPE_WDS &&
	    vif->type != NL80211_IFTYPE_ADHOC)
		return -EOPNOTSUPP;

	mutex_lock(&wl->mutex);
	if (wl->operating)
		goto out_mutex_unlock;

	b43dbg(wl, "Adding Interface type %d\n", vif->type);

	dev = wl->current_dev;
	wl->operating = true;
	wl->vif = vif;
	wl->if_type = vif->type;
	memcpy(wl->mac_addr, vif->addr, ETH_ALEN);

	b43_adjust_opmode(dev);
	b43_set_pretbtt(dev);
	b43_set_synth_pu_delay(dev, 0);
	b43_upload_card_macaddress(dev);

	err = 0;
 out_mutex_unlock:
	mutex_unlock(&wl->mutex);

	if (err == 0)
		b43_op_bss_info_changed(hw, vif, &vif->bss_conf, ~0);

	return err;
}