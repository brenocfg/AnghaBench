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
struct mtd_info {struct DiskOnChip* priv; } ;
struct DiskOnChip {scalar_t__ interleave; } ;
typedef  int loff_t ;

/* Variables and functions */
 unsigned int NAND_CMD_READ0 ; 
 unsigned int NAND_CMD_READ1 ; 
 unsigned int NAND_CMD_READOOB ; 

__attribute__((used)) static unsigned int DoC_GetDataOffset(struct mtd_info *mtd, loff_t *from)
{
	struct DiskOnChip *this = mtd->priv;

	if (this->interleave) {
		unsigned int ofs = *from & 0x3ff;
		unsigned int cmd;

		if (ofs < 512) {
			cmd = NAND_CMD_READ0;
			ofs &= 0x1ff;
		} else if (ofs < 1014) {
			cmd = NAND_CMD_READ1;
			ofs = (ofs & 0x1ff) + 10;
		} else {
			cmd = NAND_CMD_READOOB;
			ofs = ofs - 1014;
		}

		*from = (*from & ~0x3ff) | ofs;
		return cmd;
	} else {
		/* No interleave */
		if ((*from) & 0x100)
			return NAND_CMD_READ1;
		return NAND_CMD_READ0;
	}
}