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
struct sis190_private {int /*<<< orphan*/  mmio_addr; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int mdio_read (int /*<<< orphan*/ ,int,int) ; 
 struct sis190_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int __mdio_read(struct net_device *dev, int phy_id, int reg)
{
	struct sis190_private *tp = netdev_priv(dev);

	return mdio_read(tp->mmio_addr, phy_id, reg);
}