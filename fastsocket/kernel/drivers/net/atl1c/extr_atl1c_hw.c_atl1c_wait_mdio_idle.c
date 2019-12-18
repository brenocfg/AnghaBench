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
struct atl1c_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_READ_REG (struct atl1c_hw*,int /*<<< orphan*/ ,int*) ; 
 int MDIO_CTRL_BUSY ; 
 int MDIO_CTRL_START ; 
 int MDIO_MAX_AC_TO ; 
 int /*<<< orphan*/  REG_MDIO_CTRL ; 
 int /*<<< orphan*/  udelay (int) ; 

bool atl1c_wait_mdio_idle(struct atl1c_hw *hw)
{
	u32 val;
	int i;

	for (i = 0; i < MDIO_MAX_AC_TO; i++) {
		AT_READ_REG(hw, REG_MDIO_CTRL, &val);
		if (!(val & (MDIO_CTRL_BUSY | MDIO_CTRL_START)))
			break;
		udelay(10);
	}

	return i != MDIO_MAX_AC_TO;
}