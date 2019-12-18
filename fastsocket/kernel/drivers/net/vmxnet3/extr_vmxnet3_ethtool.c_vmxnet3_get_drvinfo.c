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
struct vmxnet3_adapter {int /*<<< orphan*/  pdev; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  regdump_len; scalar_t__ eedump_len; scalar_t__ testinfo_len; int /*<<< orphan*/  n_stats; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_SS_STATS ; 
 int /*<<< orphan*/  VMXNET3_DRIVER_VERSION_REPORT ; 
 struct vmxnet3_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmxnet3_driver_name ; 
 int /*<<< orphan*/  vmxnet3_get_regs_len (struct net_device*) ; 
 int /*<<< orphan*/  vmxnet3_get_sset_count (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vmxnet3_get_drvinfo(struct net_device *netdev, struct ethtool_drvinfo *drvinfo)
{
	struct vmxnet3_adapter *adapter = netdev_priv(netdev);

	strlcpy(drvinfo->driver, vmxnet3_driver_name, sizeof(drvinfo->driver));

	strlcpy(drvinfo->version, VMXNET3_DRIVER_VERSION_REPORT,
		sizeof(drvinfo->version));

	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev),
		sizeof(drvinfo->bus_info));
	drvinfo->n_stats = vmxnet3_get_sset_count(netdev, ETH_SS_STATS);
	drvinfo->testinfo_len = 0;
	drvinfo->eedump_len   = 0;
	drvinfo->regdump_len  = vmxnet3_get_regs_len(netdev);
}