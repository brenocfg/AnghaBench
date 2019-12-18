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
 int ks8851_rdreg16 (struct ks8851_net*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ks8851_net* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks8851_phy_read(struct net_device *dev, int phy_addr, int reg)
{
	struct ks8851_net *ks = netdev_priv(dev);
	int ksreg;
	int result;

	ksreg = ks8851_phy_reg(reg);
	if (!ksreg)
		return 0x0;	/* no error return allowed, so use zero */

	mutex_lock(&ks->lock);
	result = ks8851_rdreg16(ks, ksreg);
	mutex_unlock(&ks->lock);

	return result;
}