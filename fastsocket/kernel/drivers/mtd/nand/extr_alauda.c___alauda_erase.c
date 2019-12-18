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
typedef  int u32 ;
struct mtd_info {scalar_t__ erasesize; struct alauda* priv; } ;
struct erase_info {int addr; int len; } ;
struct alauda {int blockmask; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int alauda_erase_block (struct mtd_info*,int) ; 
 int alauda_isbad (struct mtd_info*,int) ; 

__attribute__((used)) static int __alauda_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	struct alauda *al = mtd->priv;
	u32 ofs = instr->addr;
	u32 len = instr->len;
	int err;

	if ((ofs & al->blockmask) || (len & al->blockmask))
		return -EINVAL;

	while (len) {
		/* don't erase bad blocks */
		err = alauda_isbad(mtd, ofs);
		if (err > 0)
			err = -EIO;
		if (err < 0)
			return err;

		err = alauda_erase_block(mtd, ofs);
		if (err < 0)
			return err;

		ofs += mtd->erasesize;
		len -= mtd->erasesize;
	}
	return 0;
}