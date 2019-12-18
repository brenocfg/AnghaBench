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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct ixgbe_adapter {int eeprom_verh; int eeprom_verl; int /*<<< orphan*/  pdev; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  regdump_len; int /*<<< orphan*/  testinfo_len; int /*<<< orphan*/  n_stats; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_STATS_LEN ; 
 int /*<<< orphan*/  IXGBE_TEST_LEN ; 
 int /*<<< orphan*/  ixgbe_driver_name ; 
 int /*<<< orphan*/  ixgbe_driver_version ; 
 int /*<<< orphan*/  ixgbe_get_regs_len (struct net_device*) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ixgbe_get_drvinfo(struct net_device *netdev,
                              struct ethtool_drvinfo *drvinfo)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	u32 nvm_track_id;

	strlcpy(drvinfo->driver, ixgbe_driver_name, sizeof(drvinfo->driver));
	strlcpy(drvinfo->version, ixgbe_driver_version,
		sizeof(drvinfo->version));

	nvm_track_id = (adapter->eeprom_verh << 16) |
			adapter->eeprom_verl;
	snprintf(drvinfo->fw_version, sizeof(drvinfo->fw_version), "0x%08x",
		 nvm_track_id);

	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev),
		sizeof(drvinfo->bus_info));
	drvinfo->n_stats = IXGBE_STATS_LEN;
	drvinfo->testinfo_len = IXGBE_TEST_LEN;
	drvinfo->regdump_len = ixgbe_get_regs_len(netdev);
}