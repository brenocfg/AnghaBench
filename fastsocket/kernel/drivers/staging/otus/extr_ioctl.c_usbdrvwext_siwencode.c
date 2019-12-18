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
struct zsKeyInfo {char* key; int keyIndex; int /*<<< orphan*/  flag; int /*<<< orphan*/  keyLength; } ;
struct usbdrv_private {int DeviceOpened; } ;
struct net_device {struct usbdrv_private* ml_priv; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int flags; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FALSE ; 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_INDEX ; 
 int ZM_ENCRYPTION_WEP_DISABLED ; 
 int ZM_ENCRYPTION_WEP_ENABLED ; 
 int /*<<< orphan*/  ZM_KEY_FLAG_DEFAULT_KEY ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  zfiWlanDisable (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfiWlanEnable (struct net_device*) ; 
 int /*<<< orphan*/  zfiWlanQueryFrequency (struct net_device*) ; 
 int /*<<< orphan*/  zfiWlanRemoveKey (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfiWlanSetFrequency (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfiWlanSetKey (struct net_device*,struct zsKeyInfo) ; 
 int /*<<< orphan*/  zfiWlanSetWepStatus (struct net_device*,int) ; 

int usbdrvwext_siwencode(struct net_device *dev,
		struct iw_request_info *info,
		struct iw_point *erq, char *key)
{
	struct zsKeyInfo keyInfo;
	int i;
	int WepState = ZM_ENCRYPTION_WEP_DISABLED;
	struct usbdrv_private *macp = dev->ml_priv;

	if (!netif_running(dev))
		return -EINVAL;

	if ((erq->flags & IW_ENCODE_DISABLED) == 0) {
		keyInfo.key = key;
		keyInfo.keyLength = erq->length;
		keyInfo.keyIndex = (erq->flags & IW_ENCODE_INDEX) - 1;
		if (keyInfo.keyIndex >= 4)
			keyInfo.keyIndex = 0;
		keyInfo.flag = ZM_KEY_FLAG_DEFAULT_KEY;

		zfiWlanSetKey(dev, keyInfo);
		WepState = ZM_ENCRYPTION_WEP_ENABLED;
	} else {
		for (i = 1; i < 4; i++)
			zfiWlanRemoveKey(dev, 0, i);
		WepState = ZM_ENCRYPTION_WEP_DISABLED;
		/* zfiWlanSetEncryMode(dev, ZM_NO_WEP); */
	}

	if (macp->DeviceOpened == 1) {
		zfiWlanSetWepStatus(dev, WepState);
		zfiWlanSetFrequency(dev, zfiWlanQueryFrequency(dev), FALSE);
		/* zfiWlanSetEncryMode(dev, zfiWlanQueryEncryMode(dev)); */
		/* u8_t wpaieLen,wpaie[50]; */
		/* zfiWlanQueryWpaIe(dev, wpaie, &wpaieLen); */
		zfiWlanDisable(dev, 0);
		zfiWlanEnable(dev);
		/* if (wpaieLen > 2) */
		/* zfiWlanSetWpaIe(dev, wpaie, wpaieLen); */
	}

	return 0;
}