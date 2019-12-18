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
struct ixgb_adapter {int /*<<< orphan*/  pdev; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  eedump_len; int /*<<< orphan*/  regdump_len; int /*<<< orphan*/  n_stats; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGB_STATS_LEN ; 
 char* ixgb_driver_name ; 
 char* ixgb_driver_version ; 
 int /*<<< orphan*/  ixgb_get_eeprom_len (struct net_device*) ; 
 int /*<<< orphan*/  ixgb_get_regs_len (struct net_device*) ; 
 struct ixgb_adapter* netdev_priv (struct net_device*) ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
ixgb_get_drvinfo(struct net_device *netdev,
		   struct ethtool_drvinfo *drvinfo)
{
	struct ixgb_adapter *adapter = netdev_priv(netdev);

	strncpy(drvinfo->driver,  ixgb_driver_name, 32);
	strncpy(drvinfo->version, ixgb_driver_version, 32);
	strncpy(drvinfo->fw_version, "N/A", 32);
	strncpy(drvinfo->bus_info, pci_name(adapter->pdev), 32);
	drvinfo->n_stats = IXGB_STATS_LEN;
	drvinfo->regdump_len = ixgb_get_regs_len(netdev);
	drvinfo->eedump_len = ixgb_get_eeprom_len(netdev);
}