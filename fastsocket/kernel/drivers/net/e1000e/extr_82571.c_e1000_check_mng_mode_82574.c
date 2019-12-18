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
typedef  int u16 ;
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 int E1000_NVM_INIT_CTRL2_MNGM ; 
 int /*<<< orphan*/  NVM_INIT_CONTROL2_REG ; 
 int /*<<< orphan*/  e1000_read_nvm (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static bool e1000_check_mng_mode_82574(struct e1000_hw *hw)
{
	u16 data;

	e1000_read_nvm(hw, NVM_INIT_CONTROL2_REG, 1, &data);
	return (data & E1000_NVM_INIT_CTRL2_MNGM) != 0;
}