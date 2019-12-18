#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct octeon_ethernet {int /*<<< orphan*/  poll; } ;
struct net_device {TYPE_1__* netdev_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ndo_stop ) (struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cvm_oct_common_init (struct net_device*) ; 
 int /*<<< orphan*/  cvm_oct_xaui_poll ; 
 struct octeon_ethernet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  octeon_is_simulation () ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 

int cvm_oct_xaui_init(struct net_device *dev)
{
	struct octeon_ethernet *priv = netdev_priv(dev);
	cvm_oct_common_init(dev);
	dev->netdev_ops->ndo_stop(dev);
	if (!octeon_is_simulation())
		priv->poll = cvm_oct_xaui_poll;

	return 0;
}