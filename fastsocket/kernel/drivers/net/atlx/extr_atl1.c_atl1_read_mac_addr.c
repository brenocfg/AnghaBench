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
typedef  size_t u16 ;
struct atl1_hw {int /*<<< orphan*/ * perm_mac_addr; int /*<<< orphan*/ * mac_addr; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 size_t ETH_ALEN ; 
 scalar_t__ atl1_get_permanent_address (struct atl1_hw*) ; 
 int /*<<< orphan*/  random_ether_addr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32 atl1_read_mac_addr(struct atl1_hw *hw)
{
	u16 i;

	if (atl1_get_permanent_address(hw))
		random_ether_addr(hw->perm_mac_addr);

	for (i = 0; i < ETH_ALEN; i++)
		hw->mac_addr[i] = hw->perm_mac_addr[i];
	return 0;
}