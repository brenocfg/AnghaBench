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
struct ixgbe_hw {int dummy; } ;
struct ixgbevf_adapter {int /*<<< orphan*/  mbx_lock; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int ixgbe_mbox_api_10 ; 
 int ixgbe_mbox_api_11 ; 
 int ixgbe_mbox_api_unknown ; 
 int ixgbevf_negotiate_api_version (struct ixgbe_hw*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixgbevf_negotiate_api(struct ixgbevf_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	int api[] = { ixgbe_mbox_api_11,
		      ixgbe_mbox_api_10,
		      ixgbe_mbox_api_unknown };
	int err = 0, idx = 0;

	spin_lock_bh(&adapter->mbx_lock);

	while (api[idx] != ixgbe_mbox_api_unknown) {
		err = ixgbevf_negotiate_api_version(hw, api[idx]);
		if (!err)
			break;
		idx++;
	}

	spin_unlock_bh(&adapter->mbx_lock);
}