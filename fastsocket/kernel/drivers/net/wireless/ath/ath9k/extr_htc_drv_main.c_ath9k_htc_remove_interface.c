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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_vif {int /*<<< orphan*/  type; int /*<<< orphan*/  addr; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct ath9k_htc_priv* priv; } ;
struct ath_common {int dummy; } ;
struct ath9k_htc_vif {int index; } ;
struct ath9k_htc_target_vif {int index; int /*<<< orphan*/  myaddr; } ;
struct ath9k_htc_priv {int vif_slot; scalar_t__ num_ap_vif; int rearm_ani; int /*<<< orphan*/  mutex; int /*<<< orphan*/  hw; int /*<<< orphan*/  nvifs; int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG ; 
 int /*<<< orphan*/  DEC_VIF (struct ath9k_htc_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_RESUME_ALL ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  WMI_CMD_BUF (int /*<<< orphan*/ ,struct ath9k_htc_target_vif*) ; 
 int /*<<< orphan*/  WMI_VAP_REMOVE_CMDID ; 
 int /*<<< orphan*/  ath9k_htc_ps_restore (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_ps_wakeup (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_remove_bslot (struct ath9k_htc_priv*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  ath9k_htc_remove_station (struct ath9k_htc_priv*,struct ieee80211_vif*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath9k_htc_set_bssid_mask (struct ath9k_htc_priv*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  ath9k_htc_set_opmode (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_stop_ani (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_vif_iter ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*,int) ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ath9k_htc_target_vif*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_htc_remove_interface(struct ieee80211_hw *hw,
				       struct ieee80211_vif *vif)
{
	struct ath9k_htc_priv *priv = hw->priv;
	struct ath_common *common = ath9k_hw_common(priv->ah);
	struct ath9k_htc_vif *avp = (void *)vif->drv_priv;
	struct ath9k_htc_target_vif hvif;
	int ret = 0;
	u8 cmd_rsp;

	mutex_lock(&priv->mutex);
	ath9k_htc_ps_wakeup(priv);

	memset(&hvif, 0, sizeof(struct ath9k_htc_target_vif));
	memcpy(&hvif.myaddr, vif->addr, ETH_ALEN);
	hvif.index = avp->index;
	WMI_CMD_BUF(WMI_VAP_REMOVE_CMDID, &hvif);
	if (ret) {
		ath_err(common, "Unable to remove interface at idx: %d\n",
			avp->index);
	}
	priv->nvifs--;
	priv->vif_slot &= ~(1 << avp->index);

	ath9k_htc_remove_station(priv, vif, NULL);

	DEC_VIF(priv, vif->type);

	if ((vif->type == NL80211_IFTYPE_AP) ||
	    (vif->type == NL80211_IFTYPE_ADHOC))
		ath9k_htc_remove_bslot(priv, vif);

	ath9k_htc_set_opmode(priv);

	ath9k_htc_set_bssid_mask(priv, vif);

	/*
	 * Stop ANI only if there are no associated station interfaces.
	 */
	if ((vif->type == NL80211_IFTYPE_AP) && (priv->num_ap_vif == 0)) {
		priv->rearm_ani = false;
		ieee80211_iterate_active_interfaces_atomic(
			priv->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
			ath9k_htc_vif_iter, priv);
		if (!priv->rearm_ani)
			ath9k_htc_stop_ani(priv);
	}

	ath_dbg(common, CONFIG, "Detach Interface at idx: %d\n", avp->index);

	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);
}