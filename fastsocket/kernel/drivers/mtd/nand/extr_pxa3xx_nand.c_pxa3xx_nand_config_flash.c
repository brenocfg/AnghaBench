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
struct pxa3xx_nand_platform_data {scalar_t__ enable_arbiter; } ;
struct pxa3xx_nand_info {int oob_size; int read_id_bytes; int col_addr_cycles; int row_addr_cycles; int reg_ndcr; struct pxa3xx_nand_flash const* flash_info; struct platform_device* pdev; } ;
struct pxa3xx_nand_flash {int page_size; int flash_width; int num_blocks; int page_per_block; int dfc_width; int /*<<< orphan*/  timing; } ;
struct TYPE_2__ {struct pxa3xx_nand_platform_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int NDCR_DWIDTH_C ; 
 int NDCR_DWIDTH_M ; 
 int NDCR_ND_ARB_EN ; 
 int NDCR_PAGE_SZ ; 
 int NDCR_PG_PER_BLK ; 
 int NDCR_RA_START ; 
 int NDCR_RD_ID_CNT (int) ; 
 int NDCR_SPARE_EN ; 
 int /*<<< orphan*/  pxa3xx_nand_set_timing (struct pxa3xx_nand_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pxa3xx_nand_config_flash(struct pxa3xx_nand_info *info,
				    const struct pxa3xx_nand_flash *f)
{
	struct platform_device *pdev = info->pdev;
	struct pxa3xx_nand_platform_data *pdata = pdev->dev.platform_data;
	uint32_t ndcr = 0x00000FFF; /* disable all interrupts */

	if (f->page_size != 2048 && f->page_size != 512)
		return -EINVAL;

	if (f->flash_width != 16 && f->flash_width != 8)
		return -EINVAL;

	/* calculate flash information */
	info->oob_size = (f->page_size == 2048) ? 64 : 16;
	info->read_id_bytes = (f->page_size == 2048) ? 4 : 2;

	/* calculate addressing information */
	info->col_addr_cycles = (f->page_size == 2048) ? 2 : 1;

	if (f->num_blocks * f->page_per_block > 65536)
		info->row_addr_cycles = 3;
	else
		info->row_addr_cycles = 2;

	ndcr |= (pdata->enable_arbiter) ? NDCR_ND_ARB_EN : 0;
	ndcr |= (info->col_addr_cycles == 2) ? NDCR_RA_START : 0;
	ndcr |= (f->page_per_block == 64) ? NDCR_PG_PER_BLK : 0;
	ndcr |= (f->page_size == 2048) ? NDCR_PAGE_SZ : 0;
	ndcr |= (f->flash_width == 16) ? NDCR_DWIDTH_M : 0;
	ndcr |= (f->dfc_width == 16) ? NDCR_DWIDTH_C : 0;

	ndcr |= NDCR_RD_ID_CNT(info->read_id_bytes);
	ndcr |= NDCR_SPARE_EN; /* enable spare by default */

	info->reg_ndcr = ndcr;

	pxa3xx_nand_set_timing(info, f->timing);
	info->flash_info = f;
	return 0;
}