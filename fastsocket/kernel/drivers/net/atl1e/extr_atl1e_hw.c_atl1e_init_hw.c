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
struct atl1e_hw {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  AT_WRITE_REG (struct atl1e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT_WRITE_REG_ARRAY (struct atl1e_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RX_HASH_TABLE ; 
 int /*<<< orphan*/  atl1e_init_pcie (struct atl1e_hw*) ; 
 int atl1e_phy_init (struct atl1e_hw*) ; 

int atl1e_init_hw(struct atl1e_hw *hw)
{
	s32 ret_val = 0;

	atl1e_init_pcie(hw);

	/* Zero out the Multicast HASH table */
	/* clear the old settings from the multicast hash table */
	AT_WRITE_REG(hw, REG_RX_HASH_TABLE, 0);
	AT_WRITE_REG_ARRAY(hw, REG_RX_HASH_TABLE, 1, 0);

	ret_val = atl1e_phy_init(hw);

	return ret_val;
}