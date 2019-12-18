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
struct iw_param {int disabled; } ;

/* Variables and functions */
 scalar_t__ ZM_STA_PS_NONE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ zfiWlanQueryPowerSaveMode (struct net_device*) ; 

int usbdrvwext_giwpower(struct net_device *dev,
		struct iw_request_info *info,
		struct iw_param *frq, char *extra)
{
	unsigned long irqFlag;
	struct usbdrv_private *macp = dev->ml_priv;

	if (macp->DeviceOpened != 1)
		return 0;

	spin_lock_irqsave(&macp->cs_lock, irqFlag);

	if (zfiWlanQueryPowerSaveMode(dev) == ZM_STA_PS_NONE)
		frq->disabled = 1;
	else
		frq->disabled = 0;

	spin_unlock_irqrestore(&macp->cs_lock, irqFlag);

	return 0;
}