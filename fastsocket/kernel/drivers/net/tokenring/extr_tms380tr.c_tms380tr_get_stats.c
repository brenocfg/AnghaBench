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
struct net_local {int /*<<< orphan*/  MacStat; } ;
struct net_device_stats {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct net_local* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct net_device_stats *tms380tr_get_stats(struct net_device *dev)
{
	struct net_local *tp = netdev_priv(dev);

	return ((struct net_device_stats *)&tp->MacStat);
}