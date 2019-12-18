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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct i596_private {int options; int /*<<< orphan*/  mpu_port; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int OPT_MPU_16BIT ; 
 struct i596_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mpu_port(struct net_device *dev, int c, dma_addr_t x)
{
	struct i596_private *lp = netdev_priv(dev);

	u32 v = (u32) (c) | (u32) (x);

	if (lp->options & OPT_MPU_16BIT) {
		writew(v & 0xffff, lp->mpu_port);
		wmb();  /* order writes to MPU port */
		udelay(1);
		writew(v >> 16, lp->mpu_port);
	} else {
		writel(v, lp->mpu_port);
		wmb();  /* order writes to MPU port */
		udelay(1);
		writel(v, lp->mpu_port);
	}
}