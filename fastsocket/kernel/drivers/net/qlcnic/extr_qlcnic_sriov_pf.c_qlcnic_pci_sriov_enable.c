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
struct qlcnic_adapter {int flags; int /*<<< orphan*/  portnum; struct net_device* netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int QLCNIC_MSIX_ENABLED ; 
 int /*<<< orphan*/  __qlcnic_down (struct qlcnic_adapter*,struct net_device*) ; 
 int __qlcnic_pci_sriov_enable (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  __qlcnic_up (struct qlcnic_adapter*,struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ qlcnic_83xx_configure_opmode (struct qlcnic_adapter*) ; 

__attribute__((used)) static int qlcnic_pci_sriov_enable(struct qlcnic_adapter *adapter, int num_vfs)
{
	struct net_device *netdev = adapter->netdev;
	int err;

	if (!(adapter->flags & QLCNIC_MSIX_ENABLED)) {
		netdev_err(netdev,
			   "SR-IOV cannot be enabled, when legacy interrupts are enabled\n");
		return -EIO;
	}

	if (netif_running(netdev))
		__qlcnic_down(adapter, netdev);

	err = __qlcnic_pci_sriov_enable(adapter, num_vfs);
	if (err) {
		netdev_info(netdev, "Failed to enable SR-IOV on port %d\n",
			    adapter->portnum);

		err = -EIO;
		if (qlcnic_83xx_configure_opmode(adapter))
			goto error;
	} else {
		netdev_info(netdev,
			    "SR-IOV is enabled successfully on port %d\n",
			    adapter->portnum);
		/* Return number of vfs enabled */
		err = num_vfs;
	}
	if (netif_running(netdev))
		__qlcnic_up(adapter, netdev);

error:
	return err;
}