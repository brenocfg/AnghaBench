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
struct s2io_nic {int /*<<< orphan*/  pdev; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  eedump_len; int /*<<< orphan*/  regdump_len; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  XENA_EEPROM_SPACE ; 
 int /*<<< orphan*/  XENA_REG_SPACE ; 
 struct s2io_nic* netdev_priv (struct net_device*) ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 char* s2io_driver_name ; 
 char* s2io_driver_version ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void s2io_ethtool_gdrvinfo(struct net_device *dev,
				  struct ethtool_drvinfo *info)
{
	struct s2io_nic *sp = netdev_priv(dev);

	strncpy(info->driver, s2io_driver_name, sizeof(info->driver));
	strncpy(info->version, s2io_driver_version, sizeof(info->version));
	strncpy(info->fw_version, "", sizeof(info->fw_version));
	strncpy(info->bus_info, pci_name(sp->pdev), sizeof(info->bus_info));
	info->regdump_len = XENA_REG_SPACE;
	info->eedump_len = XENA_EEPROM_SPACE;
}