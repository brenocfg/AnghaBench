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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SW_FW_SYNC ; 
 scalar_t__ e1000e_get_hw_semaphore (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000e_put_hw_semaphore (struct e1000_hw*) ; 
 int /*<<< orphan*/  er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000_release_swfw_sync_80003es2lan(struct e1000_hw *hw, u16 mask)
{
	u32 swfw_sync;

	while (e1000e_get_hw_semaphore(hw) != 0)
		; /* Empty */

	swfw_sync = er32(SW_FW_SYNC);
	swfw_sync &= ~mask;
	ew32(SW_FW_SYNC, swfw_sync);

	e1000e_put_hw_semaphore(hw);
}