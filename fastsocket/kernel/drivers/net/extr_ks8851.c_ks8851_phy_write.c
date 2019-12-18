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
struct ks8851_net {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ks8851_phy_reg (int) ; 
 int /*<<< orphan*/  ks8851_wrreg16 (struct ks8851_net*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ks8851_net* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ks8851_phy_write(struct net_device *dev,
			     int phy, int reg, int value)
{
	struct ks8851_net *ks = netdev_priv(dev);
	int ksreg;

	ksreg = ks8851_phy_reg(reg);
	if (ksreg) {
		mutex_lock(&ks->lock);
		ks8851_wrreg16(ks, ksreg, value);
		mutex_unlock(&ks->lock);
	}
}