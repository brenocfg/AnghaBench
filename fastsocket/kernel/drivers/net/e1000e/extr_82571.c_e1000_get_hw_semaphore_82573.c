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
struct e1000_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_ERR_PHY ; 
 int E1000_EXTCNF_CTRL_MDIO_SW_OWNERSHIP ; 
 int /*<<< orphan*/  EXTCNF_CTRL ; 
 scalar_t__ MDIO_OWNERSHIP_TIMEOUT ; 
 int /*<<< orphan*/  e1000_put_hw_semaphore_82573 (struct e1000_hw*) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static s32 e1000_get_hw_semaphore_82573(struct e1000_hw *hw)
{
	u32 extcnf_ctrl;
	s32 i = 0;

	extcnf_ctrl = er32(EXTCNF_CTRL);
	do {
		extcnf_ctrl |= E1000_EXTCNF_CTRL_MDIO_SW_OWNERSHIP;
		ew32(EXTCNF_CTRL, extcnf_ctrl);
		extcnf_ctrl = er32(EXTCNF_CTRL);

		if (extcnf_ctrl & E1000_EXTCNF_CTRL_MDIO_SW_OWNERSHIP)
			break;

		usleep_range(2000, 4000);
		i++;
	} while (i < MDIO_OWNERSHIP_TIMEOUT);

	if (i == MDIO_OWNERSHIP_TIMEOUT) {
		/* Release semaphores */
		e1000_put_hw_semaphore_82573(hw);
		e_dbg("Driver can't access the PHY\n");
		return -E1000_ERR_PHY;
	}

	return 0;
}