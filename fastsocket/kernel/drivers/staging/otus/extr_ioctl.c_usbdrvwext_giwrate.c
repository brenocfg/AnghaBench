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
struct iw_param {int value; scalar_t__ disabled; scalar_t__ fixed; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int zfiWlanQueryRxRate (struct net_device*) ; 

int usbdrvwext_giwrate(struct net_device *dev,
		struct iw_request_info *info,
		struct iw_param *frq, char *extra)
{
	struct usbdrv_private *macp = dev->ml_priv;

	if (!netif_running(dev))
		return -EINVAL;

	if (macp->DeviceOpened != 1)
		return 0;

	frq->fixed = 0;
	frq->disabled = 0;
	frq->value = zfiWlanQueryRxRate(dev) * 1000;

	return 0;
}