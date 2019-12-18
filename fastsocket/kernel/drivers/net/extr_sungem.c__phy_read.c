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
struct gem {int dummy; } ;

/* Variables and functions */
 int __phy_read (struct gem*,int,int) ; 
 struct gem* netdev_priv (struct net_device*) ; 

__attribute__((used)) static inline int _phy_read(struct net_device *dev, int mii_id, int reg)
{
	struct gem *gp = netdev_priv(dev);
	return __phy_read(gp, mii_id, reg);
}