#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct mtd_info {struct cafe_priv* priv; } ;
struct cafe_priv {TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  NAND_IRQ ; 
 int /*<<< orphan*/  cafe_dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int cafe_readl (struct cafe_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cafe_writel (struct cafe_priv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t cafe_nand_interrupt(int irq, void *id)
{
	struct mtd_info *mtd = id;
	struct cafe_priv *cafe = mtd->priv;
	uint32_t irqs = cafe_readl(cafe, NAND_IRQ);
	cafe_writel(cafe, irqs & ~0x90000000, NAND_IRQ);
	if (!irqs)
		return IRQ_NONE;

	cafe_dev_dbg(&cafe->pdev->dev, "irq, bits %x (%x)\n", irqs, cafe_readl(cafe, NAND_IRQ));
	return IRQ_HANDLED;
}