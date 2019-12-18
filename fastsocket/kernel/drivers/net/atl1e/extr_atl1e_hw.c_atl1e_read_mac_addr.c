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
struct atl1e_hw {int /*<<< orphan*/  perm_mac_addr; int /*<<< orphan*/  mac_addr; } ;

/* Variables and functions */
 int AT_ERR_EEPROM ; 
 int atl1e_get_permanent_address (struct atl1e_hw*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int atl1e_read_mac_addr(struct atl1e_hw *hw)
{
	int err = 0;

	err = atl1e_get_permanent_address(hw);
	if (err)
		return AT_ERR_EEPROM;
	memcpy(hw->mac_addr, hw->perm_mac_addr, sizeof(hw->perm_mac_addr));
	return 0;
}