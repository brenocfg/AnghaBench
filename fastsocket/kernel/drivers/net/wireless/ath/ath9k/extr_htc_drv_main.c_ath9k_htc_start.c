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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {struct ieee80211_channel* chan; } ;
struct TYPE_5__ {TYPE_1__ chandef; } ;
struct ieee80211_hw {TYPE_2__ conf; struct ath9k_htc_priv* priv; } ;
struct ieee80211_channel {int /*<<< orphan*/  center_freq; } ;
struct ath_hw {int /*<<< orphan*/  caldata; } ;
struct ath_common {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  cleanup_timer; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  flags; } ;
struct ath9k_htc_priv {int /*<<< orphan*/  mutex; TYPE_3__ tx; int /*<<< orphan*/  htc; int /*<<< orphan*/  op_flags; int /*<<< orphan*/  curtxpow; int /*<<< orphan*/  txpowlimit; struct ath_hw* ah; } ;
struct ath9k_channel {int dummy; } ;
typedef  enum htc_phymode { ____Placeholder_htc_phymode } htc_phymode ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ATH9K_HTC_OP_TX_QUEUES_STOP ; 
 int /*<<< orphan*/  ATH9K_HTC_TX_CLEANUP_INTERVAL ; 
 int /*<<< orphan*/  ATH9K_PM_AWAKE ; 
 int /*<<< orphan*/  CONFIG ; 
 int /*<<< orphan*/  OP_INVALID ; 
 int /*<<< orphan*/  WMI_ATH_INIT_CMDID ; 
 int /*<<< orphan*/  WMI_CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WMI_CMD_BUF (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WMI_FLUSH_RECV_CMDID ; 
 int /*<<< orphan*/  WMI_SET_MODE_CMDID ; 
 int /*<<< orphan*/  WMI_START_RECV_CMDID ; 
 struct ath9k_channel* ath9k_cmn_get_curchannel (struct ieee80211_hw*,struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_cmn_update_txpow (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath9k_host_rx_init (struct ath9k_htc_priv*) ; 
 int ath9k_htc_get_curmode (struct ath9k_htc_priv*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ath9k_htc_setpower (struct ath9k_htc_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_htc_start_btcoex (struct ath9k_htc_priv*) ; 
 int ath9k_htc_update_cap_target (struct ath9k_htc_priv*,int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int ath9k_hw_reset (struct ath_hw*,struct ath9k_channel*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  htc_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_wake_queues (struct ieee80211_hw*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath9k_htc_start(struct ieee80211_hw *hw)
{
	struct ath9k_htc_priv *priv = hw->priv;
	struct ath_hw *ah = priv->ah;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ieee80211_channel *curchan = hw->conf.chandef.chan;
	struct ath9k_channel *init_channel;
	int ret = 0;
	enum htc_phymode mode;
	__be16 htc_mode;
	u8 cmd_rsp;

	mutex_lock(&priv->mutex);

	ath_dbg(common, CONFIG,
		"Starting driver with initial channel: %d MHz\n",
		curchan->center_freq);

	/* Ensure that HW is awake before flushing RX */
	ath9k_htc_setpower(priv, ATH9K_PM_AWAKE);
	WMI_CMD(WMI_FLUSH_RECV_CMDID);

	/* setup initial channel */
	init_channel = ath9k_cmn_get_curchannel(hw, ah);

	ret = ath9k_hw_reset(ah, init_channel, ah->caldata, false);
	if (ret) {
		ath_err(common,
			"Unable to reset hardware; reset status %d (freq %u MHz)\n",
			ret, curchan->center_freq);
		mutex_unlock(&priv->mutex);
		return ret;
	}

	ath9k_cmn_update_txpow(ah, priv->curtxpow, priv->txpowlimit,
			       &priv->curtxpow);

	mode = ath9k_htc_get_curmode(priv, init_channel);
	htc_mode = cpu_to_be16(mode);
	WMI_CMD_BUF(WMI_SET_MODE_CMDID, &htc_mode);
	WMI_CMD(WMI_ATH_INIT_CMDID);
	WMI_CMD(WMI_START_RECV_CMDID);

	ath9k_host_rx_init(priv);

	ret = ath9k_htc_update_cap_target(priv, 0);
	if (ret)
		ath_dbg(common, CONFIG,
			"Failed to update capability in target\n");

	clear_bit(OP_INVALID, &priv->op_flags);
	htc_start(priv->htc);

	spin_lock_bh(&priv->tx.tx_lock);
	priv->tx.flags &= ~ATH9K_HTC_OP_TX_QUEUES_STOP;
	spin_unlock_bh(&priv->tx.tx_lock);

	ieee80211_wake_queues(hw);

	mod_timer(&priv->tx.cleanup_timer,
		  jiffies + msecs_to_jiffies(ATH9K_HTC_TX_CLEANUP_INTERVAL));

	ath9k_htc_start_btcoex(priv);

	mutex_unlock(&priv->mutex);

	return ret;
}