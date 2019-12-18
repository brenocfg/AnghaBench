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
struct nand_chip {int bbt_erase_shift; int* bbt; } ;
struct mtd_info {struct nand_chip* priv; } ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,unsigned int,int,int) ; 
 int /*<<< orphan*/  MTD_DEBUG_LEVEL2 ; 

int nand_isbad_bbt(struct mtd_info *mtd, loff_t offs, int allowbbt)
{
	struct nand_chip *this = mtd->priv;
	int block;
	uint8_t res;

	/* Get block number * 2 */
	block = (int)(offs >> (this->bbt_erase_shift - 1));
	res = (this->bbt[block >> 3] >> (block & 0x06)) & 0x03;

	DEBUG(MTD_DEBUG_LEVEL2, "nand_isbad_bbt(): bbt info for offs 0x%08x: (block %d) 0x%02x\n",
	      (unsigned int)offs, block >> 1, res);

	switch ((int)res) {
	case 0x00:
		return 0;
	case 0x01:
		return 1;
	case 0x02:
		return allowbbt ? 0 : 1;
	}
	return 1;
}