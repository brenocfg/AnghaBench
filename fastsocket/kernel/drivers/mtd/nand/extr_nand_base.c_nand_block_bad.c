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
typedef  int u16 ;
struct nand_chip {int page_shift; int pagemask; int chip_shift; int options; int badblockpos; int (* read_byte ) (struct mtd_info*) ;int /*<<< orphan*/  (* cmdfunc ) (struct mtd_info*,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  (* read_word ) (struct mtd_info*) ;int /*<<< orphan*/  (* select_chip ) (struct mtd_info*,int) ;} ;
struct mtd_info {struct nand_chip* priv; } ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  FL_READING ; 
 int NAND_BUSWIDTH_16 ; 
 int /*<<< orphan*/  NAND_CMD_READOOB ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_get_device (struct nand_chip*,struct mtd_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_release_device (struct mtd_info*) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub3 (struct mtd_info*) ; 
 int /*<<< orphan*/  stub4 (struct mtd_info*,int /*<<< orphan*/ ,int,int) ; 
 int stub5 (struct mtd_info*) ; 

__attribute__((used)) static int nand_block_bad(struct mtd_info *mtd, loff_t ofs, int getchip)
{
	int page, chipnr, res = 0;
	struct nand_chip *chip = mtd->priv;
	u16 bad;

	page = (int)(ofs >> chip->page_shift) & chip->pagemask;

	if (getchip) {
		chipnr = (int)(ofs >> chip->chip_shift);

		nand_get_device(chip, mtd, FL_READING);

		/* Select the NAND device */
		chip->select_chip(mtd, chipnr);
	}

	if (chip->options & NAND_BUSWIDTH_16) {
		chip->cmdfunc(mtd, NAND_CMD_READOOB, chip->badblockpos & 0xFE,
			      page);
		bad = cpu_to_le16(chip->read_word(mtd));
		if (chip->badblockpos & 0x1)
			bad >>= 8;
		if ((bad & 0xFF) != 0xff)
			res = 1;
	} else {
		chip->cmdfunc(mtd, NAND_CMD_READOOB, chip->badblockpos, page);
		if (chip->read_byte(mtd) != 0xff)
			res = 1;
	}

	if (getchip)
		nand_release_device(mtd);

	return res;
}