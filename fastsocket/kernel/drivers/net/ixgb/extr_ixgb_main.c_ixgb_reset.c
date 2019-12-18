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
typedef  int u32 ;
struct ixgb_hw {int max_frame_size; } ;
struct ixgb_adapter {struct ixgb_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL0 ; 
 int /*<<< orphan*/  DPRINTK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ENET_FCS_LENGTH ; 
 int /*<<< orphan*/  ERR ; 
 int IXGB_CTRL0_JFE ; 
 int IXGB_MAX_ENET_FRAME_SIZE_WITHOUT_FCS ; 
 int IXGB_MFS_SHIFT ; 
 int IXGB_READ_REG (struct ixgb_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGB_WRITE_REG (struct ixgb_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MFS ; 
 int /*<<< orphan*/  PROBE ; 
 int /*<<< orphan*/  ixgb_adapter_stop (struct ixgb_hw*) ; 
 int /*<<< orphan*/  ixgb_init_hw (struct ixgb_hw*) ; 

void
ixgb_reset(struct ixgb_adapter *adapter)
{
	struct ixgb_hw *hw = &adapter->hw;

	ixgb_adapter_stop(hw);
	if (!ixgb_init_hw(hw))
		DPRINTK(PROBE, ERR, "ixgb_init_hw failed.\n");

	/* restore frame size information */
	IXGB_WRITE_REG(hw, MFS, hw->max_frame_size << IXGB_MFS_SHIFT);
	if (hw->max_frame_size >
	    IXGB_MAX_ENET_FRAME_SIZE_WITHOUT_FCS + ENET_FCS_LENGTH) {
		u32 ctrl0 = IXGB_READ_REG(hw, CTRL0);
		if (!(ctrl0 & IXGB_CTRL0_JFE)) {
			ctrl0 |= IXGB_CTRL0_JFE;
			IXGB_WRITE_REG(hw, CTRL0, ctrl0);
		}
	}
}