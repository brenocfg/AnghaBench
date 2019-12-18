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
struct be_adapter {int /*<<< orphan*/  num_msix_roce_vec; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  be_cancel_worker (struct be_adapter*) ; 
 int /*<<< orphan*/  be_clear_queues (struct be_adapter*) ; 
 int /*<<< orphan*/  be_close (struct net_device*) ; 
 int /*<<< orphan*/  be_msix_disable (struct be_adapter*) ; 
 int be_msix_enable (struct be_adapter*) ; 
 int be_open (struct net_device*) ; 
 int /*<<< orphan*/  be_schedule_worker (struct be_adapter*) ; 
 int be_setup_queues (struct be_adapter*) ; 
 int /*<<< orphan*/  msix_enabled (struct be_adapter*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

int be_update_queues(struct be_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	int status;

	if (netif_running(netdev))
		be_close(netdev);

	be_cancel_worker(adapter);

	/* If any vectors have been shared with RoCE we cannot re-program
	 * the MSIx table.
	 */
	if (!adapter->num_msix_roce_vec)
		be_msix_disable(adapter);

	be_clear_queues(adapter);

	if (!msix_enabled(adapter)) {
		status = be_msix_enable(adapter);
		if (status)
			return status;
	}

	status = be_setup_queues(adapter);
	if (status)
		return status;

	be_schedule_worker(adapter);

	if (netif_running(netdev))
		status = be_open(netdev);

	return status;
}