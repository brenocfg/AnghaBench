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
struct sh_flctl {int seqin_page_addr; scalar_t__ page_size; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLDTCNTR (struct sh_flctl*) ; 
 int NAND_CMD_PAGEPROG ; 
 int NAND_CMD_SEQIN ; 
 int /*<<< orphan*/  empty_fifo (struct sh_flctl*) ; 
 struct sh_flctl* mtd_to_flctl (struct mtd_info*) ; 
 int /*<<< orphan*/  set_addr (struct mtd_info*,int,int) ; 
 int /*<<< orphan*/  set_cmd_regs (struct mtd_info*,int,int) ; 
 int /*<<< orphan*/  start_translation (struct sh_flctl*) ; 
 int /*<<< orphan*/  wait_completion (struct sh_flctl*) ; 
 int /*<<< orphan*/  write_fiforeg (struct sh_flctl*,int,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void execmd_write_oob(struct mtd_info *mtd)
{
	struct sh_flctl *flctl = mtd_to_flctl(mtd);
	int page_addr = flctl->seqin_page_addr;
	int sector, page_sectors;

	if (flctl->page_size) {
		sector = 3;
		page_sectors = 4;
	} else {
		sector = 0;
		page_sectors = 1;
	}

	set_cmd_regs(mtd, NAND_CMD_PAGEPROG,
			(NAND_CMD_PAGEPROG << 8) | NAND_CMD_SEQIN);

	for (; sector < page_sectors; sector++) {
		empty_fifo(flctl);
		set_addr(mtd, sector * 528 + 512, page_addr);
		writel(16, FLDTCNTR(flctl));	/* set read size */

		start_translation(flctl);
		write_fiforeg(flctl, 16, 16 * sector);
		wait_completion(flctl);
	}
}