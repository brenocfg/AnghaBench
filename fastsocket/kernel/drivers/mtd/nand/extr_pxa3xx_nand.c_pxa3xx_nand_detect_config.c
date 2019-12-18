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
struct pxa3xx_nand_info {int read_id_bytes; int reg_ndcr; int oob_size; int col_addr_cycles; int row_addr_cycles; TYPE_1__* flash_info; } ;
struct nand_flash_dev {int id; int chipsize; int /*<<< orphan*/ * name; } ;
struct TYPE_2__ {int page_per_block; int page_size; int flash_width; int dfc_width; int num_blocks; int /*<<< orphan*/ * timing; int /*<<< orphan*/ * cmdset; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  NDCR ; 
 int NDCR_DWIDTH_C ; 
 int NDCR_DWIDTH_M ; 
 int NDCR_PAGE_SZ ; 
 int NDCR_PG_PER_BLK ; 
 int __ffs (int) ; 
 scalar_t__ __readid (struct pxa3xx_nand_info*,int*) ; 
 TYPE_1__ default_flash ; 
 int /*<<< orphan*/  default_timing ; 
 int /*<<< orphan*/  largepage_cmdset ; 
 struct nand_flash_dev* nand_flash_ids ; 
 int nand_readl (struct pxa3xx_nand_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa3xx_nand_detect_timing (struct pxa3xx_nand_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smallpage_cmdset ; 

__attribute__((used)) static int pxa3xx_nand_detect_config(struct pxa3xx_nand_info *info)
{
	uint32_t ndcr = nand_readl(info, NDCR);
	struct nand_flash_dev *type = NULL;
	uint32_t id = -1;
	int i;

	default_flash.page_per_block = ndcr & NDCR_PG_PER_BLK ? 64 : 32;
	default_flash.page_size = ndcr & NDCR_PAGE_SZ ? 2048 : 512;
	default_flash.flash_width = ndcr & NDCR_DWIDTH_M ? 16 : 8;
	default_flash.dfc_width = ndcr & NDCR_DWIDTH_C ? 16 : 8;

	if (default_flash.page_size == 2048)
		default_flash.cmdset = &largepage_cmdset;
	else
		default_flash.cmdset = &smallpage_cmdset;

	/* set info fields needed to __readid */
	info->flash_info = &default_flash;
	info->read_id_bytes = (default_flash.page_size == 2048) ? 4 : 2;
	info->reg_ndcr = ndcr;

	if (__readid(info, &id))
		return -ENODEV;

	/* Lookup the flash id */
	id = (id >> 8) & 0xff;		/* device id is byte 2 */
	for (i = 0; nand_flash_ids[i].name != NULL; i++) {
		if (id == nand_flash_ids[i].id) {
			type =  &nand_flash_ids[i];
			break;
		}
	}

	if (!type)
		return -ENODEV;

	/* fill the missing flash information */
	i = __ffs(default_flash.page_per_block * default_flash.page_size);
	default_flash.num_blocks = type->chipsize << (20 - i);

	info->oob_size = (default_flash.page_size == 2048) ? 64 : 16;

	/* calculate addressing information */
	info->col_addr_cycles = (default_flash.page_size == 2048) ? 2 : 1;

	if (default_flash.num_blocks * default_flash.page_per_block > 65536)
		info->row_addr_cycles = 3;
	else
		info->row_addr_cycles = 2;

	pxa3xx_nand_detect_timing(info, &default_timing);
	default_flash.timing = &default_timing;

	return 0;
}