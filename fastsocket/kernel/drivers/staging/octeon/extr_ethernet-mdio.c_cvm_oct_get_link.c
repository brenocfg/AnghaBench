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
typedef  int /*<<< orphan*/  u32 ;
struct octeon_ethernet {int /*<<< orphan*/  mii_info; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdio_sem ; 
 int /*<<< orphan*/  mii_link_ok (int /*<<< orphan*/ *) ; 
 struct octeon_ethernet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 cvm_oct_get_link(struct net_device *dev)
{
	struct octeon_ethernet *priv = netdev_priv(dev);
	u32 ret;

	down(&mdio_sem);
	ret = mii_link_ok(&priv->mii_info);
	up(&mdio_sem);

	return ret;
}