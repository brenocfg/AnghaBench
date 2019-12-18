#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pch_gbe_hw {TYPE_1__* func; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {int /*<<< orphan*/  (* read_mac_addr ) (struct pch_gbe_hw*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  stub1 (struct pch_gbe_hw*) ; 

inline s32 pch_gbe_hal_read_mac_addr(struct pch_gbe_hw *hw)
{
	if (!hw->func->read_mac_addr) {
		pr_err("ERROR: configuration\n");
		return -ENOSYS;
	}
	return hw->func->read_mac_addr(hw);
}