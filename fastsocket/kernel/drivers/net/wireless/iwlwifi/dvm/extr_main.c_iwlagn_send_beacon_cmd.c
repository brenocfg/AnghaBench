#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_9__ {int /*<<< orphan*/  life_time; } ;
struct TYPE_13__ {int tx_flags; int /*<<< orphan*/  rate_n_flags; TYPE_2__ stop_time; int /*<<< orphan*/  sta_id; int /*<<< orphan*/  len; } ;
struct iwl_tx_beacon_cmd {TYPE_6__ tx; } ;
struct iwl_priv {TYPE_7__* beacon_skb; int /*<<< orphan*/  mgmt_tx_ant; TYPE_5__* nvm_data; TYPE_1__* beacon_ctx; struct iwl_tx_beacon_cmd* beacon_cmd; int /*<<< orphan*/  mutex; } ;
struct iwl_host_cmd {int* len; void** dataflags; struct iwl_tx_beacon_cmd** data; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; } ;
struct TYPE_11__ {TYPE_3__* rates; } ;
struct ieee80211_tx_info {scalar_t__ band; TYPE_4__ control; } ;
struct TYPE_14__ {scalar_t__ len; struct iwl_tx_beacon_cmd* data; } ;
struct TYPE_12__ {int /*<<< orphan*/  valid_tx_ant; } ;
struct TYPE_10__ {scalar_t__ idx; int flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  bcast_sta_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SYNC ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IEEE80211_BAND_5GHZ ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (TYPE_7__*) ; 
 int IEEE80211_TX_RC_MCS ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*) ; 
 scalar_t__ IWL_FIRST_CCK_RATE ; 
 scalar_t__ IWL_FIRST_OFDM_RATE ; 
 void* IWL_HCMD_DFL_NOCOPY ; 
 scalar_t__ IWL_LAST_CCK_RATE ; 
 scalar_t__ RATE_MCS_CCK_MSK ; 
 int /*<<< orphan*/  REPLY_TX_BEACON ; 
 int TX_CMD_FLG_SEQ_CTL_MSK ; 
 int TX_CMD_FLG_STA_RATE_MSK ; 
 int TX_CMD_FLG_TSF_MSK ; 
 int /*<<< orphan*/  TX_CMD_LIFE_TIME_INFINITE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_ant_idx_to_flags (int /*<<< orphan*/ ) ; 
 int iwl_dvm_send_cmd (struct iwl_priv*,struct iwl_host_cmd*) ; 
 int /*<<< orphan*/  iwl_hw_set_rate_n_flags (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  iwl_set_beacon_tim (struct iwl_priv*,struct iwl_tx_beacon_cmd*,struct iwl_tx_beacon_cmd*,scalar_t__) ; 
 int /*<<< orphan*/  iwl_toggle_tx_ant (struct iwl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iwl_tx_beacon_cmd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwlagn_send_beacon_cmd(struct iwl_priv *priv)
{
	struct iwl_tx_beacon_cmd *tx_beacon_cmd;
	struct iwl_host_cmd cmd = {
		.id = REPLY_TX_BEACON,
		.flags = CMD_SYNC,
	};
	struct ieee80211_tx_info *info;
	u32 frame_size;
	u32 rate_flags;
	u32 rate;

	/*
	 * We have to set up the TX command, the TX Beacon command, and the
	 * beacon contents.
	 */

	lockdep_assert_held(&priv->mutex);

	if (!priv->beacon_ctx) {
		IWL_ERR(priv, "trying to build beacon w/o beacon context!\n");
		return 0;
	}

	if (WARN_ON(!priv->beacon_skb))
		return -EINVAL;

	/* Allocate beacon command */
	if (!priv->beacon_cmd)
		priv->beacon_cmd = kzalloc(sizeof(*tx_beacon_cmd), GFP_KERNEL);
	tx_beacon_cmd = priv->beacon_cmd;
	if (!tx_beacon_cmd)
		return -ENOMEM;

	frame_size = priv->beacon_skb->len;

	/* Set up TX command fields */
	tx_beacon_cmd->tx.len = cpu_to_le16((u16)frame_size);
	tx_beacon_cmd->tx.sta_id = priv->beacon_ctx->bcast_sta_id;
	tx_beacon_cmd->tx.stop_time.life_time = TX_CMD_LIFE_TIME_INFINITE;
	tx_beacon_cmd->tx.tx_flags = TX_CMD_FLG_SEQ_CTL_MSK |
		TX_CMD_FLG_TSF_MSK | TX_CMD_FLG_STA_RATE_MSK;

	/* Set up TX beacon command fields */
	iwl_set_beacon_tim(priv, tx_beacon_cmd, priv->beacon_skb->data,
			   frame_size);

	/* Set up packet rate and flags */
	info = IEEE80211_SKB_CB(priv->beacon_skb);

	/*
	 * Let's set up the rate at least somewhat correctly;
	 * it will currently not actually be used by the uCode,
	 * it uses the broadcast station's rate instead.
	 */
	if (info->control.rates[0].idx < 0 ||
	    info->control.rates[0].flags & IEEE80211_TX_RC_MCS)
		rate = 0;
	else
		rate = info->control.rates[0].idx;

	priv->mgmt_tx_ant = iwl_toggle_tx_ant(priv, priv->mgmt_tx_ant,
					      priv->nvm_data->valid_tx_ant);
	rate_flags = iwl_ant_idx_to_flags(priv->mgmt_tx_ant);

	/* In mac80211, rates for 5 GHz start at 0 */
	if (info->band == IEEE80211_BAND_5GHZ)
		rate += IWL_FIRST_OFDM_RATE;
	else if (rate >= IWL_FIRST_CCK_RATE && rate <= IWL_LAST_CCK_RATE)
		rate_flags |= RATE_MCS_CCK_MSK;

	tx_beacon_cmd->tx.rate_n_flags =
			iwl_hw_set_rate_n_flags(rate, rate_flags);

	/* Submit command */
	cmd.len[0] = sizeof(*tx_beacon_cmd);
	cmd.data[0] = tx_beacon_cmd;
	cmd.dataflags[0] = IWL_HCMD_DFL_NOCOPY;
	cmd.len[1] = frame_size;
	cmd.data[1] = priv->beacon_skb->data;
	cmd.dataflags[1] = IWL_HCMD_DFL_NOCOPY;

	return iwl_dvm_send_cmd(priv, &cmd);
}