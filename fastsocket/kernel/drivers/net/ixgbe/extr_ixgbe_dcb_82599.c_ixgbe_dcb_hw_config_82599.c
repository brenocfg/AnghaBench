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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbe_dcb_config_pfc_82599 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_dcb_config_rx_arbiter_82599 (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_dcb_config_tc_stats_82599 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_dcb_config_tx_data_arbiter_82599 (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_dcb_config_tx_desc_arbiter_82599 (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

s32 ixgbe_dcb_hw_config_82599(struct ixgbe_hw *hw, u8 pfc_en, u16 *refill,
			      u16 *max, u8 *bwg_id, u8 *prio_type, u8 *prio_tc)
{
	ixgbe_dcb_config_rx_arbiter_82599(hw, refill, max, bwg_id,
					  prio_type, prio_tc);
	ixgbe_dcb_config_tx_desc_arbiter_82599(hw, refill, max,
					       bwg_id, prio_type);
	ixgbe_dcb_config_tx_data_arbiter_82599(hw, refill, max,
					       bwg_id, prio_type, prio_tc);
	ixgbe_dcb_config_pfc_82599(hw, pfc_en, prio_tc);
	ixgbe_dcb_config_tc_stats_82599(hw);

	return 0;
}