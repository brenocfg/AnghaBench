#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ autoneg; } ;
struct port_info {int /*<<< orphan*/  tx_chan; TYPE_2__* adapter; TYPE_1__ link_cfg; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  fn; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int EAGAIN ; 
 int EINVAL ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  t4_restart_aneg (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int restart_autoneg(struct net_device *dev)
{
	struct port_info *p = netdev_priv(dev);

	if (!netif_running(dev))
		return -EAGAIN;
	if (p->link_cfg.autoneg != AUTONEG_ENABLE)
		return -EINVAL;
	t4_restart_aneg(p->adapter, p->adapter->fn, p->tx_chan);
	return 0;
}