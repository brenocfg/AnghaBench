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
struct ethtool_drvinfo {int /*<<< orphan*/  n_stats; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_ENET_STATS_LEN ; 
 char* bcm_enet_driver_name ; 
 char* bcm_enet_driver_version ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void bcm_enet_get_drvinfo(struct net_device *netdev,
				 struct ethtool_drvinfo *drvinfo)
{
	strncpy(drvinfo->driver, bcm_enet_driver_name, 32);
	strncpy(drvinfo->version, bcm_enet_driver_version, 32);
	strncpy(drvinfo->fw_version, "N/A", 32);
	strncpy(drvinfo->bus_info, "bcm63xx", 32);
	drvinfo->n_stats = BCM_ENET_STATS_LEN;
}