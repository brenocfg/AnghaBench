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
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FH_MEM_RCSR_CHNL0_CONFIG_REG ; 
 int /*<<< orphan*/  FH_MEM_RSSR_RX_STATUS_REG ; 
 int /*<<< orphan*/  FH_RSSR_CHNL0_RX_STATUS_CHNL_IDLE ; 
 int iwl_poll_direct_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_write_direct32 (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int iwl_pcie_rx_stop(struct iwl_trans *trans)
{
	iwl_write_direct32(trans, FH_MEM_RCSR_CHNL0_CONFIG_REG, 0);
	return iwl_poll_direct_bit(trans, FH_MEM_RSSR_RX_STATUS_REG,
				   FH_RSSR_CHNL0_RX_STATUS_CHNL_IDLE, 1000);
}