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
struct usbnet {int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  eedump_len; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct asix_data {int /*<<< orphan*/  eeprom_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_VERSION ; 
 int /*<<< orphan*/  driver_name ; 
 struct usbnet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbnet_get_drvinfo (struct net_device*,struct ethtool_drvinfo*) ; 

__attribute__((used)) static void asix_get_drvinfo (struct net_device *net,
				 struct ethtool_drvinfo *info)
{
	struct usbnet *dev = netdev_priv(net);
	struct asix_data *data = (struct asix_data *)&dev->data;

	/* Inherit standard device info */
	usbnet_get_drvinfo(net, info);
	strncpy (info->driver, driver_name, sizeof info->driver);
	strncpy (info->version, DRIVER_VERSION, sizeof info->version);
	info->eedump_len = data->eeprom_len;
}