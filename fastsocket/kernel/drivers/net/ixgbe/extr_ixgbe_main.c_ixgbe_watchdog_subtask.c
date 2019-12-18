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
struct ixgbe_adapter {scalar_t__ link_up; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __IXGBE_DOWN ; 
 int /*<<< orphan*/  __IXGBE_RESETTING ; 
 int /*<<< orphan*/  ixgbe_spoof_check (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_update_stats (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_watchdog_flush_tx (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_watchdog_link_is_down (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_watchdog_link_is_up (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_watchdog_update_link (struct ixgbe_adapter*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixgbe_watchdog_subtask(struct ixgbe_adapter *adapter)
{
	/* if interface is down do nothing */
	if (test_bit(__IXGBE_DOWN, &adapter->state) ||
	    test_bit(__IXGBE_RESETTING, &adapter->state))
		return;

	ixgbe_watchdog_update_link(adapter);

	if (adapter->link_up)
		ixgbe_watchdog_link_is_up(adapter);
	else
		ixgbe_watchdog_link_is_down(adapter);

	ixgbe_spoof_check(adapter);
	ixgbe_update_stats(adapter);

	ixgbe_watchdog_flush_tx(adapter);
}