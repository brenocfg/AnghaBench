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
typedef  int u32 ;
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_priv {unsigned long status; TYPE_1__* hw; int /*<<< orphan*/  trans; } ;
struct iwl_device_cmd {int dummy; } ;
struct iwl_card_state_notif {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_UCODE_DRV_GP1_BIT_CMD_BLOCKED ; 
 int /*<<< orphan*/  CSR_UCODE_DRV_GP1_CLR ; 
 int /*<<< orphan*/  CSR_UCODE_DRV_GP1_SET ; 
 int CT_CARD_DISABLED ; 
 int /*<<< orphan*/  HBUS_TARG_MBX_C ; 
 int /*<<< orphan*/  HBUS_TARG_MBX_C_REG_BIT_CMD_BLOCKED ; 
 int HW_CARD_DISABLED ; 
 int /*<<< orphan*/  IWL_DEBUG_RF_KILL (struct iwl_priv*,char*,char*,char*,char*) ; 
 int RXON_CARD_DISABLED ; 
 int /*<<< orphan*/  STATUS_RF_KILL_HW ; 
 int SW_CARD_DISABLED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  iwl_scan_cancel (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwl_tt_enter_ct_kill (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwl_tt_exit_ct_kill (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwl_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write_direct32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  wiphy_rfkill_set_hw_state (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int iwlagn_rx_card_state_notif(struct iwl_priv *priv,
				    struct iwl_rx_cmd_buffer *rxb,
				    struct iwl_device_cmd *cmd)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_card_state_notif *card_state_notif = (void *)pkt->data;
	u32 flags = le32_to_cpu(card_state_notif->flags);
	unsigned long status = priv->status;

	IWL_DEBUG_RF_KILL(priv, "Card state received: HW:%s SW:%s CT:%s\n",
			  (flags & HW_CARD_DISABLED) ? "Kill" : "On",
			  (flags & SW_CARD_DISABLED) ? "Kill" : "On",
			  (flags & CT_CARD_DISABLED) ?
			  "Reached" : "Not reached");

	if (flags & (SW_CARD_DISABLED | HW_CARD_DISABLED |
		     CT_CARD_DISABLED)) {

		iwl_write32(priv->trans, CSR_UCODE_DRV_GP1_SET,
			    CSR_UCODE_DRV_GP1_BIT_CMD_BLOCKED);

		iwl_write_direct32(priv->trans, HBUS_TARG_MBX_C,
					HBUS_TARG_MBX_C_REG_BIT_CMD_BLOCKED);

		if (!(flags & RXON_CARD_DISABLED)) {
			iwl_write32(priv->trans, CSR_UCODE_DRV_GP1_CLR,
				    CSR_UCODE_DRV_GP1_BIT_CMD_BLOCKED);
			iwl_write_direct32(priv->trans, HBUS_TARG_MBX_C,
					HBUS_TARG_MBX_C_REG_BIT_CMD_BLOCKED);
		}
		if (flags & CT_CARD_DISABLED)
			iwl_tt_enter_ct_kill(priv);
	}
	if (!(flags & CT_CARD_DISABLED))
		iwl_tt_exit_ct_kill(priv);

	if (flags & HW_CARD_DISABLED)
		set_bit(STATUS_RF_KILL_HW, &priv->status);
	else
		clear_bit(STATUS_RF_KILL_HW, &priv->status);


	if (!(flags & RXON_CARD_DISABLED))
		iwl_scan_cancel(priv);

	if ((test_bit(STATUS_RF_KILL_HW, &status) !=
	     test_bit(STATUS_RF_KILL_HW, &priv->status)))
		wiphy_rfkill_set_hw_state(priv->hw->wiphy,
			test_bit(STATUS_RF_KILL_HW, &priv->status));
	return 0;
}