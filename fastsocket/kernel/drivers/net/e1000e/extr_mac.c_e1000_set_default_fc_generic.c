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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  requested_mode; } ;
struct e1000_hw {TYPE_1__ fc; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  NVM_INIT_CONTROL2_REG ; 
 int NVM_WORD0F_ASM_DIR ; 
 int NVM_WORD0F_PAUSE_MASK ; 
 int /*<<< orphan*/  e1000_fc_full ; 
 int /*<<< orphan*/  e1000_fc_none ; 
 int /*<<< orphan*/  e1000_fc_tx_pause ; 
 scalar_t__ e1000_read_nvm (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 

__attribute__((used)) static s32 e1000_set_default_fc_generic(struct e1000_hw *hw)
{
	s32 ret_val;
	u16 nvm_data;

	/* Read and store word 0x0F of the EEPROM. This word contains bits
	 * that determine the hardware's default PAUSE (flow control) mode,
	 * a bit that determines whether the HW defaults to enabling or
	 * disabling auto-negotiation, and the direction of the
	 * SW defined pins. If there is no SW over-ride of the flow
	 * control setting, then the variable hw->fc will
	 * be initialized based on a value in the EEPROM.
	 */
	ret_val = e1000_read_nvm(hw, NVM_INIT_CONTROL2_REG, 1, &nvm_data);

	if (ret_val) {
		e_dbg("NVM Read Error\n");
		return ret_val;
	}

	if (!(nvm_data & NVM_WORD0F_PAUSE_MASK))
		hw->fc.requested_mode = e1000_fc_none;
	else if ((nvm_data & NVM_WORD0F_PAUSE_MASK) == NVM_WORD0F_ASM_DIR)
		hw->fc.requested_mode = e1000_fc_tx_pause;
	else
		hw->fc.requested_mode = e1000_fc_full;

	return 0;
}