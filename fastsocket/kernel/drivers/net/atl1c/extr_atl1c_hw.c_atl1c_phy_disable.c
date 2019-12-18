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
struct atl1c_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atl1c_power_saving (struct atl1c_hw*,int /*<<< orphan*/ ) ; 

void atl1c_phy_disable(struct atl1c_hw *hw)
{
	atl1c_power_saving(hw, 0);
}