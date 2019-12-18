#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u16 ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct iwl_wipan_noa_data {size_t length; struct ieee80211_hdr* data; } ;
struct iwl_tx_cmd {int /*<<< orphan*/  hdr; int /*<<< orphan*/  len; } ;
struct TYPE_4__ {scalar_t__ state; int txq_id; } ;
struct iwl_tid_data {int seq_number; TYPE_2__ agg; } ;
struct iwl_station_priv {int /*<<< orphan*/  pending_frames; scalar_t__ client; scalar_t__ asleep; } ;
struct iwl_rxon_context {size_t bcast_sta_id; int mcast_queue; int* ac_to_queue; scalar_t__ payload; } ;
struct iwl_priv {int* queue_to_mac80211; int /*<<< orphan*/  sta_lock; int /*<<< orphan*/  trans; struct iwl_tid_data** tid_data; int /*<<< orphan*/  noa_data; struct iwl_rxon_context* contexts; } ;
struct iwl_device_cmd {size_t bcast_sta_id; int mcast_queue; int* ac_to_queue; scalar_t__ payload; } ;
struct TYPE_3__ {scalar_t__ hw_key; scalar_t__ vif; } ;
struct ieee80211_tx_info {int flags; int hw_queue; struct iwl_rxon_context** driver_data; struct iwl_rxon_context status; TYPE_1__ control; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; int /*<<< orphan*/  seq_ctrl; int /*<<< orphan*/  addr1; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IEEE80211_FCTL_MOREDATA ; 
 size_t IEEE80211_QOS_CTL_TID_MASK ; 
 int IEEE80211_SCTL_FRAG ; 
 int IEEE80211_SCTL_SEQ ; 
 int /*<<< orphan*/  IEEE80211_SEQ_TO_SN (int) ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 int IEEE80211_TX_CTL_NO_PS_BUFFER ; 
 int IEEE80211_TX_CTL_SEND_AFTER_DTIM ; 
 int IEEE80211_TX_CTL_TX_OFFCHAN ; 
 scalar_t__ IWL_AGG_OFF ; 
 scalar_t__ IWL_AGG_ON ; 
 int IWL_AUX_QUEUE ; 
 int /*<<< orphan*/  IWL_DEBUG_DROP (struct iwl_priv*,char*,...) ; 
 int /*<<< orphan*/  IWL_DEBUG_TX (struct iwl_priv*,char*,...) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*,size_t,size_t,...) ; 
 size_t IWL_INVALID_STATION ; 
 size_t IWL_MAX_TID_COUNT ; 
 size_t IWL_RXON_CTX_BSS ; 
 scalar_t__ WARN_ONCE (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 size_t* ieee80211_get_qos_ctl (struct ieee80211_hdr*) ; 
 int /*<<< orphan*/  ieee80211_has_morefrags (int /*<<< orphan*/ ) ; 
 size_t ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_assoc_req (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_auth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_data (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 int ieee80211_is_probe_resp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_qos_nullfunc (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_reassoc_req (int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_is_rfkill (struct iwl_priv*) ; 
 struct iwl_rxon_context* iwl_rxon_ctx_from_vif (scalar_t__) ; 
 int /*<<< orphan*/  iwl_scan_offchannel_skb (struct iwl_priv*) ; 
 size_t iwl_sta_id_or_broadcast (struct iwl_rxon_context*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  iwl_sta_modify_sleep_tx_count (struct iwl_priv*,size_t,int) ; 
 struct iwl_rxon_context* iwl_trans_alloc_tx_cmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_free_tx_cmd (int /*<<< orphan*/ ,struct iwl_rxon_context*) ; 
 scalar_t__ iwl_trans_tx (int /*<<< orphan*/ ,struct sk_buff*,struct iwl_rxon_context*,int) ; 
 int /*<<< orphan*/  iwlagn_tx_cmd_build_basic (struct iwl_priv*,struct sk_buff*,struct iwl_tx_cmd*,struct ieee80211_tx_info*,struct ieee80211_hdr*,size_t) ; 
 int /*<<< orphan*/  iwlagn_tx_cmd_build_hwcrypto (struct iwl_priv*,struct ieee80211_tx_info*,struct iwl_tx_cmd*,struct sk_buff*) ; 
 int /*<<< orphan*/  iwlagn_tx_cmd_build_rate (struct iwl_priv*,struct iwl_tx_cmd*,struct ieee80211_tx_info*,struct ieee80211_sta*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct ieee80211_hdr*,size_t) ; 
 int /*<<< orphan*/  memset (struct iwl_rxon_context*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pskb_expand_head (struct sk_buff*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 struct iwl_wipan_noa_data* rcu_dereference (int /*<<< orphan*/ ) ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int iwlagn_tx_skb(struct iwl_priv *priv,
		  struct ieee80211_sta *sta,
		  struct sk_buff *skb)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct iwl_station_priv *sta_priv = NULL;
	struct iwl_rxon_context *ctx = &priv->contexts[IWL_RXON_CTX_BSS];
	struct iwl_device_cmd *dev_cmd;
	struct iwl_tx_cmd *tx_cmd;
	__le16 fc;
	u8 hdr_len;
	u16 len, seq_number = 0;
	u8 sta_id, tid = IWL_MAX_TID_COUNT;
	bool is_agg = false, is_data_qos = false;
	int txq_id;

	if (info->control.vif)
		ctx = iwl_rxon_ctx_from_vif(info->control.vif);

	if (iwl_is_rfkill(priv)) {
		IWL_DEBUG_DROP(priv, "Dropping - RF KILL\n");
		goto drop_unlock_priv;
	}

	fc = hdr->frame_control;

#ifdef CONFIG_IWLWIFI_DEBUG
	if (ieee80211_is_auth(fc))
		IWL_DEBUG_TX(priv, "Sending AUTH frame\n");
	else if (ieee80211_is_assoc_req(fc))
		IWL_DEBUG_TX(priv, "Sending ASSOC frame\n");
	else if (ieee80211_is_reassoc_req(fc))
		IWL_DEBUG_TX(priv, "Sending REASSOC frame\n");
#endif

	if (unlikely(ieee80211_is_probe_resp(fc))) {
		struct iwl_wipan_noa_data *noa_data =
			rcu_dereference(priv->noa_data);

		if (noa_data &&
		    pskb_expand_head(skb, 0, noa_data->length,
				     GFP_ATOMIC) == 0) {
			memcpy(skb_put(skb, noa_data->length),
			       noa_data->data, noa_data->length);
			hdr = (struct ieee80211_hdr *)skb->data;
		}
	}

	hdr_len = ieee80211_hdrlen(fc);

	/* For management frames use broadcast id to do not break aggregation */
	if (!ieee80211_is_data(fc))
		sta_id = ctx->bcast_sta_id;
	else {
		/* Find index into station table for destination station */
		sta_id = iwl_sta_id_or_broadcast(ctx, sta);
		if (sta_id == IWL_INVALID_STATION) {
			IWL_DEBUG_DROP(priv, "Dropping - INVALID STATION: %pM\n",
				       hdr->addr1);
			goto drop_unlock_priv;
		}
	}

	if (sta)
		sta_priv = (void *)sta->drv_priv;

	if (sta_priv && sta_priv->asleep &&
	    (info->flags & IEEE80211_TX_CTL_NO_PS_BUFFER)) {
		/*
		 * This sends an asynchronous command to the device,
		 * but we can rely on it being processed before the
		 * next frame is processed -- and the next frame to
		 * this station is the one that will consume this
		 * counter.
		 * For now set the counter to just 1 since we do not
		 * support uAPSD yet.
		 *
		 * FIXME: If we get two non-bufferable frames one
		 * after the other, we might only send out one of
		 * them because this is racy.
		 */
		iwl_sta_modify_sleep_tx_count(priv, sta_id, 1);
	}

	dev_cmd = iwl_trans_alloc_tx_cmd(priv->trans);

	if (unlikely(!dev_cmd))
		goto drop_unlock_priv;

	memset(dev_cmd, 0, sizeof(*dev_cmd));
	tx_cmd = (struct iwl_tx_cmd *) dev_cmd->payload;

	/* Total # bytes to be transmitted */
	len = (u16)skb->len;
	tx_cmd->len = cpu_to_le16(len);

	if (info->control.hw_key)
		iwlagn_tx_cmd_build_hwcrypto(priv, info, tx_cmd, skb);

	/* TODO need this for burst mode later on */
	iwlagn_tx_cmd_build_basic(priv, skb, tx_cmd, info, hdr, sta_id);

	iwlagn_tx_cmd_build_rate(priv, tx_cmd, info, sta, fc);

	memset(&info->status, 0, sizeof(info->status));

	info->driver_data[0] = ctx;
	info->driver_data[1] = dev_cmd;
	/* From now on, we cannot access info->control */

	spin_lock(&priv->sta_lock);

	if (ieee80211_is_data_qos(fc) && !ieee80211_is_qos_nullfunc(fc)) {
		u8 *qc = NULL;
		struct iwl_tid_data *tid_data;
		qc = ieee80211_get_qos_ctl(hdr);
		tid = qc[0] & IEEE80211_QOS_CTL_TID_MASK;
		if (WARN_ON_ONCE(tid >= IWL_MAX_TID_COUNT))
			goto drop_unlock_sta;
		tid_data = &priv->tid_data[sta_id][tid];

		/* aggregation is on for this <sta,tid> */
		if (info->flags & IEEE80211_TX_CTL_AMPDU &&
		    tid_data->agg.state != IWL_AGG_ON) {
			IWL_ERR(priv, "TX_CTL_AMPDU while not in AGG:"
				" Tx flags = 0x%08x, agg.state = %d",
				info->flags, tid_data->agg.state);
			IWL_ERR(priv, "sta_id = %d, tid = %d seq_num = %d",
				sta_id, tid,
				IEEE80211_SEQ_TO_SN(tid_data->seq_number));
			goto drop_unlock_sta;
		}

		/* We can receive packets from the stack in IWL_AGG_{ON,OFF}
		 * only. Check this here.
		 */
		if (WARN_ONCE(tid_data->agg.state != IWL_AGG_ON &&
			      tid_data->agg.state != IWL_AGG_OFF,
		    "Tx while agg.state = %d", tid_data->agg.state))
			goto drop_unlock_sta;

		seq_number = tid_data->seq_number;
		seq_number &= IEEE80211_SCTL_SEQ;
		hdr->seq_ctrl &= cpu_to_le16(IEEE80211_SCTL_FRAG);
		hdr->seq_ctrl |= cpu_to_le16(seq_number);
		seq_number += 0x10;

		if (info->flags & IEEE80211_TX_CTL_AMPDU)
			is_agg = true;
		is_data_qos = true;
	}

	/* Copy MAC header from skb into command buffer */
	memcpy(tx_cmd->hdr, hdr, hdr_len);

	if (is_agg)
		txq_id = priv->tid_data[sta_id][tid].agg.txq_id;
	else if (info->flags & IEEE80211_TX_CTL_SEND_AFTER_DTIM) {
		/*
		 * Send this frame after DTIM -- there's a special queue
		 * reserved for this for contexts that support AP mode.
		 */
		txq_id = ctx->mcast_queue;

		/*
		 * The microcode will clear the more data
		 * bit in the last frame it transmits.
		 */
		hdr->frame_control |=
			cpu_to_le16(IEEE80211_FCTL_MOREDATA);
	} else if (info->flags & IEEE80211_TX_CTL_TX_OFFCHAN)
		txq_id = IWL_AUX_QUEUE;
	else
		txq_id = ctx->ac_to_queue[skb_get_queue_mapping(skb)];

	WARN_ON_ONCE(!is_agg && txq_id != info->hw_queue);
	WARN_ON_ONCE(is_agg &&
		     priv->queue_to_mac80211[txq_id] != info->hw_queue);

	IWL_DEBUG_TX(priv, "TX to [%d|%d] Q:%d - seq: 0x%x\n", sta_id, tid,
		     txq_id, seq_number);

	if (iwl_trans_tx(priv->trans, skb, dev_cmd, txq_id))
		goto drop_unlock_sta;

	if (is_data_qos && !ieee80211_has_morefrags(fc))
		priv->tid_data[sta_id][tid].seq_number = seq_number;

	spin_unlock(&priv->sta_lock);

	/*
	 * Avoid atomic ops if it isn't an associated client.
	 * Also, if this is a packet for aggregation, don't
	 * increase the counter because the ucode will stop
	 * aggregation queues when their respective station
	 * goes to sleep.
	 */
	if (sta_priv && sta_priv->client && !is_agg)
		atomic_inc(&sta_priv->pending_frames);

	if (info->flags & IEEE80211_TX_CTL_TX_OFFCHAN)
		iwl_scan_offchannel_skb(priv);

	return 0;

drop_unlock_sta:
	if (dev_cmd)
		iwl_trans_free_tx_cmd(priv->trans, dev_cmd);
	spin_unlock(&priv->sta_lock);
drop_unlock_priv:
	return -1;
}