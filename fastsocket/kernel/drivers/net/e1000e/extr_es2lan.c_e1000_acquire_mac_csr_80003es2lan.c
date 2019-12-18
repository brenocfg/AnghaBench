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
 int /*<<< orphan*/  E1000_SWFW_CSR_SM ; 
 int /*<<< orphan*/  e1000_acquire_swfw_sync_80003es2lan (struct e1000_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 e1000_acquire_mac_csr_80003es2lan(struct e1000_hw *hw)
{
	u16 mask;

	mask = E1000_SWFW_CSR_SM;

	return e1000_acquire_swfw_sync_80003es2lan(hw, mask);
}