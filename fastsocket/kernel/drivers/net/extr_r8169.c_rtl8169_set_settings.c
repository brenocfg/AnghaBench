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
struct rtl8169_private {int /*<<< orphan*/  timer; } ;
struct net_device {int dummy; } ;
struct ethtool_cmd {int /*<<< orphan*/  advertising; int /*<<< orphan*/  duplex; int /*<<< orphan*/  autoneg; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ethtool_cmd_speed (struct ethtool_cmd*) ; 
 struct rtl8169_private* netdev_priv (struct net_device*) ; 
 int rtl8169_set_speed (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_lock_work (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_unlock_work (struct rtl8169_private*) ; 

__attribute__((used)) static int rtl8169_set_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	int ret;

	del_timer_sync(&tp->timer);

	rtl_lock_work(tp);
	ret = rtl8169_set_speed(dev, cmd->autoneg, ethtool_cmd_speed(cmd),
				cmd->duplex, cmd->advertising);
	rtl_unlock_work(tp);

	return ret;
}