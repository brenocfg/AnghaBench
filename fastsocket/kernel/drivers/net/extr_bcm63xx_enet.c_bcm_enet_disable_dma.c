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
struct bcm_enet_priv {int dummy; } ;

/* Variables and functions */
 int ENETDMA_CHANCFG_EN_MASK ; 
 int /*<<< orphan*/  ENETDMA_CHANCFG_REG (int) ; 
 int enet_dma_readl (struct bcm_enet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enet_dma_writel (struct bcm_enet_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void bcm_enet_disable_dma(struct bcm_enet_priv *priv, int chan)
{
	int limit;

	enet_dma_writel(priv, 0, ENETDMA_CHANCFG_REG(chan));

	limit = 1000;
	do {
		u32 val;

		val = enet_dma_readl(priv, ENETDMA_CHANCFG_REG(chan));
		if (!(val & ENETDMA_CHANCFG_EN_MASK))
			break;
		udelay(1);
	} while (limit--);
}