#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int len; int ooblen; int ooboffs; int /*<<< orphan*/ * oobbuf; int /*<<< orphan*/ * datbuf; } ;
struct nand_chip {int bbt_erase_shift; int* bbt; int options; int badblockpos; TYPE_2__ ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  badblocks; } ;
struct mtd_info {TYPE_1__ ecc_stats; scalar_t__ oobsize; struct nand_chip* priv; } ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  FL_WRITING ; 
 int NAND_USE_FLASH_BBT ; 
 int nand_do_write_oob (struct mtd_info*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  nand_get_device (struct nand_chip*,struct mtd_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_release_device (struct mtd_info*) ; 
 int nand_update_bbt (struct mtd_info*,int) ; 

__attribute__((used)) static int nand_default_block_markbad(struct mtd_info *mtd, loff_t ofs)
{
	struct nand_chip *chip = mtd->priv;
	uint8_t buf[2] = { 0, 0 };
	int block, ret;

	/* Get block number */
	block = (int)(ofs >> chip->bbt_erase_shift);
	if (chip->bbt)
		chip->bbt[block >> 2] |= 0x01 << ((block & 0x03) << 1);

	/* Do we have a flash based bad block table ? */
	if (chip->options & NAND_USE_FLASH_BBT)
		ret = nand_update_bbt(mtd, ofs);
	else {
		/* We write two bytes, so we dont have to mess with 16 bit
		 * access
		 */
		nand_get_device(chip, mtd, FL_WRITING);
		ofs += mtd->oobsize;
		chip->ops.len = chip->ops.ooblen = 2;
		chip->ops.datbuf = NULL;
		chip->ops.oobbuf = buf;
		chip->ops.ooboffs = chip->badblockpos & ~0x01;

		ret = nand_do_write_oob(mtd, ofs, &chip->ops);
		nand_release_device(mtd);
	}
	if (!ret)
		mtd->ecc_stats.badblocks++;

	return ret;
}