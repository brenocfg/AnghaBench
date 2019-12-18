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
struct mwl8k_priv {int cookie_dma; TYPE_2__* txq; TYPE_1__* rxq; } ;
struct TYPE_6__ {void* length; void* code; } ;
struct mwl8k_cmd_set_hw_spec {TYPE_3__ header; void* total_rxd; void* num_tx_desc_per_queue; void* flags; void** tx_queue_ptrs; void* num_tx_queues; void* rx_queue_ptr; void* ps_cookie; } ;
struct ieee80211_hw {struct mwl8k_priv* priv; } ;
struct TYPE_5__ {int txd_dma; } ;
struct TYPE_4__ {int rxd_dma; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MWL8K_CMD_SET_HW_SPEC ; 
 int MWL8K_RX_DESCS ; 
 int MWL8K_SET_HW_SPEC_FLAG_ENABLE_LIFE_TIME_EXPIRY ; 
 int MWL8K_SET_HW_SPEC_FLAG_GENERATE_CCMP_HDR ; 
 int MWL8K_SET_HW_SPEC_FLAG_HOSTFORM_BEACON ; 
 int MWL8K_SET_HW_SPEC_FLAG_HOSTFORM_PROBERESP ; 
 int MWL8K_SET_HW_SPEC_FLAG_HOST_DECR_MGMT ; 
 int MWL8K_TX_DESCS ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  kfree (struct mwl8k_cmd_set_hw_spec*) ; 
 struct mwl8k_cmd_set_hw_spec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mwl8k_post_cmd (struct ieee80211_hw*,TYPE_3__*) ; 
 int mwl8k_tx_queues (struct mwl8k_priv*) ; 

__attribute__((used)) static int mwl8k_cmd_set_hw_spec(struct ieee80211_hw *hw)
{
	struct mwl8k_priv *priv = hw->priv;
	struct mwl8k_cmd_set_hw_spec *cmd;
	int rc;
	int i;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		return -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_HW_SPEC);
	cmd->header.length = cpu_to_le16(sizeof(*cmd));

	cmd->ps_cookie = cpu_to_le32(priv->cookie_dma);
	cmd->rx_queue_ptr = cpu_to_le32(priv->rxq[0].rxd_dma);
	cmd->num_tx_queues = cpu_to_le32(mwl8k_tx_queues(priv));

	/*
	 * Mac80211 stack has Q0 as highest priority and Q3 as lowest in
	 * that order. Firmware has Q3 as highest priority and Q0 as lowest
	 * in that order. Map Q3 of mac80211 to Q0 of firmware so that the
	 * priority is interpreted the right way in firmware.
	 */
	for (i = 0; i < mwl8k_tx_queues(priv); i++) {
		int j = mwl8k_tx_queues(priv) - 1 - i;
		cmd->tx_queue_ptrs[i] = cpu_to_le32(priv->txq[j].txd_dma);
	}

	cmd->flags = cpu_to_le32(MWL8K_SET_HW_SPEC_FLAG_HOST_DECR_MGMT |
				 MWL8K_SET_HW_SPEC_FLAG_HOSTFORM_PROBERESP |
				 MWL8K_SET_HW_SPEC_FLAG_HOSTFORM_BEACON |
				 MWL8K_SET_HW_SPEC_FLAG_ENABLE_LIFE_TIME_EXPIRY |
				 MWL8K_SET_HW_SPEC_FLAG_GENERATE_CCMP_HDR);
	cmd->num_tx_desc_per_queue = cpu_to_le32(MWL8K_TX_DESCS);
	cmd->total_rxd = cpu_to_le32(MWL8K_RX_DESCS);

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kfree(cmd);

	return rc;
}