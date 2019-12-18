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
struct usbnet {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  OID_802_11_BSSID ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int) ; 
 int rndis_set_oid (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_bssid(struct usbnet *usbdev, const u8 *bssid)
{
	int ret;

	ret = rndis_set_oid(usbdev, OID_802_11_BSSID, bssid, ETH_ALEN);
	if (ret < 0) {
		netdev_warn(usbdev->net, "setting BSSID[%pM] failed (%08X)\n",
			    bssid, ret);
		return ret;
	}

	return ret;
}