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
struct net_device {int dummy; } ;
struct can_priv {int /*<<< orphan*/  restart_timer; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_STATE_STOPPED ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_setup ; 
 int /*<<< orphan*/  init_timer (int /*<<< orphan*/ *) ; 
 struct can_priv* netdev_priv (struct net_device*) ; 

struct net_device *alloc_candev(int sizeof_priv)
{
	struct net_device *dev;
	struct can_priv *priv;

	dev = alloc_netdev(sizeof_priv, "can%d", can_setup);
	if (!dev)
		return NULL;

	priv = netdev_priv(dev);

	priv->state = CAN_STATE_STOPPED;

	init_timer(&priv->restart_timer);

	return dev;
}