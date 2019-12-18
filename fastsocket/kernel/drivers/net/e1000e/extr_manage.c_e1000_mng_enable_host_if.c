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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  arc_subsystem_valid; } ;
struct e1000_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ERR_HOST_INTERFACE_COMMAND ; 
 int E1000_HICR_C ; 
 int E1000_HICR_EN ; 
 scalar_t__ E1000_MNG_DHCP_COMMAND_TIMEOUT ; 
 int /*<<< orphan*/  HICR ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static s32 e1000_mng_enable_host_if(struct e1000_hw *hw)
{
	u32 hicr;
	u8 i;

	if (!hw->mac.arc_subsystem_valid) {
		e_dbg("ARC subsystem not valid.\n");
		return -E1000_ERR_HOST_INTERFACE_COMMAND;
	}

	/* Check that the host interface is enabled. */
	hicr = er32(HICR);
	if (!(hicr & E1000_HICR_EN)) {
		e_dbg("E1000_HOST_EN bit disabled.\n");
		return -E1000_ERR_HOST_INTERFACE_COMMAND;
	}
	/* check the previous command is completed */
	for (i = 0; i < E1000_MNG_DHCP_COMMAND_TIMEOUT; i++) {
		hicr = er32(HICR);
		if (!(hicr & E1000_HICR_C))
			break;
		mdelay(1);
	}

	if (i == E1000_MNG_DHCP_COMMAND_TIMEOUT) {
		e_dbg("Previous command timeout failed .\n");
		return -E1000_ERR_HOST_INTERFACE_COMMAND;
	}

	return 0;
}