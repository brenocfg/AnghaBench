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
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM0 ; 
 unsigned int CAM0EN ; 
 scalar_t__ REG_CAMEN ; 
 unsigned int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 
 struct w90p910_ether* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  w90p910_write_cam (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void w90p910_enable_cam(struct net_device *dev)
{
	struct w90p910_ether *ether = netdev_priv(dev);
	unsigned int val;

	w90p910_write_cam(dev, CAM0, dev->dev_addr);

	val = __raw_readl(ether->reg + REG_CAMEN);
	val |= CAM0EN;
	__raw_writel(val, ether->reg + REG_CAMEN);
}