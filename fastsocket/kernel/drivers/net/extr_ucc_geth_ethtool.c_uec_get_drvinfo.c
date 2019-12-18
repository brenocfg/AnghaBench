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
struct ethtool_drvinfo {int /*<<< orphan*/  regdump_len; scalar_t__ eedump_len; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 char* DRV_NAME ; 
 char* DRV_VERSION ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  uec_get_regs_len (struct net_device*) ; 

__attribute__((used)) static void
uec_get_drvinfo(struct net_device *netdev,
                       struct ethtool_drvinfo *drvinfo)
{
	strncpy(drvinfo->driver, DRV_NAME, 32);
	strncpy(drvinfo->version, DRV_VERSION, 32);
	strncpy(drvinfo->fw_version, "N/A", 32);
	strncpy(drvinfo->bus_info, "QUICC ENGINE", 32);
	drvinfo->eedump_len = 0;
	drvinfo->regdump_len = uec_get_regs_len(netdev);
}