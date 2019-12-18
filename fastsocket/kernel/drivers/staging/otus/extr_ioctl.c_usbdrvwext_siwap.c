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
typedef  int /*<<< orphan*/  u16_t ;
struct usbdrv_private {int DeviceOpened; } ;
struct sockaddr {int /*<<< orphan*/ * sa_data; } ;
struct net_device {struct usbdrv_private* ml_priv; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ZM_MODE_AP ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  zfiWlanDisable (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfiWlanEnable (struct net_device*) ; 
 scalar_t__ zfiWlanQueryWlanMode (struct net_device*) ; 
 int /*<<< orphan*/  zfiWlanSetBssid (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfiWlanSetMacAddress (struct net_device*,int /*<<< orphan*/ *) ; 

int usbdrvwext_siwap(struct net_device *dev, struct iw_request_info *info,
		struct sockaddr *MacAddr, char *extra)
{
	struct usbdrv_private *macp = dev->ml_priv;

	if (!netif_running(dev))
		return -EINVAL;

	if (zfiWlanQueryWlanMode(dev) == ZM_MODE_AP) {
		/* AP Mode */
		zfiWlanSetMacAddress(dev, (u16_t *)&MacAddr->sa_data[0]);
	} else {
		/* STA Mode */
		zfiWlanSetBssid(dev, &MacAddr->sa_data[0]);
	}

	if (macp->DeviceOpened == 1) {
		/* u8_t wpaieLen,wpaie[80]; */
		/* zfiWlanQueryWpaIe(dev, wpaie, &wpaieLen); */
		zfiWlanDisable(dev, 0);
		zfiWlanEnable(dev);
		/* if (wpaieLen > 2) */
		/* zfiWlanSetWpaIe(dev, wpaie, wpaieLen); */
	}

	return 0;
}