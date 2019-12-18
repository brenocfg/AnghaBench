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
typedef  int uint16_t ;
struct pxa3xx_nand_info {int data_size; int ndcb0; int ndcb1; int ndcb2; int row_addr_cycles; int col_addr_cycles; int /*<<< orphan*/  use_ecc; struct pxa3xx_nand_flash* flash_info; } ;
struct pxa3xx_nand_flash {int page_size; struct pxa3xx_nand_cmdset* cmdset; } ;
struct pxa3xx_nand_cmdset {int program; } ;

/* Variables and functions */
 int EINVAL ; 
 int NDCB0_ADDR_CYC (int) ; 
 int NDCB0_AUTO_RS ; 
 int NDCB0_CMD_TYPE (int) ; 
 int NDCB0_DBC ; 

__attribute__((used)) static int prepare_read_prog_cmd(struct pxa3xx_nand_info *info,
			uint16_t cmd, int column, int page_addr)
{
	const struct pxa3xx_nand_flash *f = info->flash_info;
	const struct pxa3xx_nand_cmdset *cmdset = f->cmdset;

	/* calculate data size */
	switch (f->page_size) {
	case 2048:
		info->data_size = (info->use_ecc) ? 2088 : 2112;
		break;
	case 512:
		info->data_size = (info->use_ecc) ? 520 : 528;
		break;
	default:
		return -EINVAL;
	}

	/* generate values for NDCBx registers */
	info->ndcb0 = cmd | ((cmd & 0xff00) ? NDCB0_DBC : 0);
	info->ndcb1 = 0;
	info->ndcb2 = 0;
	info->ndcb0 |= NDCB0_ADDR_CYC(info->row_addr_cycles + info->col_addr_cycles);

	if (info->col_addr_cycles == 2) {
		/* large block, 2 cycles for column address
		 * row address starts from 3rd cycle
		 */
		info->ndcb1 |= page_addr << 16;
		if (info->row_addr_cycles == 3)
			info->ndcb2 = (page_addr >> 16) & 0xff;
	} else
		/* small block, 1 cycles for column address
		 * row address starts from 2nd cycle
		 */
		info->ndcb1 = page_addr << 8;

	if (cmd == cmdset->program)
		info->ndcb0 |= NDCB0_CMD_TYPE(1) | NDCB0_AUTO_RS;

	return 0;
}