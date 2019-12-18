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
struct igbvf_adapter {int /*<<< orphan*/  pdev; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  eedump_len; int /*<<< orphan*/  regdump_len; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  igbvf_driver_name ; 
 int /*<<< orphan*/  igbvf_driver_version ; 
 int /*<<< orphan*/  igbvf_get_eeprom_len (struct net_device*) ; 
 int /*<<< orphan*/  igbvf_get_regs_len (struct net_device*) ; 
 struct igbvf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void igbvf_get_drvinfo(struct net_device *netdev,
                              struct ethtool_drvinfo *drvinfo)
{
	struct igbvf_adapter *adapter = netdev_priv(netdev);

	strlcpy(drvinfo->driver,  igbvf_driver_name, sizeof(drvinfo->driver));
	strlcpy(drvinfo->version, igbvf_driver_version,
		sizeof(drvinfo->version));
	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev),
		sizeof(drvinfo->bus_info));
	drvinfo->regdump_len = igbvf_get_regs_len(netdev);
	drvinfo->eedump_len = igbvf_get_eeprom_len(netdev);
}