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
struct net_device_stats {int dummy; } ;
struct net_device {int dummy; } ;
struct bdx_priv {struct net_device_stats net_stats; } ;

/* Variables and functions */
 struct bdx_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct net_device_stats *bdx_get_stats(struct net_device *ndev)
{
	struct bdx_priv *priv = netdev_priv(ndev);
	struct net_device_stats *net_stat = &priv->net_stats;
	return net_stat;
}