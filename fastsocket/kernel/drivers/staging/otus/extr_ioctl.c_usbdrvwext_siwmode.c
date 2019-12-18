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
union iwreq_data {int mode; } ;
typedef  int /*<<< orphan*/  u8_t ;
struct usbdrv_private {int DeviceOpened; } ;
struct net_device {struct usbdrv_private* ml_priv; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IW_MODE_ADHOC 130 
#define  IW_MODE_INFRA 129 
#define  IW_MODE_MASTER 128 
 int /*<<< orphan*/  ZM_MODE_AP ; 
 int /*<<< orphan*/  ZM_MODE_IBSS ; 
 int /*<<< orphan*/  ZM_MODE_INFRASTRUCTURE ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  zfiWlanDisable (struct net_device*,int) ; 
 int /*<<< orphan*/  zfiWlanEnable (struct net_device*) ; 
 int /*<<< orphan*/  zfiWlanSetWlanMode (struct net_device*,int /*<<< orphan*/ ) ; 

int usbdrvwext_siwmode(struct net_device *dev,
		struct iw_request_info *info,
		union iwreq_data *wrq, char *extra)
{
	struct usbdrv_private *macp = dev->ml_priv;
	u8_t WlanMode;

	if (!netif_running(dev))
		return -EINVAL;

	if (macp->DeviceOpened != 1)
		return 0;

	switch (wrq->mode) {
	case IW_MODE_MASTER:
		WlanMode = ZM_MODE_AP;
		break;
	case IW_MODE_INFRA:
		WlanMode = ZM_MODE_INFRASTRUCTURE;
		break;
	case IW_MODE_ADHOC:
		WlanMode = ZM_MODE_IBSS;
		break;
	default:
		WlanMode = ZM_MODE_IBSS;
		break;
	}

	zfiWlanSetWlanMode(dev, WlanMode);
	zfiWlanDisable(dev, 1);
	zfiWlanEnable(dev);

	return 0;
}