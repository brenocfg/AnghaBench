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
struct ethtool_drvinfo {int /*<<< orphan*/  eedump_len; int /*<<< orphan*/  regdump_len; scalar_t__ testinfo_len; scalar_t__ n_stats; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct atl2_adapter {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 char* atl2_driver_name ; 
 char* atl2_driver_version ; 
 int /*<<< orphan*/  atl2_get_eeprom_len (struct net_device*) ; 
 int /*<<< orphan*/  atl2_get_regs_len (struct net_device*) ; 
 struct atl2_adapter* netdev_priv (struct net_device*) ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void atl2_get_drvinfo(struct net_device *netdev,
	struct ethtool_drvinfo *drvinfo)
{
	struct atl2_adapter *adapter = netdev_priv(netdev);

	strncpy(drvinfo->driver,  atl2_driver_name, 32);
	strncpy(drvinfo->version, atl2_driver_version, 32);
	strncpy(drvinfo->fw_version, "L2", 32);
	strncpy(drvinfo->bus_info, pci_name(adapter->pdev), 32);
	drvinfo->n_stats = 0;
	drvinfo->testinfo_len = 0;
	drvinfo->regdump_len = atl2_get_regs_len(netdev);
	drvinfo->eedump_len = atl2_get_eeprom_len(netdev);
}