#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {struct ieee80211_channel* chan; } ;
struct TYPE_9__ {int flags; TYPE_2__ chandef; } ;
struct ieee80211_hw {TYPE_4__ conf; } ;
struct ieee80211_conf {int dummy; } ;
struct ieee80211_channel {int /*<<< orphan*/  center_freq; } ;
struct ath_hw {TYPE_3__* curchan; } ;
struct ath_common {TYPE_1__* hw; } ;
struct ath9k_hw_cal_data {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  cleanup_timer; } ;
struct ath9k_htc_priv {TYPE_5__ tx; int /*<<< orphan*/  op_flags; int /*<<< orphan*/  htc; int /*<<< orphan*/  curtxpow; int /*<<< orphan*/  txpowlimit; struct ath9k_hw_cal_data caldata; struct ath_hw* ah; } ;
struct ath9k_channel {int dummy; } ;
typedef  enum htc_phymode { ____Placeholder_htc_phymode } htc_phymode ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_8__ {int /*<<< orphan*/  channel; } ;
struct TYPE_6__ {struct ieee80211_conf conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH9K_HTC_TX_CLEANUP_INTERVAL ; 
 int /*<<< orphan*/  CONFIG ; 
 int EIO ; 
 int IEEE80211_CONF_OFFCHANNEL ; 
 int /*<<< orphan*/  OP_INVALID ; 
 int /*<<< orphan*/  OP_SCANNING ; 
 int /*<<< orphan*/  WMI_CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WMI_CMD_BUF (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WMI_DISABLE_INTR_CMDID ; 
 int /*<<< orphan*/  WMI_DRAIN_TXQ_ALL_CMDID ; 
 int /*<<< orphan*/  WMI_ENABLE_INTR_CMDID ; 
 int /*<<< orphan*/  WMI_SET_MODE_CMDID ; 
 int /*<<< orphan*/  WMI_START_RECV_CMDID ; 
 int /*<<< orphan*/  WMI_STOP_RECV_CMDID ; 
 int /*<<< orphan*/  ath9k_cmn_update_txpow (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath9k_host_rx_init (struct ath9k_htc_priv*) ; 
 int ath9k_htc_get_curmode (struct ath9k_htc_priv*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ath9k_htc_ps_restore (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_ps_wakeup (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_tx_drain (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_vif_reconfig (struct ath9k_htc_priv*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int ath9k_hw_reset (struct ath_hw*,struct ath9k_channel*,struct ath9k_hw_cal_data*,int) ; 
 int /*<<< orphan*/  ath9k_wmi_event_drain (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  conf_is_ht (struct ieee80211_conf*) ; 
 int /*<<< orphan*/  conf_is_ht40 (struct ieee80211_conf*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htc_start (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath9k_htc_set_channel(struct ath9k_htc_priv *priv,
				 struct ieee80211_hw *hw,
				 struct ath9k_channel *hchan)
{
	struct ath_hw *ah = priv->ah;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ieee80211_conf *conf = &common->hw->conf;
	bool fastcc;
	struct ieee80211_channel *channel = hw->conf.chandef.chan;
	struct ath9k_hw_cal_data *caldata = NULL;
	enum htc_phymode mode;
	__be16 htc_mode;
	u8 cmd_rsp;
	int ret;

	if (test_bit(OP_INVALID, &priv->op_flags))
		return -EIO;

	fastcc = !!(hw->conf.flags & IEEE80211_CONF_OFFCHANNEL);

	ath9k_htc_ps_wakeup(priv);

	del_timer_sync(&priv->tx.cleanup_timer);
	ath9k_htc_tx_drain(priv);

	WMI_CMD(WMI_DISABLE_INTR_CMDID);
	WMI_CMD(WMI_DRAIN_TXQ_ALL_CMDID);
	WMI_CMD(WMI_STOP_RECV_CMDID);

	ath9k_wmi_event_drain(priv);

	ath_dbg(common, CONFIG,
		"(%u MHz) -> (%u MHz), HT: %d, HT40: %d fastcc: %d\n",
		priv->ah->curchan->channel,
		channel->center_freq, conf_is_ht(conf), conf_is_ht40(conf),
		fastcc);

	if (!fastcc)
		caldata = &priv->caldata;

	ret = ath9k_hw_reset(ah, hchan, caldata, fastcc);
	if (ret) {
		ath_err(common,
			"Unable to reset channel (%u Mhz) reset status %d\n",
			channel->center_freq, ret);
		goto err;
	}

	ath9k_cmn_update_txpow(ah, priv->curtxpow, priv->txpowlimit,
			       &priv->curtxpow);

	WMI_CMD(WMI_START_RECV_CMDID);
	if (ret)
		goto err;

	ath9k_host_rx_init(priv);

	mode = ath9k_htc_get_curmode(priv, hchan);
	htc_mode = cpu_to_be16(mode);
	WMI_CMD_BUF(WMI_SET_MODE_CMDID, &htc_mode);
	if (ret)
		goto err;

	WMI_CMD(WMI_ENABLE_INTR_CMDID);
	if (ret)
		goto err;

	htc_start(priv->htc);

	if (!test_bit(OP_SCANNING, &priv->op_flags) &&
	    !(hw->conf.flags & IEEE80211_CONF_OFFCHANNEL))
		ath9k_htc_vif_reconfig(priv);

	mod_timer(&priv->tx.cleanup_timer,
		  jiffies + msecs_to_jiffies(ATH9K_HTC_TX_CLEANUP_INTERVAL));

err:
	ath9k_htc_ps_restore(priv);
	return ret;
}