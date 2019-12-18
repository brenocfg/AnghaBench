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
struct sh_flctl {int* done_buff; scalar_t__ page_size; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLDTCNTR (struct sh_flctl*) ; 
 int NAND_CMD_READ0 ; 
 int NAND_CMD_READSTART ; 
 int /*<<< orphan*/  empty_fifo (struct sh_flctl*) ; 
 struct sh_flctl* mtd_to_flctl (struct mtd_info*) ; 
 int /*<<< orphan*/  read_fiforeg (struct sh_flctl*,int,int) ; 
 int /*<<< orphan*/  set_addr (struct mtd_info*,int,int) ; 
 int /*<<< orphan*/  set_cmd_regs (struct mtd_info*,int,int) ; 
 int /*<<< orphan*/  start_translation (struct sh_flctl*) ; 
 int /*<<< orphan*/  wait_completion (struct sh_flctl*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void execmd_read_oob(struct mtd_info *mtd, int page_addr)
{
	struct sh_flctl *flctl = mtd_to_flctl(mtd);

	set_cmd_regs(mtd, NAND_CMD_READ0,
		(NAND_CMD_READSTART << 8) | NAND_CMD_READ0);

	empty_fifo(flctl);
	if (flctl->page_size) {
		int i;
		/* In case that the page size is 2k */
		for (i = 0; i < 16 * 3; i++)
			flctl->done_buff[i] = 0xFF;

		set_addr(mtd, 3 * 528 + 512, page_addr);
		writel(16, FLDTCNTR(flctl));

		start_translation(flctl);
		read_fiforeg(flctl, 16, 16 * 3);
		wait_completion(flctl);
	} else {
		/* In case that the page size is 512b */
		set_addr(mtd, 512, page_addr);
		writel(16, FLDTCNTR(flctl));

		start_translation(flctl);
		read_fiforeg(flctl, 16, 0);
		wait_completion(flctl);
	}
}