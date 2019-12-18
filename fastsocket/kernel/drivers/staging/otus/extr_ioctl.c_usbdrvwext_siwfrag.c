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
typedef  scalar_t__ u16_t ;
struct usbdrv_private {int DeviceOpened; } ;
struct net_device {struct usbdrv_private* ml_priv; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {scalar_t__ value; scalar_t__ disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  zfiWlanSetFragThreshold (struct net_device*,scalar_t__) ; 

int usbdrvwext_siwfrag(struct net_device *dev,
		struct iw_request_info *info,
		struct iw_param *frag, char *extra)
{
	struct usbdrv_private *macp = dev->ml_priv;
	u16_t fragThreshold;

	if (macp->DeviceOpened != 1)
		return 0;

	if (frag->disabled)
		fragThreshold = 0;
	else
		fragThreshold = frag->value;

	zfiWlanSetFragThreshold(dev, fragThreshold);

	return 0;
}