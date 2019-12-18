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
struct ethtool_drvinfo {char* fw_version; int /*<<< orphan*/  n_stats; scalar_t__ regdump_len; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct cas {scalar_t__ casreg_len; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ CAS_MAX_REGS ; 
 int /*<<< orphan*/  CAS_NUM_STAT_KEYS ; 
 int /*<<< orphan*/  DRV_MODULE_NAME ; 
 int /*<<< orphan*/  DRV_MODULE_VERSION ; 
 int /*<<< orphan*/  ETHTOOL_BUSINFO_LEN ; 
 struct cas* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cas_get_drvinfo(struct net_device *dev, struct ethtool_drvinfo *info)
{
	struct cas *cp = netdev_priv(dev);
	strncpy(info->driver, DRV_MODULE_NAME, ETHTOOL_BUSINFO_LEN);
	strncpy(info->version, DRV_MODULE_VERSION, ETHTOOL_BUSINFO_LEN);
	info->fw_version[0] = '\0';
	strncpy(info->bus_info, pci_name(cp->pdev), ETHTOOL_BUSINFO_LEN);
	info->regdump_len = cp->casreg_len < CAS_MAX_REGS ?
		cp->casreg_len : CAS_MAX_REGS;
	info->n_stats = CAS_NUM_STAT_KEYS;
}