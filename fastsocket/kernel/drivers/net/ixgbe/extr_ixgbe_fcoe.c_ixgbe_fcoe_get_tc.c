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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  up; } ;
struct ixgbe_adapter {TYPE_1__ fcoe; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_get_prio_tc_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u8 ixgbe_fcoe_get_tc(struct ixgbe_adapter *adapter)
{
#ifdef CONFIG_IXGBE_DCB
	return netdev_get_prio_tc_map(adapter->netdev, adapter->fcoe.up);
#else
	return 0;
#endif
}