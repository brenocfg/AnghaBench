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
struct usbdrv_private {int DeviceOpened; } ;
struct net_device {struct usbdrv_private* ml_priv; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int flags; int length; int /*<<< orphan*/  pointer; } ;

/* Variables and functions */
 int E2BIG ; 
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  FALSE ; 
 int IW_ESSID_MAX_SIZE ; 
 scalar_t__ copy_from_user (char**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  zfiWlanDisable (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfiWlanEnable (struct net_device*) ; 
 int /*<<< orphan*/  zfiWlanQueryEncryMode (struct net_device*) ; 
 int /*<<< orphan*/  zfiWlanQueryFrequency (struct net_device*) ; 
 int /*<<< orphan*/  zfiWlanSetEncryMode (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfiWlanSetFrequency (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfiWlanSetSSID (struct net_device*,char*,int /*<<< orphan*/ ) ; 

int usbdrvwext_siwessid(struct net_device *dev,
		struct iw_request_info *info,
		struct iw_point *essid, char *extra)
{
	char EssidBuf[IW_ESSID_MAX_SIZE + 1];
	struct usbdrv_private *macp = dev->ml_priv;

	if (!netif_running(dev))
		return -EINVAL;

	if (essid->flags == 1) {
		if (essid->length > (IW_ESSID_MAX_SIZE + 1))
			return -E2BIG;

		if (copy_from_user(&EssidBuf, essid->pointer, essid->length))
			return -EFAULT;

		EssidBuf[essid->length] = '\0';
		/* printk("siwessid - Set Essid : %s\n",EssidBuf); */
		/* printk("siwessid - Essid Len : %d\n",essid->length); */
		/* printk("siwessid - Essid Flag : %x\n",essid->flags); */
		if (macp->DeviceOpened == 1) {
			zfiWlanSetSSID(dev, EssidBuf, strlen(EssidBuf));
			zfiWlanSetFrequency(dev, zfiWlanQueryFrequency(dev),
						FALSE);
			zfiWlanSetEncryMode(dev, zfiWlanQueryEncryMode(dev));
			/* u8_t wpaieLen,wpaie[50]; */
			/* zfiWlanQueryWpaIe(dev, wpaie, &wpaieLen); */
			zfiWlanDisable(dev, 0);
			zfiWlanEnable(dev);
			/* if (wpaieLen > 2) */
			/* zfiWlanSetWpaIe(dev, wpaie, wpaieLen); */
		}
	}

	return 0;
}