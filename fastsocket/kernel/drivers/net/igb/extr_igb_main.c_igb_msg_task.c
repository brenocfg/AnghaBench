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
typedef  scalar_t__ u32 ;
struct e1000_hw {int dummy; } ;
struct igb_adapter {scalar_t__ vfs_allocated_count; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  igb_check_for_ack (struct e1000_hw*,scalar_t__) ; 
 int /*<<< orphan*/  igb_check_for_msg (struct e1000_hw*,scalar_t__) ; 
 int /*<<< orphan*/  igb_check_for_rst (struct e1000_hw*,scalar_t__) ; 
 int /*<<< orphan*/  igb_rcv_ack_from_vf (struct igb_adapter*,scalar_t__) ; 
 int /*<<< orphan*/  igb_rcv_msg_from_vf (struct igb_adapter*,scalar_t__) ; 
 int /*<<< orphan*/  igb_vf_reset_event (struct igb_adapter*,scalar_t__) ; 

__attribute__((used)) static void igb_msg_task(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 vf;

	for (vf = 0; vf < adapter->vfs_allocated_count; vf++) {
		/* process any reset requests */
		if (!igb_check_for_rst(hw, vf))
			igb_vf_reset_event(adapter, vf);

		/* process any messages pending */
		if (!igb_check_for_msg(hw, vf))
			igb_rcv_msg_from_vf(adapter, vf);

		/* process any acks */
		if (!igb_check_for_ack(hw, vf))
			igb_rcv_ack_from_vf(adapter, vf);
	}
}