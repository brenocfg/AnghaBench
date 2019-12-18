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
typedef  scalar_t__ u8_t ;
struct usbdrv_private {int DeviceOpened; } ;
struct net_device {struct usbdrv_private* ml_priv; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int flags; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int EINVAL ; 
 int IW_ESSID_MAX_SIZE ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  zfiWlanQuerySSID (struct net_device*,char*,scalar_t__*) ; 

int usbdrvwext_giwessid(struct net_device *dev,
		struct iw_request_info *info,
		struct iw_point *essid, char *extra)
{
	struct usbdrv_private *macp = dev->ml_priv;
	u8_t EssidLen;
	char EssidBuf[IW_ESSID_MAX_SIZE + 1];
	int ssid_len;

	if (!netif_running(dev))
		return -EINVAL;

	if (macp->DeviceOpened != 1)
		return 0;

	zfiWlanQuerySSID(dev, &EssidBuf[0], &EssidLen);

	/* Convert type from unsigned char to char */
	ssid_len = (int)EssidLen;

	/* Make sure the essid length is not greater than IW_ESSID_MAX_SIZE */
	if (ssid_len > IW_ESSID_MAX_SIZE)
		ssid_len = IW_ESSID_MAX_SIZE;

	EssidBuf[ssid_len] = '\0';

	essid->flags = 1;
	essid->length = strlen(EssidBuf);

	memcpy(extra, EssidBuf, essid->length);
	/* wireless.c in Kernel would handle copy_to_user -- line 679 */
	/* if (essid->pointer) {
	* if (copy_to_user(essid->pointer, EssidBuf, essid->length)) {
	* printk("giwessid - copy_to_user Fail\n");
	* return -EFAULT;
	* }
	* }
	*/

	return 0;
}