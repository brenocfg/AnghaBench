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
struct net_device {int dummy; } ;
struct be_adapter {TYPE_1__* pdev; int /*<<< orphan*/  num_tx_qs; int /*<<< orphan*/  num_rx_qs; struct net_device* netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int be_evt_queues_create (struct be_adapter*) ; 
 int be_mcc_queues_create (struct be_adapter*) ; 
 int be_rx_cqs_create (struct be_adapter*) ; 
 int be_tx_qs_create (struct be_adapter*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int netif_set_real_num_rx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_set_real_num_tx_queues (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int be_setup_queues(struct be_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	int status;

	status = be_evt_queues_create(adapter);
	if (status)
		goto err;

	status = be_tx_qs_create(adapter);
	if (status)
		goto err;

	status = be_rx_cqs_create(adapter);
	if (status)
		goto err;

	status = be_mcc_queues_create(adapter);
	if (status)
		goto err;

	status = netif_set_real_num_rx_queues(netdev, adapter->num_rx_qs);
	if (status)
		goto err;

	netif_set_real_num_tx_queues(netdev, adapter->num_tx_qs);

	return 0;
err:
	dev_err(&adapter->pdev->dev, "queue_setup failed\n");
	return status;
}