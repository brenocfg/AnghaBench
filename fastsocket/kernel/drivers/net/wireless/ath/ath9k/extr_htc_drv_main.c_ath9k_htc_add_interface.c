#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_vif {int const type; int /*<<< orphan*/  addr; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct ath9k_htc_priv* priv; } ;
struct ath_common {int dummy; } ;
struct ath9k_htc_vif {int index; } ;
struct ath9k_htc_target_vif {int index; int /*<<< orphan*/  rtsthreshold; int /*<<< orphan*/  opmode; int /*<<< orphan*/  myaddr; } ;
struct ath9k_htc_priv {int vif_slot; int /*<<< orphan*/  mutex; TYPE_1__* ah; int /*<<< orphan*/  op_flags; int /*<<< orphan*/  nvifs; } ;
struct TYPE_3__ {int const opmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  HTC_M_HOSTAP ; 
 int /*<<< orphan*/  HTC_M_IBSS ; 
 int /*<<< orphan*/  HTC_M_STA ; 
 int /*<<< orphan*/  INC_VIF (struct ath9k_htc_priv*,int const) ; 
#define  NL80211_IFTYPE_ADHOC 130 
#define  NL80211_IFTYPE_AP 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  OP_ANI_RUNNING ; 
 int /*<<< orphan*/  WMI_CMD_BUF (int /*<<< orphan*/ ,struct ath9k_htc_target_vif*) ; 
 int /*<<< orphan*/  WMI_VAP_CREATE_CMDID ; 
 int /*<<< orphan*/  WMI_VAP_REMOVE_CMDID ; 
 int ath9k_htc_add_station (struct ath9k_htc_priv*,struct ieee80211_vif*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath9k_htc_assign_bslot (struct ath9k_htc_priv*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  ath9k_htc_ps_restore (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_ps_wakeup (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_set_bssid_mask (struct ath9k_htc_priv*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  ath9k_htc_set_opmode (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_start_ani (struct ath9k_htc_priv*) ; 
 struct ath_common* ath9k_hw_common (TYPE_1__*) ; 
 int /*<<< orphan*/  ath9k_hw_set_tsfadjust (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int const,int) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*,int const) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int ffz (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ath9k_htc_target_vif*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath9k_htc_add_interface(struct ieee80211_hw *hw,
				   struct ieee80211_vif *vif)
{
	struct ath9k_htc_priv *priv = hw->priv;
	struct ath9k_htc_vif *avp = (void *)vif->drv_priv;
	struct ath_common *common = ath9k_hw_common(priv->ah);
	struct ath9k_htc_target_vif hvif;
	int ret = 0;
	u8 cmd_rsp;

	mutex_lock(&priv->mutex);

	ath9k_htc_ps_wakeup(priv);
	memset(&hvif, 0, sizeof(struct ath9k_htc_target_vif));
	memcpy(&hvif.myaddr, vif->addr, ETH_ALEN);

	switch (vif->type) {
	case NL80211_IFTYPE_STATION:
		hvif.opmode = HTC_M_STA;
		break;
	case NL80211_IFTYPE_ADHOC:
		hvif.opmode = HTC_M_IBSS;
		break;
	case NL80211_IFTYPE_AP:
		hvif.opmode = HTC_M_HOSTAP;
		break;
	default:
		ath_err(common,
			"Interface type %d not yet supported\n", vif->type);
		ret = -EOPNOTSUPP;
		goto out;
	}

	/* Index starts from zero on the target */
	avp->index = hvif.index = ffz(priv->vif_slot);
	hvif.rtsthreshold = cpu_to_be16(2304);
	WMI_CMD_BUF(WMI_VAP_CREATE_CMDID, &hvif);
	if (ret)
		goto out;

	/*
	 * We need a node in target to tx mgmt frames
	 * before association.
	 */
	ret = ath9k_htc_add_station(priv, vif, NULL);
	if (ret) {
		WMI_CMD_BUF(WMI_VAP_REMOVE_CMDID, &hvif);
		goto out;
	}

	ath9k_htc_set_bssid_mask(priv, vif);

	priv->vif_slot |= (1 << avp->index);
	priv->nvifs++;

	INC_VIF(priv, vif->type);

	if ((vif->type == NL80211_IFTYPE_AP) ||
	    (vif->type == NL80211_IFTYPE_ADHOC))
		ath9k_htc_assign_bslot(priv, vif);

	ath9k_htc_set_opmode(priv);

	if ((priv->ah->opmode == NL80211_IFTYPE_AP) &&
	    !test_bit(OP_ANI_RUNNING, &priv->op_flags)) {
		ath9k_hw_set_tsfadjust(priv->ah, true);
		ath9k_htc_start_ani(priv);
	}

	ath_dbg(common, CONFIG, "Attach a VIF of type: %d at idx: %d\n",
		vif->type, avp->index);

out:
	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);

	return ret;
}