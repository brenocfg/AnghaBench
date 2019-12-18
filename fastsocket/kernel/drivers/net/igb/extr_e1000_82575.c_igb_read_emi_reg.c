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
typedef  int /*<<< orphan*/  u16 ;
struct e1000_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  __igb_access_emi_reg (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

s32 igb_read_emi_reg(struct e1000_hw *hw, u16 addr, u16 *data)
{
	return __igb_access_emi_reg(hw, addr, data, true);
}