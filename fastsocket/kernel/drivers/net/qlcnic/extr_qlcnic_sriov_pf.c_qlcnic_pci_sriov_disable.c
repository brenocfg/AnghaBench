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
struct qlcnic_adapter {struct net_device* netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  __qlcnic_down (struct qlcnic_adapter*,struct net_device*) ; 
 int /*<<< orphan*/  __qlcnic_up (struct qlcnic_adapter*,struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ qlcnic_83xx_configure_opmode (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_sriov_pf_cleanup (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_sriov_pf_disable (struct qlcnic_adapter*) ; 

__attribute__((used)) static int qlcnic_pci_sriov_disable(struct qlcnic_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;

	if (netif_running(netdev))
		__qlcnic_down(adapter, netdev);

	qlcnic_sriov_pf_disable(adapter);

	qlcnic_sriov_pf_cleanup(adapter);

	/* After disabling SRIOV re-init the driver in default mode
	   configure opmode based on op_mode of function
	 */
	if (qlcnic_83xx_configure_opmode(adapter))
		return -EIO;

	if (netif_running(netdev))
		__qlcnic_up(adapter, netdev);

	return 0;
}