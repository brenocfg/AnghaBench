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
struct resource {int /*<<< orphan*/  start; } ;
struct pxa3xx_nand_info {int /*<<< orphan*/  clk; int /*<<< orphan*/  mmio_base; struct mtd_info* data_buff; int /*<<< orphan*/  data_buff_phys; int /*<<< orphan*/  data_buff_size; int /*<<< orphan*/  data_dma_ch; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mtd_info {struct pxa3xx_nand_info* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQ_NAND ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_mtd_device (struct mtd_info*) ; 
 int /*<<< orphan*/  del_mtd_partitions (struct mtd_info*) ; 
 int /*<<< orphan*/  dma_free_writecombine (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mtd_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct pxa3xx_nand_info*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mtd_info*) ; 
 struct mtd_info* platform_get_drvdata (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pxa_free_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 scalar_t__ use_dma ; 

__attribute__((used)) static int pxa3xx_nand_remove(struct platform_device *pdev)
{
	struct mtd_info *mtd = platform_get_drvdata(pdev);
	struct pxa3xx_nand_info *info = mtd->priv;
	struct resource *r;

	platform_set_drvdata(pdev, NULL);

	del_mtd_device(mtd);
	del_mtd_partitions(mtd);
	free_irq(IRQ_NAND, info);
	if (use_dma) {
		pxa_free_dma(info->data_dma_ch);
		dma_free_writecombine(&pdev->dev, info->data_buff_size,
				info->data_buff, info->data_buff_phys);
	} else
		kfree(info->data_buff);

	iounmap(info->mmio_base);
	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(r->start, resource_size(r));

	clk_disable(info->clk);
	clk_put(info->clk);

	kfree(mtd);
	return 0;
}