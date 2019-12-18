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
struct e1000_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_SWFW_EEP_SM ; 
 int /*<<< orphan*/  igb_acquire_swfw_sync_i210 (struct e1000_hw*,int /*<<< orphan*/ ) ; 

s32 igb_acquire_nvm_i210(struct e1000_hw *hw)
{
	return igb_acquire_swfw_sync_i210(hw, E1000_SWFW_EEP_SM);
}