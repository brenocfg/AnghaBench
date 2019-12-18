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
typedef  int u16 ;
struct iwl_mvm {int /*<<< orphan*/  fw; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int PHY_RX_CHAIN_DRIVER_FORCE_POS ; 
 int PHY_RX_CHAIN_FORCE_MIMO_SEL_POS ; 
 int PHY_RX_CHAIN_FORCE_SEL_POS ; 
 int PHY_RX_CHAIN_VALID_POS ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int iwl_fw_valid_rx_ant (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline __le16 iwl_mvm_scan_rx_chain(struct iwl_mvm *mvm)
{
	u16 rx_chain;
	u8 rx_ant = iwl_fw_valid_rx_ant(mvm->fw);

	rx_chain = rx_ant << PHY_RX_CHAIN_VALID_POS;
	rx_chain |= rx_ant << PHY_RX_CHAIN_FORCE_MIMO_SEL_POS;
	rx_chain |= rx_ant << PHY_RX_CHAIN_FORCE_SEL_POS;
	rx_chain |= 0x1 << PHY_RX_CHAIN_DRIVER_FORCE_POS;
	return cpu_to_le16(rx_chain);
}