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
struct net_device {int dummy; } ;
struct atl1c_adapter {int /*<<< orphan*/  common_task; int /*<<< orphan*/  work_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATL1C_WORK_EVENT_RESET ; 
 struct atl1c_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atl1c_tx_timeout(struct net_device *netdev)
{
	struct atl1c_adapter *adapter = netdev_priv(netdev);

	/* Do the reset outside of interrupt context */
	set_bit(ATL1C_WORK_EVENT_RESET, &adapter->work_event);
	schedule_work(&adapter->common_task);
}