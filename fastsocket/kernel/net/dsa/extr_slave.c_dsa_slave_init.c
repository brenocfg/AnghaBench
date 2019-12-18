#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  iflink; } ;
struct dsa_slave_priv {TYPE_3__* parent; } ;
struct TYPE_6__ {TYPE_2__* dst; } ;
struct TYPE_5__ {TYPE_1__* master_netdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 struct dsa_slave_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int dsa_slave_init(struct net_device *dev)
{
	struct dsa_slave_priv *p = netdev_priv(dev);

	dev->iflink = p->parent->dst->master_netdev->ifindex;

	return 0;
}