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
struct atl1e_hw {int dummy; } ;

/* Variables and functions */
 int AT_READ_REG (struct atl1e_hw*,int) ; 
 int /*<<< orphan*/  AT_WRITE_REG (struct atl1e_hw*,int,int) ; 

__attribute__((used)) static void atl1e_init_pcie(struct atl1e_hw *hw)
{
	u32 value;
	/* comment 2lines below to save more power when sususpend
	   value = LTSSM_TEST_MODE_DEF;
	   AT_WRITE_REG(hw, REG_LTSSM_TEST_MODE, value);
	 */

	/* pcie flow control mode change */
	value = AT_READ_REG(hw, 0x1008);
	value |= 0x8000;
	AT_WRITE_REG(hw, 0x1008, value);
}