#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u16 ;
struct sk_buff {scalar_t__ data; } ;
struct iwl_tx_cmd {int /*<<< orphan*/  hdr; } ;
struct iwl_mvm_sta {size_t sta_id; int /*<<< orphan*/  lock; TYPE_1__* tid_data; } ;
struct iwl_mvm {int /*<<< orphan*/  trans; int /*<<< orphan*/ * pending_frames; } ;
struct iwl_device_cmd {scalar_t__ payload; } ;
struct ieee80211_tx_info {size_t hw_queue; int flags; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_hdr {int /*<<< orphan*/  seq_ctrl; int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int seq_number; scalar_t__ state; size_t txq_id; } ;

/* Variables and functions */
 size_t IEEE80211_QOS_CTL_TID_MASK ; 
 int IEEE80211_SCTL_FRAG ; 
 int IEEE80211_SCTL_SEQ ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 int IEEE80211_TX_CTL_SEND_AFTER_DTIM ; 
 scalar_t__ IWL_AGG_ON ; 
 int /*<<< orphan*/  IWL_DEBUG_TX (struct iwl_mvm*,char*,size_t,size_t,size_t,int) ; 
 size_t IWL_MAX_TID_COUNT ; 
 size_t IWL_MVM_FIRST_AGG_QUEUE ; 
 size_t IWL_MVM_STATION_COUNT ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 size_t* ieee80211_get_qos_ctl (struct ieee80211_hdr*) ; 
 int /*<<< orphan*/  ieee80211_has_morefrags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_qos_nullfunc (int /*<<< orphan*/ ) ; 
 struct iwl_device_cmd* iwl_mvm_set_tx_params (struct iwl_mvm*,struct sk_buff*,struct ieee80211_sta*,size_t) ; 
 int /*<<< orphan*/  iwl_trans_free_tx_cmd (int /*<<< orphan*/ ,struct iwl_device_cmd*) ; 
 scalar_t__ iwl_trans_tx (int /*<<< orphan*/ ,struct sk_buff*,struct iwl_device_cmd*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct ieee80211_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int iwl_mvm_tx_skb(struct iwl_mvm *mvm, struct sk_buff *skb,
		   struct ieee80211_sta *sta)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct iwl_mvm_sta *mvmsta;
	struct iwl_device_cmd *dev_cmd;
	struct iwl_tx_cmd *tx_cmd;
	__le16 fc;
	u16 seq_number = 0;
	u8 tid = IWL_MAX_TID_COUNT;
	u8 txq_id = info->hw_queue;
	bool is_data_qos = false, is_ampdu = false;

	mvmsta = (void *)sta->drv_priv;
	fc = hdr->frame_control;

	if (WARN_ON_ONCE(!mvmsta))
		return -1;

	if (WARN_ON_ONCE(mvmsta->sta_id == IWL_MVM_STATION_COUNT))
		return -1;

	dev_cmd = iwl_mvm_set_tx_params(mvm, skb, sta, mvmsta->sta_id);
	if (!dev_cmd)
		goto drop;

	tx_cmd = (struct iwl_tx_cmd *)dev_cmd->payload;
	/* From now on, we cannot access info->control */

	spin_lock(&mvmsta->lock);

	if (ieee80211_is_data_qos(fc) && !ieee80211_is_qos_nullfunc(fc)) {
		u8 *qc = NULL;
		qc = ieee80211_get_qos_ctl(hdr);
		tid = qc[0] & IEEE80211_QOS_CTL_TID_MASK;
		if (WARN_ON_ONCE(tid >= IWL_MAX_TID_COUNT))
			goto drop_unlock_sta;

		seq_number = mvmsta->tid_data[tid].seq_number;
		seq_number &= IEEE80211_SCTL_SEQ;
		hdr->seq_ctrl &= cpu_to_le16(IEEE80211_SCTL_FRAG);
		hdr->seq_ctrl |= cpu_to_le16(seq_number);
		seq_number += 0x10;
		is_data_qos = true;
		is_ampdu = info->flags & IEEE80211_TX_CTL_AMPDU;
	}

	/* Copy MAC header from skb into command buffer */
	memcpy(tx_cmd->hdr, hdr, ieee80211_hdrlen(fc));

	WARN_ON_ONCE(info->flags & IEEE80211_TX_CTL_SEND_AFTER_DTIM);

	if (is_ampdu) {
		if (WARN_ON_ONCE(mvmsta->tid_data[tid].state != IWL_AGG_ON))
			goto drop_unlock_sta;
		txq_id = mvmsta->tid_data[tid].txq_id;
	}

	IWL_DEBUG_TX(mvm, "TX to [%d|%d] Q:%d - seq: 0x%x\n", mvmsta->sta_id,
		     tid, txq_id, seq_number);

	/* NOTE: aggregation will need changes here (for txq id) */
	if (iwl_trans_tx(mvm->trans, skb, dev_cmd, txq_id))
		goto drop_unlock_sta;

	if (is_data_qos && !ieee80211_has_morefrags(fc))
		mvmsta->tid_data[tid].seq_number = seq_number;

	spin_unlock(&mvmsta->lock);

	if (txq_id < IWL_MVM_FIRST_AGG_QUEUE)
		atomic_inc(&mvm->pending_frames[mvmsta->sta_id]);

	return 0;

drop_unlock_sta:
	iwl_trans_free_tx_cmd(mvm->trans, dev_cmd);
	spin_unlock(&mvmsta->lock);
drop:
	return -1;
}