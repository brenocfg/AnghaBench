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
struct e1000_adapter {int /*<<< orphan*/  fifo_stall_task; int /*<<< orphan*/  phy_info_task; int /*<<< orphan*/  watchdog_task; int /*<<< orphan*/  reset_task; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  __E1000_DOWN ; 
 int /*<<< orphan*/  __E1000_RESETTING ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void e1000_down_and_stop(struct e1000_adapter *adapter)
{
	set_bit(__E1000_DOWN, &adapter->flags);

	/* Only kill reset task if adapter is not resetting */
	if (!test_bit(__E1000_RESETTING, &adapter->flags))
		cancel_work_sync(&adapter->reset_task);

	cancel_delayed_work_sync(&adapter->watchdog_task);
	cancel_delayed_work_sync(&adapter->phy_info_task);
	cancel_delayed_work_sync(&adapter->fifo_stall_task);
}