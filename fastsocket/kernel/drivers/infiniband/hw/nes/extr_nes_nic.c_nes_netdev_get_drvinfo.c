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
struct nes_vnic {TYPE_1__* nesdev; } ;
struct nes_adapter {int firmware_version; } ;
struct ethtool_drvinfo {scalar_t__ regdump_len; scalar_t__ eedump_len; scalar_t__ testinfo_len; int /*<<< orphan*/  n_stats; int /*<<< orphan*/  version; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcidev; struct nes_adapter* nesadapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  DRV_VERSION ; 
 int /*<<< orphan*/  nes_netdev_get_stats_count (struct net_device*) ; 
 struct nes_vnic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nes_netdev_get_drvinfo(struct net_device *netdev,
		struct ethtool_drvinfo *drvinfo)
{
	struct nes_vnic *nesvnic = netdev_priv(netdev);
	struct nes_adapter *nesadapter = nesvnic->nesdev->nesadapter;

	strcpy(drvinfo->driver, DRV_NAME);
	strcpy(drvinfo->bus_info, pci_name(nesvnic->nesdev->pcidev));
	sprintf(drvinfo->fw_version, "%u.%u", nesadapter->firmware_version>>16,
				nesadapter->firmware_version & 0x000000ff);
	strcpy(drvinfo->version, DRV_VERSION);
	drvinfo->n_stats = nes_netdev_get_stats_count(netdev);
	drvinfo->testinfo_len = 0;
	drvinfo->eedump_len = 0;
	drvinfo->regdump_len = 0;
}