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
typedef  int uint32_t ;
struct pci_dev {int dummy; } ;
struct mtd_info {struct cafe_priv* priv; } ;
struct cafe_priv {int dmaaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLOBAL_CTRL ; 
 int /*<<< orphan*/  GLOBAL_IRQ_MASK ; 
 int /*<<< orphan*/  NAND_DMA_ADDR0 ; 
 int /*<<< orphan*/  NAND_DMA_ADDR1 ; 
 int /*<<< orphan*/  NAND_DMA_CTRL ; 
 int /*<<< orphan*/  NAND_IRQ_MASK ; 
 int /*<<< orphan*/  NAND_RESET ; 
 int /*<<< orphan*/  NAND_TIMING1 ; 
 int /*<<< orphan*/  NAND_TIMING2 ; 
 int /*<<< orphan*/  NAND_TIMING3 ; 
 int cafe_readl (struct cafe_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cafe_writel (struct cafe_priv*,int,int /*<<< orphan*/ ) ; 
 struct mtd_info* pci_get_drvdata (struct pci_dev*) ; 
 int* timing ; 

__attribute__((used)) static int cafe_nand_resume(struct pci_dev *pdev)
{
	uint32_t ctrl;
	struct mtd_info *mtd = pci_get_drvdata(pdev);
	struct cafe_priv *cafe = mtd->priv;

       /* Start off by resetting the NAND controller completely */
	cafe_writel(cafe, 1, NAND_RESET);
	cafe_writel(cafe, 0, NAND_RESET);
	cafe_writel(cafe, 0xffffffff, NAND_IRQ_MASK);

	/* Restore timing configuration */
	cafe_writel(cafe, timing[0], NAND_TIMING1);
	cafe_writel(cafe, timing[1], NAND_TIMING2);
	cafe_writel(cafe, timing[2], NAND_TIMING3);

        /* Disable master reset, enable NAND clock */
	ctrl = cafe_readl(cafe, GLOBAL_CTRL);
	ctrl &= 0xffffeff0;
	ctrl |= 0x00007000;
	cafe_writel(cafe, ctrl | 0x05, GLOBAL_CTRL);
	cafe_writel(cafe, ctrl | 0x0a, GLOBAL_CTRL);
	cafe_writel(cafe, 0, NAND_DMA_CTRL);
	cafe_writel(cafe, 0x7006, GLOBAL_CTRL);
	cafe_writel(cafe, 0x700a, GLOBAL_CTRL);

	/* Set up DMA address */
	cafe_writel(cafe, cafe->dmaaddr & 0xffffffff, NAND_DMA_ADDR0);
	if (sizeof(cafe->dmaaddr) > 4)
	/* Shift in two parts to shut the compiler up */
		cafe_writel(cafe, (cafe->dmaaddr >> 16) >> 16, NAND_DMA_ADDR1);
	else
		cafe_writel(cafe, 0, NAND_DMA_ADDR1);

	/* Enable NAND IRQ in global IRQ mask register */
	cafe_writel(cafe, 0x80000007, GLOBAL_IRQ_MASK);
	return 0;
}