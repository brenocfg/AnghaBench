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
struct bcm_enet_priv {int dummy; } ;

/* Variables and functions */
 int ENET_IR_MII ; 
 int /*<<< orphan*/  ENET_IR_REG ; 
 int /*<<< orphan*/  ENET_MIIDATA_REG ; 
 int enet_readl (struct bcm_enet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enet_writel (struct bcm_enet_priv*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int do_mdio_op(struct bcm_enet_priv *priv, unsigned int data)
{
	int limit;

	/* make sure mii interrupt status is cleared */
	enet_writel(priv, ENET_IR_MII, ENET_IR_REG);

	enet_writel(priv, data, ENET_MIIDATA_REG);
	wmb();

	/* busy wait on mii interrupt bit, with timeout */
	limit = 1000;
	do {
		if (enet_readl(priv, ENET_IR_REG) & ENET_IR_MII)
			break;
		udelay(1);
	} while (limit-- > 0);

	return (limit < 0) ? 1 : 0;
}