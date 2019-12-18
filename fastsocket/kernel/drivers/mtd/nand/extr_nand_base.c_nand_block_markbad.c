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
struct nand_chip {int (* block_markbad ) (struct mtd_info*,int /*<<< orphan*/ ) ;} ;
struct mtd_info {struct nand_chip* priv; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int nand_block_isbad (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int stub1 (struct mtd_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nand_block_markbad(struct mtd_info *mtd, loff_t ofs)
{
	struct nand_chip *chip = mtd->priv;
	int ret;

	if ((ret = nand_block_isbad(mtd, ofs))) {
		/* If it was bad already, return success and do nothing. */
		if (ret > 0)
			return 0;
		return ret;
	}

	return chip->block_markbad(mtd, ofs);
}