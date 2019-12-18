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
 unsigned int MCMDR_RXON ; 
 scalar_t__ REG_MCMDR ; 
 unsigned int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 
 struct w90p910_ether* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void w90p910_enable_rx(struct net_device *dev, unsigned int enable)
{
	struct w90p910_ether *ether = netdev_priv(dev);
	unsigned int val;

	val = __raw_readl(ether->reg + REG_MCMDR);

	if (enable)
		val |= MCMDR_RXON;
	else
		val &= ~MCMDR_RXON;

	__raw_writel(val, ether->reg + REG_MCMDR);
}