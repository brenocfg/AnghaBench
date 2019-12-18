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
typedef  int /*<<< orphan*/  zero_addr ;
typedef  int u8_t ;
struct usbdrv_private {int DeviceOpened; scalar_t__ adapterState; } ;
struct sockaddr {int /*<<< orphan*/ * sa_data; } ;
struct net_device {struct usbdrv_private* ml_priv; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ ZM_MODE_AP ; 
 scalar_t__ ZM_STATUS_MEDIA_CONNECT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  zfiWlanQueryBssid (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfiWlanQueryMacAddress (struct net_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ zfiWlanQueryWlanMode (struct net_device*) ; 

int usbdrvwext_giwap(struct net_device *dev,
		struct iw_request_info *info,
		struct sockaddr *MacAddr, char *extra)
{
	struct usbdrv_private *macp = dev->ml_priv;

	if (macp->DeviceOpened != 1)
		return 0;

	if (zfiWlanQueryWlanMode(dev) == ZM_MODE_AP) {
		/* AP Mode */
		zfiWlanQueryMacAddress(dev, &MacAddr->sa_data[0]);
	} else {
		/* STA Mode */
		if (macp->adapterState == ZM_STATUS_MEDIA_CONNECT) {
			zfiWlanQueryBssid(dev, &MacAddr->sa_data[0]);
		} else {
			u8_t zero_addr[6] = { 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00 };
			memcpy(&MacAddr->sa_data[0], zero_addr,
							sizeof(zero_addr));
		}
	}

	return 0;
}