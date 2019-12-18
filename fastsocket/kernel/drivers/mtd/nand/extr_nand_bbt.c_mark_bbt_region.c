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
typedef  int uint8_t ;
struct nand_chip {int numchips; int chipsize; int bbt_erase_shift; int page_shift; int* bbt; } ;
struct nand_bbt_descr {int options; int* pages; int maxblocks; scalar_t__ reserved_block_code; } ;
struct mtd_info {int size; struct nand_chip* priv; } ;
typedef  int loff_t ;

/* Variables and functions */
 int NAND_BBT_ABSPAGE ; 
 int NAND_BBT_LASTBLOCK ; 
 int NAND_BBT_PERCHIP ; 
 int NAND_BBT_WRITE ; 
 int /*<<< orphan*/  nand_update_bbt (struct mtd_info*,int) ; 

__attribute__((used)) static void mark_bbt_region(struct mtd_info *mtd, struct nand_bbt_descr *td)
{
	struct nand_chip *this = mtd->priv;
	int i, j, chips, block, nrblocks, update;
	uint8_t oldval, newval;

	/* Do we have a bbt per chip ? */
	if (td->options & NAND_BBT_PERCHIP) {
		chips = this->numchips;
		nrblocks = (int)(this->chipsize >> this->bbt_erase_shift);
	} else {
		chips = 1;
		nrblocks = (int)(mtd->size >> this->bbt_erase_shift);
	}

	for (i = 0; i < chips; i++) {
		if ((td->options & NAND_BBT_ABSPAGE) ||
		    !(td->options & NAND_BBT_WRITE)) {
			if (td->pages[i] == -1)
				continue;
			block = td->pages[i] >> (this->bbt_erase_shift - this->page_shift);
			block <<= 1;
			oldval = this->bbt[(block >> 3)];
			newval = oldval | (0x2 << (block & 0x06));
			this->bbt[(block >> 3)] = newval;
			if ((oldval != newval) && td->reserved_block_code)
				nand_update_bbt(mtd, (loff_t)block << (this->bbt_erase_shift - 1));
			continue;
		}
		update = 0;
		if (td->options & NAND_BBT_LASTBLOCK)
			block = ((i + 1) * nrblocks) - td->maxblocks;
		else
			block = i * nrblocks;
		block <<= 1;
		for (j = 0; j < td->maxblocks; j++) {
			oldval = this->bbt[(block >> 3)];
			newval = oldval | (0x2 << (block & 0x06));
			this->bbt[(block >> 3)] = newval;
			if (oldval != newval)
				update = 1;
			block += 2;
		}
		/* If we want reserved blocks to be recorded to flash, and some
		   new ones have been marked, then we need to update the stored
		   bbts.  This should only happen once. */
		if (update && td->reserved_block_code)
			nand_update_bbt(mtd, (loff_t)(block - 2) << (this->bbt_erase_shift - 1));
	}
}