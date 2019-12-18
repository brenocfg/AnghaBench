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
struct can_priv {int /*<<< orphan*/  restart_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  can_flush_echo_skb (struct net_device*) ; 
 scalar_t__ del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct can_priv* netdev_priv (struct net_device*) ; 

void close_candev(struct net_device *dev)
{
	struct can_priv *priv = netdev_priv(dev);

	if (del_timer_sync(&priv->restart_timer))
		dev_put(dev);
	can_flush_echo_skb(dev);
}