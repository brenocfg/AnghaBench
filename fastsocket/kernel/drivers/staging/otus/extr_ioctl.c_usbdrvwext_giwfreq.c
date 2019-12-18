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
struct iw_freq {int e; int /*<<< orphan*/  m; } ;

/* Variables and functions */
 int /*<<< orphan*/  zfiWlanQueryFrequency (struct net_device*) ; 

int usbdrvwext_giwfreq(struct net_device *dev,
		struct iw_request_info *info,
		struct iw_freq *freq, char *extra)
{
	struct usbdrv_private *macp = dev->ml_priv;

	if (macp->DeviceOpened != 1)
		return 0;

	freq->m = zfiWlanQueryFrequency(dev);
	freq->e = 3;

	return 0;
}