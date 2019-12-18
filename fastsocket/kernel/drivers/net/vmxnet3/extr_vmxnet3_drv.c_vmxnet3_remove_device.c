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
struct vmxnet3_adapter {int num_tx_queues; int /*<<< orphan*/  shared_pa; int /*<<< orphan*/  shared; int /*<<< orphan*/  pdev; int /*<<< orphan*/  queue_desc_pa; int /*<<< orphan*/  tqd_start; int /*<<< orphan*/  pm_conf; int /*<<< orphan*/  rss_conf; int /*<<< orphan*/  work; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct Vmxnet3_TxQueueDesc {int dummy; } ;
struct Vmxnet3_RxQueueDesc {int dummy; } ;
struct Vmxnet3_DriverShared {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMXNET3_DEVICE_MAX_RX_QUEUES ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ enable_mq ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 struct vmxnet3_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ num_online_cpus () ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int rounddown_pow_of_two (int) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  vmxnet3_free_intr_resources (struct vmxnet3_adapter*) ; 
 int /*<<< orphan*/  vmxnet3_free_pci_resources (struct vmxnet3_adapter*) ; 

__attribute__((used)) static void
vmxnet3_remove_device(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct vmxnet3_adapter *adapter = netdev_priv(netdev);
	int size = 0;
	int num_rx_queues;

#ifdef VMXNET3_RSS
	if (enable_mq)
		num_rx_queues = min(VMXNET3_DEVICE_MAX_RX_QUEUES,
				    (int)num_online_cpus());
	else
#endif
		num_rx_queues = 1;
	num_rx_queues = rounddown_pow_of_two(num_rx_queues);

	cancel_work_sync(&adapter->work);

	unregister_netdev(netdev);

	vmxnet3_free_intr_resources(adapter);
	vmxnet3_free_pci_resources(adapter);
#ifdef VMXNET3_RSS
	kfree(adapter->rss_conf);
#endif
	kfree(adapter->pm_conf);

	size = sizeof(struct Vmxnet3_TxQueueDesc) * adapter->num_tx_queues;
	size += sizeof(struct Vmxnet3_RxQueueDesc) * num_rx_queues;
	pci_free_consistent(adapter->pdev, size, adapter->tqd_start,
			    adapter->queue_desc_pa);
	pci_free_consistent(adapter->pdev, sizeof(struct Vmxnet3_DriverShared),
			    adapter->shared, adapter->shared_pa);
	free_netdev(netdev);
}