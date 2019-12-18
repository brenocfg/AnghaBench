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
typedef  scalar_t__ u32 ;
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_VFTA ; 
 scalar_t__ E1000_VLAN_FILTER_TBL_SIZE ; 
 int /*<<< orphan*/  array_wr32 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrfl () ; 

void igb_clear_vfta(struct e1000_hw *hw)
{
	u32 offset;

	for (offset = 0; offset < E1000_VLAN_FILTER_TBL_SIZE; offset++) {
		array_wr32(E1000_VFTA, offset, 0);
		wrfl();
	}
}