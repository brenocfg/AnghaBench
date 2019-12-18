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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct sk_buff {scalar_t__ len; scalar_t__ protocol; scalar_t__ data; } ;
struct iwl_tx_cmd {int tid_tspec; int sta_id; void* life_time; scalar_t__ next_frame_len; void* len; void* tx_flags; scalar_t__ driver_txop; void* pm_frame_timeout; } ;
struct iwl_mvm {scalar_t__ rts_threshold; } ;
struct ieee80211_tx_info {int flags; scalar_t__ band; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_PAE ; 
 scalar_t__ FCS_LEN ; 
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 int IEEE80211_TX_CTL_ASSIGN_SEQ ; 
 int IEEE80211_TX_CTL_NO_ACK ; 
 int IWL_TID_NON_QOS ; 
 scalar_t__ TX_CMD_FLG_ACK ; 
 scalar_t__ TX_CMD_FLG_BAR ; 
 scalar_t__ TX_CMD_FLG_BT_DIS ; 
 scalar_t__ TX_CMD_FLG_MORE_FRAG ; 
 scalar_t__ TX_CMD_FLG_PROT_REQUIRE ; 
 scalar_t__ TX_CMD_FLG_SEQ_CTL ; 
 scalar_t__ TX_CMD_FLG_TSF ; 
 scalar_t__ TX_CMD_LIFE_TIME_INFINITE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  ieee80211_get_DA (struct ieee80211_hdr*) ; 
 int* ieee80211_get_qos_ctl (struct ieee80211_hdr*) ; 
 scalar_t__ ieee80211_has_morefrags (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_assoc_req (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_back_req (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_mgmt (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_probe_resp (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_reassoc_req (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (void*) ; 

__attribute__((used)) static void iwl_mvm_set_tx_cmd(struct iwl_mvm *mvm, struct sk_buff *skb,
			       struct iwl_tx_cmd *tx_cmd,
			       struct ieee80211_tx_info *info, u8 sta_id)
{
	struct ieee80211_hdr *hdr = (void *)skb->data;
	__le16 fc = hdr->frame_control;
	u32 tx_flags = le32_to_cpu(tx_cmd->tx_flags);
	u32 len = skb->len + FCS_LEN;

	if (!(info->flags & IEEE80211_TX_CTL_NO_ACK))
		tx_flags |= TX_CMD_FLG_ACK;
	else
		tx_flags &= ~TX_CMD_FLG_ACK;

	if (ieee80211_is_probe_resp(fc))
		tx_flags |= TX_CMD_FLG_TSF;
	else if (ieee80211_is_back_req(fc))
		tx_flags |= TX_CMD_FLG_ACK | TX_CMD_FLG_BAR;

	/* High prio packet (wrt. BT coex) if it is EAPOL, MCAST or MGMT */
	if (info->band == IEEE80211_BAND_2GHZ        &&
	    (skb->protocol == cpu_to_be16(ETH_P_PAE)  ||
	     is_multicast_ether_addr(hdr->addr1)      ||
	     ieee80211_is_back_req(fc)                ||
	     ieee80211_is_mgmt(fc)))
		tx_flags |= TX_CMD_FLG_BT_DIS;

	if (ieee80211_has_morefrags(fc))
		tx_flags |= TX_CMD_FLG_MORE_FRAG;

	if (ieee80211_is_data_qos(fc)) {
		u8 *qc = ieee80211_get_qos_ctl(hdr);
		tx_cmd->tid_tspec = qc[0] & 0xf;
		tx_flags &= ~TX_CMD_FLG_SEQ_CTL;
	} else {
		tx_cmd->tid_tspec = IWL_TID_NON_QOS;
		if (info->flags & IEEE80211_TX_CTL_ASSIGN_SEQ)
			tx_flags |= TX_CMD_FLG_SEQ_CTL;
		else
			tx_flags &= ~TX_CMD_FLG_SEQ_CTL;
	}

	if (ieee80211_is_mgmt(fc)) {
		if (ieee80211_is_assoc_req(fc) || ieee80211_is_reassoc_req(fc))
			tx_cmd->pm_frame_timeout = cpu_to_le16(3);
		else
			tx_cmd->pm_frame_timeout = cpu_to_le16(2);

		/* The spec allows Action frames in A-MPDU, we don't support
		 * it
		 */
		WARN_ON_ONCE(info->flags & IEEE80211_TX_CTL_AMPDU);
	} else {
		tx_cmd->pm_frame_timeout = 0;
	}

	if (info->flags & IEEE80211_TX_CTL_AMPDU)
		tx_flags |= TX_CMD_FLG_PROT_REQUIRE;

	if (ieee80211_is_data(fc) && len > mvm->rts_threshold &&
	    !is_multicast_ether_addr(ieee80211_get_DA(hdr)))
		tx_flags |= TX_CMD_FLG_PROT_REQUIRE;

	tx_cmd->driver_txop = 0;
	tx_cmd->tx_flags = cpu_to_le32(tx_flags);
	/* Total # bytes to be transmitted */
	tx_cmd->len = cpu_to_le16((u16)skb->len);
	tx_cmd->next_frame_len = 0;
	tx_cmd->life_time = cpu_to_le32(TX_CMD_LIFE_TIME_INFINITE);
	tx_cmd->sta_id = sta_id;
}