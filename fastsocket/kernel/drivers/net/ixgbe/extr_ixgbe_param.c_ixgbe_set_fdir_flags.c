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
typedef  int u32 ;
struct ixgbe_adapter {int flags; } ;

/* Variables and functions */
 int IXGBE_FLAG_FDIR_HASH_CAPABLE ; 
 int IXGBE_FLAG_FDIR_PERFECT_CAPABLE ; 
 int /*<<< orphan*/  e_dev_info (char*) ; 
 int /*<<< orphan*/  ixgbe_adapter_fdir_capable (struct ixgbe_adapter*) ; 

void ixgbe_set_fdir_flags(struct ixgbe_adapter *adapter, u32 flags)
{
	u32 *aflags = &adapter->flags;

	/* set flags */
	*aflags |= flags;

	/* remove Fdir flags if module option disabled Fdir */
	if (!ixgbe_adapter_fdir_capable(adapter)) {
		/*
		 * Do not set any flags that will enable the
		 * flow director.
		 */
		*aflags &= ~(IXGBE_FLAG_FDIR_HASH_CAPABLE |
			     IXGBE_FLAG_FDIR_PERFECT_CAPABLE);
		e_dev_info("Flow Director disabled\n");
	}
}