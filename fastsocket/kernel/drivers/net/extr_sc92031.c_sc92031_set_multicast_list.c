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
struct sc92031_priv {int /*<<< orphan*/  lock; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _sc92031_set_mar (struct net_device*) ; 
 int /*<<< orphan*/  _sc92031_set_rx_config (struct net_device*) ; 
 int /*<<< orphan*/  mmiowb () ; 
 struct sc92031_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sc92031_set_multicast_list(struct net_device *dev)
{
	struct sc92031_priv *priv = netdev_priv(dev);

	spin_lock_bh(&priv->lock);

	_sc92031_set_mar(dev);
	_sc92031_set_rx_config(dev);
	mmiowb();

	spin_unlock_bh(&priv->lock);
}