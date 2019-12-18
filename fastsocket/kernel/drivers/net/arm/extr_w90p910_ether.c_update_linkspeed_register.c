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
struct w90p910_ether {scalar_t__ reg; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned int DUPLEX_FULL ; 
 unsigned int MCMDR_FDUP ; 
 unsigned int MCMDR_OPMOD ; 
 scalar_t__ REG_MCMDR ; 
 unsigned int SPEED_100 ; 
 unsigned int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 
 struct w90p910_ether* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void update_linkspeed_register(struct net_device *dev,
				unsigned int speed, unsigned int duplex)
{
	struct w90p910_ether *ether = netdev_priv(dev);
	unsigned int val;

	val = __raw_readl(ether->reg + REG_MCMDR);

	if (speed == SPEED_100) {
		/* 100 full/half duplex */
		if (duplex == DUPLEX_FULL) {
			val |= (MCMDR_OPMOD | MCMDR_FDUP);
		} else {
			val |= MCMDR_OPMOD;
			val &= ~MCMDR_FDUP;
		}
	} else {
		/* 10 full/half duplex */
		if (duplex == DUPLEX_FULL) {
			val |= MCMDR_FDUP;
			val &= ~MCMDR_OPMOD;
		} else {
			val &= ~(MCMDR_FDUP | MCMDR_OPMOD);
		}
	}

	__raw_writel(val, ether->reg + REG_MCMDR);
}