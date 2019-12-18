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
struct rtl_fw {int /*<<< orphan*/  phy_action; } ;
struct rtl8169_private {struct net_device* dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  netif_err (struct rtl8169_private*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 scalar_t__ rtl_fw_data_ok (struct rtl8169_private*,struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl_fw_format_ok (struct rtl8169_private*,struct rtl_fw*) ; 

__attribute__((used)) static int rtl_check_firmware(struct rtl8169_private *tp, struct rtl_fw *rtl_fw)
{
	struct net_device *dev = tp->dev;
	int rc = -EINVAL;

	if (!rtl_fw_format_ok(tp, rtl_fw)) {
		netif_err(tp, ifup, dev, "invalid firwmare\n");
		goto out;
	}

	if (rtl_fw_data_ok(tp, dev, &rtl_fw->phy_action))
		rc = 0;
out:
	return rc;
}