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
struct net_device_stats {int collisions; } ;
struct net_device {int dummy; } ;
struct ioc3_private {struct net_device_stats stats; struct ioc3* regs; } ;
struct ioc3 {int dummy; } ;

/* Variables and functions */
 int ETCDC_COLLCNT_MASK ; 
 int ioc3_r_etcdc () ; 
 struct ioc3_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct net_device_stats *ioc3_get_stats(struct net_device *dev)
{
	struct ioc3_private *ip = netdev_priv(dev);
	struct ioc3 *ioc3 = ip->regs;

	ip->stats.collisions += (ioc3_r_etcdc() & ETCDC_COLLCNT_MASK);
	return &ip->stats;
}