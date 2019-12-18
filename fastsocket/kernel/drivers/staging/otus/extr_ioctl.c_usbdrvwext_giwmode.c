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
struct usbdrv_private {int DeviceOpened; int /*<<< orphan*/  cs_lock; } ;
struct net_device {struct usbdrv_private* ml_priv; } ;
struct iw_request_info {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IW_MODE_ADHOC ; 
 int /*<<< orphan*/  IW_MODE_INFRA ; 
 int /*<<< orphan*/  IW_MODE_MASTER ; 
#define  ZM_MODE_AP 130 
#define  ZM_MODE_IBSS 129 
#define  ZM_MODE_INFRASTRUCTURE 128 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int zfiWlanQueryWlanMode (struct net_device*) ; 

int usbdrvwext_giwmode(struct net_device *dev,
	struct iw_request_info *info,
	__u32 *mode, char *extra)
{
	unsigned long irqFlag;
	struct usbdrv_private *macp = dev->ml_priv;

	if (!netif_running(dev))
		return -EINVAL;

	if (macp->DeviceOpened != 1)
		return 0;

	spin_lock_irqsave(&macp->cs_lock, irqFlag);

	switch (zfiWlanQueryWlanMode(dev)) {
	case ZM_MODE_AP:
		*mode = IW_MODE_MASTER;
		break;
	case ZM_MODE_INFRASTRUCTURE:
		*mode = IW_MODE_INFRA;
		break;
	case ZM_MODE_IBSS:
		*mode = IW_MODE_ADHOC;
		break;
	default:
		*mode = IW_MODE_ADHOC;
		break;
	}

	spin_unlock_irqrestore(&macp->cs_lock, irqFlag);

	return 0;
}