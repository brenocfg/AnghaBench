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
typedef  int /*<<< orphan*/  u8 ;
struct usbnet {int dummy; } ;
struct rndis_wlan_private {int /*<<< orphan*/  radio_on; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int get_bssid (struct usbnet*,int /*<<< orphan*/ *) ; 
 struct rndis_wlan_private* get_rndis_wlan_priv (struct usbnet*) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool is_associated(struct usbnet *usbdev)
{
	struct rndis_wlan_private *priv = get_rndis_wlan_priv(usbdev);
	u8 bssid[ETH_ALEN];
	int ret;

	if (!priv->radio_on)
		return false;

	ret = get_bssid(usbdev, bssid);

	return (ret == 0 && !is_zero_ether_addr(bssid));
}