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
typedef  int u16 ;
struct usbdrv_private {int DeviceOpened; int /*<<< orphan*/  cs_lock; } ;
struct net_device {struct usbdrv_private* ml_priv; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int value; int disabled; int fixed; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int zfiWlanQueryFragThreshold (struct net_device*) ; 

int usbdrvwext_giwfrag(struct net_device *dev,
		struct iw_request_info *info,
		struct iw_param *frag, char *extra)
{
	struct usbdrv_private *macp = dev->ml_priv;
	u16 val;
	unsigned long irqFlag;

	if (!netif_running(dev))
		return -EINVAL;

	if (macp->DeviceOpened != 1)
		return 0;

	spin_lock_irqsave(&macp->cs_lock, irqFlag);

	val = zfiWlanQueryFragThreshold(dev);

	frag->value = val;

	frag->disabled = (val >= 2346);
	frag->fixed = 1;

	spin_unlock_irqrestore(&macp->cs_lock, irqFlag);

	return 0;
}