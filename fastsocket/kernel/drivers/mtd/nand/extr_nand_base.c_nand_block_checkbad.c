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
struct nand_chip {int (* block_bad ) (struct mtd_info*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  bbt; } ;
struct mtd_info {struct nand_chip* priv; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int nand_isbad_bbt (struct mtd_info*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct mtd_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nand_block_checkbad(struct mtd_info *mtd, loff_t ofs, int getchip,
			       int allowbbt)
{
	struct nand_chip *chip = mtd->priv;

	if (!chip->bbt)
		return chip->block_bad(mtd, ofs, getchip);

	/* Return info from the table */
	return nand_isbad_bbt(mtd, ofs, allowbbt);
}