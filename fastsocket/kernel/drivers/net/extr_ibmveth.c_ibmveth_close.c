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
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int /*<<< orphan*/  irq; } ;
struct ibmveth_adapter {scalar_t__ buffer_list_addr; int /*<<< orphan*/  rx_no_buffer; TYPE_1__* vdev; int /*<<< orphan*/  pool_config; int /*<<< orphan*/  napi; } ;
struct TYPE_2__ {int /*<<< orphan*/  unit_address; } ;

/* Variables and functions */
 long H_BUSY ; 
 scalar_t__ H_IS_LONG_BUSY (long) ; 
 long H_SUCCESS ; 
 int /*<<< orphan*/  VIO_IRQ_DISABLE ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 long h_free_logical_lan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h_vio_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmveth_cleanup (struct ibmveth_adapter*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,long) ; 
 struct ibmveth_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int ibmveth_close(struct net_device *netdev)
{
	struct ibmveth_adapter *adapter = netdev_priv(netdev);
	long lpar_rc;

	netdev_dbg(netdev, "close starting\n");

	napi_disable(&adapter->napi);

	if (!adapter->pool_config)
		netif_stop_queue(netdev);

	h_vio_signal(adapter->vdev->unit_address, VIO_IRQ_DISABLE);

	do {
		lpar_rc = h_free_logical_lan(adapter->vdev->unit_address);
	} while (H_IS_LONG_BUSY(lpar_rc) || (lpar_rc == H_BUSY));

	if (lpar_rc != H_SUCCESS) {
		netdev_err(netdev, "h_free_logical_lan failed with %lx, "
			   "continuing with close\n", lpar_rc);
	}

	free_irq(netdev->irq, netdev);

	adapter->rx_no_buffer = *(u64 *)(((char *)adapter->buffer_list_addr) +
						4096 - 8);

	ibmveth_cleanup(adapter);

	netdev_dbg(netdev, "close complete\n");

	return 0;
}