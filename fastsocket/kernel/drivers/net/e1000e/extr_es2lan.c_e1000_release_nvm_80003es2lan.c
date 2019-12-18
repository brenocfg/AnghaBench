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

/* Variables and functions */
 int /*<<< orphan*/  E1000_SWFW_EEP_SM ; 
 int /*<<< orphan*/  e1000_release_swfw_sync_80003es2lan (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000e_release_nvm (struct e1000_hw*) ; 

__attribute__((used)) static void e1000_release_nvm_80003es2lan(struct e1000_hw *hw)
{
	e1000e_release_nvm(hw);
	e1000_release_swfw_sync_80003es2lan(hw, E1000_SWFW_EEP_SM);
}