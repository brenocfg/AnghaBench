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
struct ixgbe_adapter {size_t bd_number; } ;

/* Variables and functions */
 scalar_t__* FdirMode ; 
 scalar_t__ IXGBE_FDIR_FILTER_ON ; 
 size_t num_FdirMode ; 

bool ixgbe_adapter_fdir_capable(struct ixgbe_adapter *adapter)
{
	if (num_FdirMode <= adapter->bd_number)
		return true;

	if (FdirMode[adapter->bd_number] == IXGBE_FDIR_FILTER_ON)
		return true;

	return false;

}