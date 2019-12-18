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
struct ks_net {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ks_phy_reg (int) ; 
 int /*<<< orphan*/  ks_wrreg16 (struct ks_net*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ks_net* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ks_phy_write(struct net_device *netdev,
			     int phy, int reg, int value)
{
	struct ks_net *ks = netdev_priv(netdev);
	int ksreg;

	ksreg = ks_phy_reg(reg);
	if (ksreg) {
		mutex_lock(&ks->lock);
		ks_wrreg16(ks, ksreg, value);
		mutex_unlock(&ks->lock);
	}
}