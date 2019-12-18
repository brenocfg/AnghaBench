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
struct ethtool_drvinfo {scalar_t__ eedump_len; scalar_t__ regdump_len; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 char* DRV_NAME ; 
 int /*<<< orphan*/  GFAR_INFOSTR_LEN ; 
 char* gfar_driver_version ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gfar_gdrvinfo(struct net_device *dev, struct
	      ethtool_drvinfo *drvinfo)
{
	strncpy(drvinfo->driver, DRV_NAME, GFAR_INFOSTR_LEN);
	strncpy(drvinfo->version, gfar_driver_version, GFAR_INFOSTR_LEN);
	strncpy(drvinfo->fw_version, "N/A", GFAR_INFOSTR_LEN);
	strncpy(drvinfo->bus_info, "N/A", GFAR_INFOSTR_LEN);
	drvinfo->regdump_len = 0;
	drvinfo->eedump_len = 0;
}